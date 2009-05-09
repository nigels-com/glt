/** \file
 * n-Cylinder-Intersection CSG Tree Generation
 *
 * The program creates test case csg trees
 * consisting of n intersected cylinders.
 * n should be specified on the command line.
 *
 * http://www.nigels.com/research/
 *
 * \author  Nigel Stewart (nigels@nigels.com)
 * \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc,char *argv[])
{
    if (argc!=2)
    {
        cout << endl;
        cout << "Cylinder Intersection CSG Tree" << endl;
        cout << "Nigel Stewart (nigels@nigels.com)" << endl;
        cout << "RMIT School of Computer Science & IT" << endl;
        cout << "2nd April 2002" << endl;
        cout << endl;
        cout << "Usage: cylinders [n]" << endl;
        cout << endl;
        cout << "\t n is the number of cylinders" << endl;
        cout << endl;

        return EXIT_FAILURE;
    }

    int    n = atoi(argv[1]);

    if (n<=0)
        return EXIT_FAILURE;

    for (int i=0; i<n; i++)
    {
        cout << "C" << i << " = cylinder orange \t";
        cout << "scale 1 1 2 ";
        cout << "translate 0 0 -1 ";
        cout << "rotate 0 1 0 " << double(i)/n*180.0 << endl;
    }

    {
        cout << "Tree = ";
        for (int i=0; i<n-1; i++)
            cout << "(C" << i << ".";
    }

    {
        cout << "C" << n-1;
        for (int i=0; i<n-1; i++)
            cout << ")";
    }

    return EXIT_SUCCESS;
}
