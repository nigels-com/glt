#include <glutm/main.h>

// Tentitive name: GRIPS - Grand Integrated Particle System
//
// TODO:
//          3-body example
//          Fix spin mode for master/slave
//
// See also:
//   http://www.glscene.org/   Newtonian Gravity By Eric Hardinge

#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

#include "window.h"
#include "examples.h"

#include <misc/string.h>

bool GlutMain(const std::vector<std::string> &arg)
{
#if 0
    int   argc = 2;
    char *argv[] = { "grips", "-warning" };
    glutInit(&argc,argv);
#endif

    static Grips *window = new Grips(480,480,20,20);

    if (arg.size()>1)
    {
        if (arg[1]=="-")
            window->read(cin);
        else
        {
            ifstream is(arg[1].c_str(),ios::in);
            if (is.good())
                window->read(is);
            else
            {
                cout << Grips::help;
                return false;
            }
        }
    }
    else
//        window->read(hockey2dExample);
//        window->read(shadowsExample);
        window->read(lorenz6Example);

    window->open();

    return true;
}
