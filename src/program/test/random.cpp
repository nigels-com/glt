#include <math/random.h>

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const string defaultDelim(" ");

template<class T>
void printNumbers(T &rng,const int n=100,const int perLine=8,const string &delim = defaultDelim)
{
    for (int i=0; i<n; i++)
    {
        if (perLine!=0 && i!=0 && i%perLine==0)
            cout << endl;

        cout << rng.rand() << delim;
    }

    cout << endl;
}

int main(int argc,char *argv[])
{
    cout << endl << "GLT_FAST_FLOAT is ";

    #ifndef GLT_FAST_FLOAT
    cout << "not ";
    #endif

    cout << "defined." << endl << endl;

    // 200 lcg random numbers

    cout << endl << "First 200 GltRandomLCG random numbers:" << endl;
    GltRandomLCG lcg;
    printNumbers(lcg,200);

    // 200 lsfr random numbers

    cout << endl << "First 200 GltRandomLFSRMix random numbers:" << endl;
    GltRandomLFSRMix lsfr;
    printNumbers(lsfr,200);

    // 200 random lsfr doubles

    cout << endl << "Second 200 GltRandomLFSRMix random numbers as doubles:" << endl;
    GltRandomDouble<GltRandomLFSRMix> drng(lsfr);
    printNumbers(drng,200);

    // 200 random lsfr integers

    cout << endl << "Third 200 GltRandomLFSRMix random numbers as integers [0,99]:" << endl;
    GltRandomInteger<GltRandomLFSRMix> irng(lsfr,0,99);
    printNumbers(irng,200);

    // 200 random lsfr positions on sphere surface
    cout << endl << "200 random positions on sphere surface:" << endl;
    GltRandomSphere<GltRandomLFSRMix> srng(lsfr);
    printNumbers(srng,200,0,string("\n"));

    return EXIT_SUCCESS;
}
