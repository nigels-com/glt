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
    static Grips *window = new Grips(400,400,10,10);

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
        window->read(shadowsExample);

    window->open();

    return true;
}
