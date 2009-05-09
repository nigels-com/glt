/** \file
 * Randomised Swiss Cheese CSG Tree Generation
 *
 * http://www.nigels.com/research/
 *
 * \author  Nigel Stewart (nigels@nigels.com)
 * \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include <math/random.h>
#include <math/vector3.h>

#include <iostream>
#include <cstdlib>
using namespace std;

int type = 0;
double radius = 0;
int seed = 1974;
int n = 0;

bool args(int argc,char *argv[])
{
    if (argc!=5)
        return false;

    type   = atoi(argv[1]);
    radius = atof(argv[2]);
    seed   = atoi(argv[3]);
    n      = atoi(argv[4]);

    if (radius<=0.0)
        return false;

    if (n<0)
        return false;

    return true;
}

int main(int argc,char *argv[])
{
    if (!args(argc,argv))
    {
        cout << endl;
        cout << "Random Swiss Cheese" << endl;
        cout << "Nigel Stewart (nigels@nigels.com)" << endl;
        cout << "RMIT School of Computer Science & IT" << endl;
        cout << "2nd April 2002" << endl;
        cout << endl;
        cout << "Usage: cheese type radius seed n" << endl;
        cout << endl;
        cout << "\t type - 0 for intersection, 1 for subtraction."<< endl;
        cout << "\t radius is the maximum hole radius" << endl;
        cout << "\t seed is for random numbers" << endl;
        cout << "\t n is the number of holes" << endl;
        cout << endl;

        return EXIT_FAILURE;
    }

    GltRandomLFSRMix                  core(seed);
    GltRandomDouble<GltRandomLFSRMix> rand(core);

    cout << "X = sphere yellow scale 1.0 2.0 1.0" << endl;

    if (type==0)
    {
        cout << "Slice1      = box yellow translate 1 1 1 scale 1 0.50 1" << endl;
        cout << "Slice2      = box yellow translate 1 1 1 scale 1 0.51 1 rotate 0 1 0 -10" << endl;
    }
    else
    {
        cout << "Slice1      = box yellow translate 0 0 -1" << endl;
        cout << "Slice2      = box yellow translate 0 0 -1 rotate 0 1 0 260" << endl;
        cout << "Slice3      = box yellow translate 0 -1 0 " << endl;
        cout << "Slice4      = box yellow translate 0 1.99  0" << endl;
    }

    for (int i=0; i<n; i++)
    {
        const double r = rand.rand()*radius;

        cout << "A" << i << " = sphere orange";
        cout << " scale "     << r     << " " << r     << " " << r;
        cout << " translate " << pow(rand.rand(),0.5) << " " << rand.rand() << " " << 0.0;
        cout << " rotate 0 1 0 " << rand.rand()*80.0;
        cout << endl;
    }

    {
        if (type==0)
            cout << "Tree = (X.(Slice1.(Slice2-";
        else
            cout << "Tree = (X-(Slice1+(Slice2+(Slice3+(Slice4+";

        for (int i=0; i<n-1; i++)
            cout << "(A" << i << "+";
        cout << "A" << n-1;
    }

    {
        for (int i=0; i<n-1; i++)
            cout << ")";

        if (type==0)
            cout << ")))" << endl;
        else
            cout << ")))))" << endl;

        //

        if (type==1)
            cout << "Tree = (X-(Slice1+(Slice2+(Slice3+Slice4))))";

    }

    {
        cout << "Tree = (";
        int i;
        for (i=0; i<n-2; i++)
            cout << "A" << i << "+(";
        cout << "A" << i << "+A" << i+1;
        for (i=0; i<n-1; i++)
            cout << ")";
        cout << endl;
    }

    cout << "Transform =  translate  -0.4 -0.5 -0.4" << endl;

    return EXIT_SUCCESS;
}

