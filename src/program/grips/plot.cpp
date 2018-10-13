#include "plot.h"
#include "psystem.h"

#include <node/fields.h>

#include <iostream>
using namespace std;

const string Plot::_plotModeDescription[Plot::PLOT_MAX] =
{
    "x",
    "y",
    "z",
    "xy",
    "xyz"
};

Plot::Plot()
: _enable(false), _mode(PLOT_X), _particle(0)
{
}

Plot::~Plot()
{
}

void
Plot::update(ParticleSystem &system) const
{
    if (!_enable)
        return;

    if (_particle>=0 && _particle<system.size())
    {
        cout << system._t;

        if (_mode==PLOT_X || _mode==PLOT_XY || _mode==PLOT_XYZ)
            cout << '\t' << system[_particle]._position.x();

        if (_mode==PLOT_Y || _mode==PLOT_XY || _mode==PLOT_XYZ)
            cout << '\t' << system[_particle]._position.y();

        if (_mode==PLOT_Z || _mode==PLOT_XYZ)
            cout << '\t' << system[_particle]._position.z();

        cout << endl;
    }
}

GltFieldPtr
Plot::settings()
{
    GltFields *root = new GltFields("plot");
    root->add(_enable,"enable");
    root->add((int &)_mode,PLOT_MAX,_plotModeDescription,"mode");
    root->add(_particle,"particle");
    return root;
}
