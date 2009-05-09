/** \file
 * 3-axis CSG Tree Generation
 *
 * http://www.nigels.com/research/
 *
 * \author  Nigel Stewart (nigels@nigels.com)
 * \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include <math/random.h>

typedef enum
{
    ENDMILL = 0,
    BALLNOSE,

    TOOL_MAX

} ToolType;

// Config

ToolType tool      = ENDMILL;
int      seed      = 1974;
int      n         = 10;
double   minRadius = 1.0;
double   maxRadius = 3.0;

const string color1("gray95");
const string color2("yellow");

// Parse command-line args

bool args(int argc,char *argv[])
{
    if (argc<4)
        return false;

    tool = (ToolType) atoi(argv[1]);
    seed =            atoi(argv[2]);
    n    =            atoi(argv[3]);

    if (tool<ENDMILL || tool>=TOOL_MAX)
        return false;

    if (n<0)
        return false;

    if (argc>4)
        minRadius = atof(argv[4]);

    if (argc>5)
        maxRadius = atof(argv[5]);

    return true;
}

int main(int argc,char *argv[])
{
    if (!args(argc,argv))
    {
        cout << endl;
        cout << "3Axis Drilling" << endl;
        cout << "Nigel Stewart (nigels@nigels.com)" << endl;
        cout << "RMIT School of Computer Science & IT" << endl;
        cout << "2nd April 2002" << endl;
        cout << endl;
        cout << "Usage: 3axis type seed n" << endl;
        cout << endl;
        cout << "\t type is 0 for endmill, or 1 for ballnose" << endl;
        cout << "\t seed is for random numbers" << endl;
        cout << "\t n is the number of subtracted operations" << endl;
        cout << endl;

        return EXIT_FAILURE;
    }

    GltRandomLCG rand(seed);

    cout << "X = box " << color1 << " scale 20 20 5.0" << endl;

    for (int i=0; i<n; i++)
    {
        double r = GltRandomDouble<GltRandomLCG>(rand,minRadius,maxRadius).rand();
        double x = GltRandomDouble<GltRandomLCG>(rand,-20.0,20.0).rand();
        double y = GltRandomDouble<GltRandomLCG>(rand,-20.0,20.0).rand();
        double z;

        switch (tool)
        {
        default:
        case ENDMILL:   z = GltRandomDouble<GltRandomLCG>(rand,-6.0,  5.0).rand(); break;
        case BALLNOSE:  z = GltRandomDouble<GltRandomLCG>(rand,-6.0+r,5.0).rand(); break;
        }

        cout << "C" << i << " = cylinder " << color2 << " \t";
        cout << "scale " << r << ' ' << r << ' ' << 6.0 - z;
        cout << " translate " << x << ' ' << y << ' ' << z << endl;

        if (tool==BALLNOSE)
        {
            // We scale by a fudge factor because the GLUT sphere is slightly
            // smaller than the GLUT cylinder for some strange reason.

            cout << "S" << i << " = sphere " << color2 << " \t";
            cout << "scale " << r*1.007 << ' ' << r*1.007 << ' ' << r*1.007;
            cout << " translate " << x << ' ' << y << ' ' << z << endl;
        }
    }

    // Output X-C0-...

    switch (tool)
    {
    default:
    case ENDMILL:
                    {
                        cout << "Tree = (X-";
                        for (int i=0; i<n-1; i++)
                            cout << "(C" << i << "+";
                        cout << "C" << n-1;
                    }

                    {
                        for (int i=0; i<n-1; i++)
                            cout << ")";
                        cout << ")" << endl;
                    }
                    break;

    case BALLNOSE:
                    {
                        cout << "Tree = (X-";
                        for (int i=0; i<n-1; i++)
                            cout << "(C" << i << "+(S" << i << "+";
                        cout << "(C" << n-1 << "+S" << n-1 << ")";
                    }

                    {
                        for (int i=0; i<n-1; i++)
                            cout << "))";
                        cout << ")" << endl;
                    }

                    break;
    }

    // Output C0+...

    switch (tool)
    {
    default:
    case ENDMILL:
                    {
                        cout << "Tree = ";
                        for (int i=0; i<n-1; i++)
                            cout << "(C" << i << "+";
                        cout << "C" << n-1;
                    }

                    {
                        for (int i=0; i<n-1; i++)
                            cout << ")";
                        cout << endl;
                    }
                    break;

    case BALLNOSE:
                    {
                        cout << "Tree = ";
                        for (int i=0; i<n-1; i++)
                            cout << "(C" << i << "+(S" << i << "+";
                        cout << "(C" << n-1 << "+S" << n-1 << ")";
                    }

                    {
                        for (int i=0; i<n-1; i++)
                            cout << "))";
                        cout << endl;
                    }

                    break;
    }

    return EXIT_SUCCESS;
}
