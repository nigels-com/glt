#include <math/hash.h>

#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc,char *argv[])
{
    for (int i=0; i<16; ++i)
      for (int j=0; j<16; ++j)
      {
          cout << i << ' ' << hashWang32(i)%16 << ' ';
          cout << j << ' ' << hashWang32(j)%16 << ' ';
          cout << hashWang32(hashWang32(i)^j)%16 << endl;
      }

    return EXIT_SUCCESS;
}
