#include "model.h"

#include <math/matrix4.h>
#include <math/vector3.h>
#include <math/path.h>

#include <glutm/shape.h>

#include <mesh/mesh.h>
#include <mesh/sweep.h>

#include <node/dlist.h>

#include <glt/material.h>

#include <string>
#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;

CsgModel::CsgModel()
{
}

CsgModel::~CsgModel()
{
}

const int
CsgModel::trees() const
{
    return _trees.size();
}

GltShapePtr
CsgModel::tree(const int i)
{
    assert(i>=0 && i<_trees.size());
    return _trees[i];
}

const int
CsgModel::primitives() const
{
    return _primitives.size();
}

GltShapePtr
CsgModel::primitive(const int i)
{
    assert(i>=0 && i<_primitives.size());
    return _primitives[i];
}

bool
CsgModel::read(istream &is)
{
    reset();

    while (!is.eof() || is.good())
    {
        string name;
        is >> name;

        string equals;
        is >> equals;

        if (is.eof() && !name.size() && !equals.size())
            return true;

        if (!name.size() || !equals.size() || equals!="=")
        {
            cerr << "Error parsing CSG tree or shape, unexpected \"" << name << "\"" << endl;
            return false;
        }

        if (name=="Tree")
        {
            GltShapePtr tree;
            if (!readTree(tree,is))
            {
                cerr << "Error parsing CSG tree." << endl;
                return false;
            }

            _trees.push_back(tree);
        }
        else
        if (name=="Transform")
        {
            if (!read(_transform,is))
            {
                cerr << "Error parsing transformation." << endl;
                return false;
            }
        }
        else
        {
            GltShapePtr shape;
            if (!readShape(shape,is))
            {
                cerr << "Error parsing CSG shape: " << name << endl;
                return false;
            }

            shape->name() = name;
            _primitives.push_back(shape);
        }
    }

    return true;
}

bool
CsgModel::readToken(string &token,istream &is)
{
    bool begin = true;
    bool number = true;
    token = string();

    while (is.good() && !is.eof())
    {
        char ch = is.get();

        if ((ch<'0' || ch>'9') && ch!='.' && ch!='-' && ch!=' ' && ch!='\t')
            number = false;

        if (begin && ch=='\n')
            return true;

        if (begin && (ch==' ' || ch=='\t'))
            continue;

        if (begin && (ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='.'))
        {
            token += ch;
            return true;
        }

        begin = false;

        if (ch==' ' || ch=='\t' || ch=='\n')
        {
            is.putback(ch);
            return true;
        }

        if (!number && (ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='.'))
        {
            is.putback(ch);
            return true;
        }

        token += ch;

        if (ch=='(' || ch==')')
            return true;
    }

    return false;
}

bool
CsgModel::matchToken(const string &match,istream &is)
{
    string token;

    if (!readToken(token,is))
        return false;

    return token==match;
}

bool
CsgModel::readTree(GltShapePtr &tree, istream &is)
{
    string token;

    if (!readToken(token,is))
        return false;

    if (token=="(")
    {
        CsgNode *node = new CsgNode();
        tree = GltShapePtr(node);

        // Left sub-tree

        if (!readTree(node->left(),is))
            return false;

        // Read operator

        if (!readToken(token,is))
            return false;

        if (token.size()!=1)
            return false;

        switch (token[0])
        {
        case '+': node->type() = NODE_UNION;        break;
        case '.': node->type() = NODE_INTERSECTION; break;
        case '-': node->type() = NODE_DIFFERENCE;   break;
        default:
            return false;
        }

        // Right sub-tree

        if (!readTree(node->right(),is))
            return false;

        if (!matchToken(")",is))
            return false;
    }
    else
    {
        // Lookup shape by name

        for (uint32 i=0; i<_primitives.size(); i++)
            if (_primitives[i]->name()==token)
            {
                tree = _primitives[i];
                return true;
            }

        // Shape name is not known

        return false;
    }

    return true;
}

bool
CsgModel::readShape(GltShapePtr &shape,std::istream &is)
{
    string type;

    if (!readToken(type,is))
        return false;

         if (type=="sphere")   shape = new GlutSphere();
    else if (type=="box")      shape = new GlutCube();
    else if (type=="cylinder") shape = new GlutCylinder();
    else if (type=="cone")
    {
        GlutCone *cone = new GlutCone();
        cone->closed() = true;
        shape = cone;
    }
    else if (type=="torus")
    {
        double innerRadius;
        if (!read(innerRadius,is))
        {
            cerr << "Error parsing torus inner radius." << endl;
            return false;
        }

        double outerRadius;
        if (!read(outerRadius,is))
        {
            cerr << "Error parsing torus inner radius." << endl;
            return false;
        }

        shape = new GlutTorus(true,innerRadius,outerRadius);
    }
    else if (type=="helix" || type=="helixseg")
    {
        const bool segment = type=="helixseg";

        double radius,height,period;
        int    slices,stacks;
        int    index;

        if (!read(radius,is))
        {
            cerr << "Error parsing helix radius." << endl;
            return false;
        }

        if (!read(height,is))
        {
            cerr << "Error parsing helix height." << endl;
            return false;
        }

        if (!read(period,is))
        {
            cerr << "Error parsing helix period." << endl;
            return false;
        }

        if (!read(slices,is))
        {
            cerr << "Error parsing helix slices." << endl;
            return false;
        }

        if (!read(stacks,is))
        {
            cerr << "Error parsing helix stacks." << endl;
            return false;
        }

        if (segment)
        {
            // Index of convex segment

            if (!read(index,is))
            {
                cerr << "Error parsing helix segment index." << endl;
                return false;
            }
        }

        GltPath3DHelix curve(Vector0,VectorZ*height,1.0,period,0.0);
        GltShapePtr helix = MeshSweep(curve,radius,slices,stacks,segment);

        if (segment)
        {
            // Replace shape with convex segment

            GltShapes *v = dynamic_cast<GltShapes *>(helix.get());
            if (v && uint32(index)<v->size())
                shape = (*v)[index];
        }
        else
            shape = helix;

        shape->inheritSolid() = true;
    }
    else if (type=="mesh")
    {
        Mesh *mesh = new Mesh();
        if (!read(*mesh,is))
        {
            cerr << "Error parsing mesh." << endl;
            return false;
        }

        mesh->inheritSolid() = true;
        mesh->cullFace() = true;
        shape = mesh;
    }
    else
        {
            cerr << "Error parsing CSG shape type: " << type << endl;
            return false;
        }

    if (!read(shape->color(),is))
    {
        cerr << "Error parsing color" << endl;
        return false;
    }

    Matrix matrix;
    if (!read(matrix,is))
    {
        cerr << "Error parsing transformation matrix" << endl;
        return false;
    }

    shape->transformation() = matrix;

    return true;
}

bool
CsgModel::read(float &val,istream &is)
{
    is >> val;
    return true;
}

bool
CsgModel::read(double &val,istream &is)
{
    is >> val;
    return true;
}

bool
CsgModel::read(int &val,istream &is)
{
    is >> val;
    return true;
}

bool
CsgModel::read(Vector3 &v,std::istream &is)
{
    if (!read(v.x(),is))
        return false;

    if (!read(v.y(),is))
        return false;

    if (!read(v.z(),is))
        return false;

    return true;
}

bool
CsgModel::read(GltColor &color,std::istream &is)
{
    std::string name;
    if (!readToken(name,is))
        return false;

    color = name;
    return true;
}

bool
CsgModel::read(GltMaterial &material,std::istream &is)
{
    std::string name;
    if (!readToken(name,is))
        return false;

    // todo - actually lookup material by name

    material = GltMaterial();
    return true;
}

bool
CsgModel::read(Matrix &matrix,std::istream &is)
{
    string transform;
    if (!readToken(transform,is))
        return false;

    // End of line

    if (!transform.size())
    {
        matrix = Matrix();
        return true;
    }

    if (transform=="scale")
    {
        Vector3 scale;
        if (!read(scale,is))
        {
            cerr << "Error parsing scale, expecting vector." << endl;
            return false;
        }

        matrix = matrixScale(scale);
    }
    else
        if (transform=="translate")
        {
            Vector3 translate;
            if (!read(translate,is))
            {
                cerr << "Error parsing translation, expecting vector." << endl;
                return false;
            }

            matrix = matrixTranslate(translate);
        }
        else
            if (transform=="rotate")
            {
                Vector3 axis;
                if (!read(axis,is))
                {
                    cerr << "Error parsing rotation axis, expecting vector." << endl;
                    return false;
                }

                double angle;
                if (!read(angle,is))
                {
                    cerr << "Error parsing rotation angle, expecting double." << endl;
                    return false;
                }

                matrix = matrixRotate(axis,angle);
            }
            else
            {
                cerr << "Error parsing transformation, expecting translate, rotate or scale: found \"" << transform << "\"" << endl;
                return false;
            }

    Matrix m;
    if (read(m,is))
        matrix = matrix * m;

    return true;
}

bool
CsgModel::readTriangle(Triangle &val,Mesh &model,istream &is)
{
    Point a,b,c;

    if
    (
        !read(a.position(),is) ||
        !read(a.normal(),is)   ||
        !read(b.position(),is) ||
        !read(b.normal(),is)   ||
        !read(c.position(),is) ||
        !read(c.normal(),is)
    )
        return false;

    model.point().push_back(a);  Point *pa = &model.point().back();
    model.point().push_back(b);  Point *pb = &model.point().back();
    model.point().push_back(c);  Point *pc = &model.point().back();

    val = Triangle(pa,pb,pc);

    return true;
}

bool
CsgModel::readQuad(Quad &val,Mesh &model,istream &is)
{
    Point a,b,c,d;

    if
    (
        !read(a.position(),is) ||
        !read(a.normal(),is)   ||
        !read(b.position(),is) ||
        !read(b.normal(),is)   ||
        !read(c.position(),is) ||
        !read(c.normal(),is)   ||
        !read(d.position(),is) ||
        !read(d.normal(),is)
    )
        return false;

    model.point().push_back(a);  Point *pa = &model.point().back();
    model.point().push_back(b);  Point *pb = &model.point().back();
    model.point().push_back(c);  Point *pc = &model.point().back();
    model.point().push_back(d);  Point *pd = &model.point().back();

    val = Quad(pa,pb,pc,pd);

    return true;
}

bool
CsgModel::read(Mesh &val,istream &is)
{
    string token;

    int n;

    // Read triangles

    {
        if (!read(n,is))
            return false;

        #ifndef NDEBUG
        cout << "Reading " << n << " triangles..." << endl;
        #endif

        Triangle tri;
        for (int i=0; i<n; i++)
        {
            if (!readTriangle(tri,val,is))
            {
                cerr << "Error parsing triangle " << i << endl;
                return false;
            }

            val.triangle().push_back(tri);
        }
    }

    // Read quads

    {
        if (!read(n,is))
            return false;

        #ifndef NDEBUG
        cout << "Reading " << n << " quads..." << endl;
        #endif

        Quad quad;
        for (int i=0; i<n; i++)
        {
            if (!readQuad(quad,val,is))
            {
                cerr << "Error parsing quad " << i << endl;
                return false;
            }

            val.quad().push_back(quad);
        }
    }

    //

    return true;
}

bool
CsgModel::write(ostream &os)
{
    return false;
}

void
CsgModel::reset()
{
    _transform = Matrix();
    _trees.clear();
    _primitives.clear();
}

