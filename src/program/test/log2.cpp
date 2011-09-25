#include <math/real.h>

#include <cstdlib>
#include <iostream>
using namespace std;

ostream &printLog2(ostream &os,const uint32 v)
{
    os << "log2(1<<" << v << ") = log2(" << (1u<<v) << ") = " << log2(1u<<v) << endl;
    return os;
}

int main(int argc,char *argv[])
{
    for (unsigned int i=0; i<32; ++i)
    {
        printLog2(cout,i);
    }

    return EXIT_SUCCESS;
}
