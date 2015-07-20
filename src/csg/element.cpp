#include "element.h"

#include <cassert>
#include <iostream>
#include <set>
using namespace std;

#include <node/shape.h>
#include <node/shapes.h>

#include <glt/error.h>

/////////////////////////////////////////////////////////////////////////////

CsgElement::CsgElement()
: _positive(false)
{
}

CsgElement::CsgElement(ReferenceCountPtr<GltShape> shape,bool positive)
: _shape(shape), _positive(positive)
{
    updateBox();
}

CsgElement::~CsgElement()
{
}

void
CsgElement::updateBox()
{
    if (_shape.get())
        _shape.get()->boundingBox(_box);
}

const BoundingBox &CsgElement::box() const { return _box; }

void
CsgElement::drawFront() const
{
    if (!_shape.get())
        return;

    GLERROR

    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        _shape.get()->draw();

    glPopAttrib();

    GLERROR
}

void
CsgElement::drawBack() const
{
    if (!_shape.get())
        return;

    GLERROR

    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        _shape.get()->draw();

    glPopAttrib();

    GLERROR
}

string
CsgElement::toString() const
{
    assert(_shape.get());
    return _shape.get()->name();
}

bool
CsgElement::operator==(const CsgElement &el) const
{
    assert(_shape.get() && el._shape.get());
    return _shape.get()->name()==el._shape.get()->name() && _positive==el._positive;
}

//////////////////////////////////////////////////////////

CsgProduct::CsgProduct()
{
}

CsgProduct::~CsgProduct()
{
}

string
CsgProduct::toString() const
{
    string tmp;

    tmp += '(';

    for (GLuint i=0; i<size(); i++)
    {
        if (i>0)
            tmp += ((*this)[i]._positive ? '.' : '-');

        tmp +=  (*this)[i].toString();
    }

    tmp += ')';

    return tmp;
}

void
CsgProduct::negate()
{
    for (GLuint i=0; i<size(); i++)
        (*this)[i]._positive = !(*this)[i]._positive;
}

void
CsgProduct::optimise()
{
    for (GLuint i=0; i<size(); i++)
    {
        for (GLuint j=i+1; j<size(); j++)
        {
            const CsgElement &el1 = (*this)[i];
            const CsgElement &el2 = (*this)[j];

            // Look for two instances of the same node

            if ((*el1._shape).name() == (*el2._shape).name())
            {
                // Check if the second is a duplicate

                if (el1._positive == el2._positive)
                {
                    erase(begin()+j);
                    break;
                }
                else
                {
                    // The second is opposite sign
                    erase(begin(),end());
                    return;
                }
            }
        }
    }
}

bool
CsgProduct::contains(const CsgProduct &other) const
{
    for (GLuint i=0; i<other.size(); i++)
    {
        bool found = false;

        for (GLuint j=0; j<size(); j++)
            if (other[i]==(*this)[j])
            {
                found = true;
                break;
            }

        if (!found)
            return false;
    }

    return true;
}

bool
CsgProduct::split(CsgProduct &intersect,CsgProduct &subtract) const
{
    int n = 0;

    {
        for (GLuint i=0; i<size(); i++)
            if ((*this)[i]._positive)
                n++;
    }

    intersect.clear();
    subtract.clear();

    {
        for (GLuint i=0; i<size(); i++)
            if ((*this)[i]._positive)
                intersect.push_back((*this)[i]);
            else
                subtract.push_back((*this)[i]);
    }

    return true;
}

bool
CsgProduct::split(GltShapes &intersect,GltShapes &subtract) const
{
    for (GLuint i=0; i<size(); i++)
        if ((*this)[i]._positive)
            intersect.push_back((*this)[i]._shape);
        else
            subtract.push_back((*this)[i]._shape);

    return true;
}

void
CsgProduct::remove(const CsgProduct &other)
{
    for (GLuint i=0; i<other.size(); i++)
        for (GLuint j=0; j<size(); j++)
            if ((*this)[j]==other[i])
            {
                erase(begin()+j);
                j--;
            }
}

void
CsgProduct::add(CsgProduct &prod)
{
    insert(end(),prod.begin(),prod.end());
}

const ReferenceCountPtr<GltShape> &
CsgProduct::shape(const int i) const
{
    assert(i>=0 && size_t(i)<=size());
    return (*this)[i]._shape;
}

const bool &
CsgProduct::positive(const int i) const
{
    assert(i>=0 && size_t(i)<=size());
    return (*this)[i]._positive;
}

const CsgOverlapGraph &CsgProduct::graph() const { return _graph; }
      CsgOverlapGraph &CsgProduct::graph()       { return _graph; }

vector<bool>
CsgProduct::intersected() const
{
    vector<bool> tmp(size());

    for (GLuint i=0; i<size(); i++)
        tmp[i] = positive(i);

    return tmp;
}

////////////////////////////////////////////////////

CsgSumOfProducts::CsgSumOfProducts()
{
}

CsgSumOfProducts::~CsgSumOfProducts()
{
}

void CsgSumOfProducts::optimise()
{
    // Optimise individual products

    for (GLuint i=0; i<size(); i++)
    {
        (*this)[i].optimise();
        if ((*this)[i].size()==0)
        {
            erase(begin()+i);
            i--;
        }
    }

    // Dispose of unnecessary products

    {
        for (GLuint i=0; i<size(); i++)
            for (GLuint j=0; j<size(); j++)
                if (i!=j)
                {
                    const CsgProduct &sumPositive = (*this)[i];
                          CsgProduct sumNegative = sumPositive;

                    sumNegative.negate();

                    const CsgProduct &other = (*this)[j];

                    if (sumPositive.contains(other))
                    {
                        erase(begin()+i);
                        i--;
                        break;
                    }

                    if (sumNegative.contains(other))
                    {
                        sumNegative.remove(other);
                        sumNegative.negate();
                        (*this)[i] = sumNegative;
                    }
                }
    }
}

string CsgSumOfProducts::toString() const
{
    string tmp;

    for (GLuint i=0; i<size(); i++)
    {
        if (i>0)
            tmp += " + ";

        tmp += (*this)[i].toString();
    }

    return tmp;
}

bool
CsgSumOfProducts::writePov(ostream &os) const
{
    // First output all named shapes

    os << "// Primitive shapes" << endl << endl;

    {
        set<const GltShape *> list;
        for (GLuint i=0; i<size(); i++)
            for (GLuint j=0; j<(*this)[i].size(); j++)
            {
                const GltShapePtr &shape = (*this)[i].shape(j);
                if (list.find(shape.get())==list.end())
                {
                    list.insert(shape.get());
                    os << "// " << shape->name() << endl;
                    os << "#declare " << shape->name() << " = " << endl;
                    shape->povrayExport(os);
                    os << ";" << endl << endl;
                }
            }
    }

    // Then output trees

    os << "// CSG Trees" << endl << endl;

    for (GLuint i=0; i<size(); i++)
    {
        CsgProduct intersect,subtract;
        (*this)[i].split(intersect,subtract);

        os << "difference {" << endl;
        os << "intersection {" << endl;

        {
            for (GLuint j=0; j<intersect.size(); j++)
                os << "\tobject { " << intersect.shape(j)->name() << " }" << endl;
        }

        os << "}" << endl;

        {
            for (GLuint j=0; j<subtract.size(); j++)
                os << "\tobject { " << subtract.shape(j)->name() << " }" << endl;
        }

        os << "}" << endl;
    }

    return true;
}

void CsgSumOfProducts::add(CsgSumOfProducts &sum)
{
    insert(end(),sum.begin(),sum.end());
}
