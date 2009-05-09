/** \file
 * Create helical CSG trees
 *
 * http://www.nigels.com/research/
 *
 * \author  Nigel Stewart (nigels@nigels.com)
 * \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include <math/path.h>

#include <mesh/sweep.h>
#include <mesh/mesh.h>

#include <node/shapes.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

void writePoint(ostream &os,const Point &point)
{
    os << point.position().x() << ' ';
    os << point.position().y() << ' ';
    os << point.position().z() << ' ';
    os << point.normal().x() << ' ';
    os << point.normal().y() << ' ';
    os << point.normal().z() << ' ';
}

void writeTriangle(ostream &os,const Triangle &triangle)
{
    writePoint(os,*triangle[0]);
    writePoint(os,*triangle[1]);
    writePoint(os,*triangle[2]);
}

void writeQuad(ostream &os,const Quad &quad)
{
    writePoint(os,*quad[0]);
    writePoint(os,*quad[1]);
    writePoint(os,*quad[2]);
    writePoint(os,*quad[3]);
}

void writeMesh(ostream &os,const Mesh &mesh)
{
    uint32 i;

    os << "mesh ";

    cout << mesh.triangle().size() << " ";
    for (i=0; i<mesh.triangle().size(); i++)
        writeTriangle(os,mesh.triangle()[i]);

    cout << mesh.quad().size() << " ";
    for (i=0; i<mesh.quad().size(); i++)
        writeQuad(os,mesh.quad()[i]);
}

int    n = 1;
bool   convex = false;
int    stacks = 20;
int    slices = 20;
double radius = 0.5;
double freq   = 2.0;

int main(int argc,char *argv[])
{
    if (argc!=7)
    {
        cout << endl;
        cout << "Helix Generation" << endl;
        cout << "Nigel Stewart (nigels@nigels.com)" << endl;
        cout << "RMIT Department of Mechanical and Manufacturing Engineering" << endl;
        cout << "14th August 2001" << endl;
        cout << endl;
        cout << "Usage: helix [n] [convex] [stacks] [slices] [radius] [freq]" << endl;
        cout << endl;
        cout << "\t n is the number of helix shapes" << endl;
        cout << "\t convex controls convex helix segment generation" << endl;
        cout << "\t stacks,slices triangle resolution" << endl;
        cout << "\t radius helix radius" << endl;
        cout << "\t freq number of revolutions" << endl;
        cout << endl;

        return EXIT_FAILURE;
    }

    n      = atoi(argv[1]);
    convex = atoi(argv[2])!=0;
    stacks = atoi(argv[3]);
    slices = atoi(argv[4]);
    radius = atof(argv[5]);
    freq   = atof(argv[6]);

    vector<string> colours;
    colours.push_back("red");
    colours.push_back("green");
    colours.push_back("blue");
    colours.push_back("yellow");
    colours.push_back("white");
    colours.push_back("black");

    vector<string> subtract;

    cout << "X = cylinder grey scale 1 1 4.0 translate 0 0 0.5" <<endl;

    for (int i=0; i<n; i++)
    {
        // Helix

        GltShape *meshes = MeshSweep(GltPath3DHelix(Vector0,VectorZ*5.0,1.0,freq,double(i)/double(n)*M_2PI),radius,slices,stacks,convex);

        //
        // Concave case
        //

        Mesh *mesh = dynamic_cast<Mesh *>(meshes);
        if (mesh)
        {
            char name[1024];
            sprintf(name,"M%d",i);
            subtract.push_back(name);

            cout << name << " = ";
            writeMesh(cout,*mesh);
            cout << ' ' << colours[i%colours.size()] << endl;
        }

        //
        // Convex case
        //

        GltShapes *shapes = dynamic_cast<GltShapes *>(meshes);
        if (shapes)
        {
            for (uint32 j=0; j<shapes->size(); j++)
            {
                Mesh *mesh = dynamic_cast<Mesh *>((*shapes)[j].get());
                if (mesh)
                {
                    char name[1024];
                    sprintf(name,"M%d_%d",i,j);
                    subtract.push_back(name);

                    cout << name << " = ";
                    writeMesh(cout,*mesh);
                    cout << ' ' << colours[i%colours.size()] << endl;
                }
            }
        }

        delete meshes;
    }

    if (subtract.size())
    {
        {
            cout << "Tree = (X-";
            for (uint32 i=0; i<subtract.size()-1; i++)
                cout << "(" << subtract[i] << "+";
            cout << subtract.back();
        }

        {
            for (uint32 i=0; i<subtract.size(); i++)
                cout << ')';
            cout << endl;
        }
    }

    cout << "Transform = translate 0 0 -2.5" <<endl;

    return EXIT_SUCCESS;
}
