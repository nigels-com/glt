#include "colmap.h"

#include "psystem.h"
#include <glt/rgb.h>
#include <node/fields.h>

#include <cmath>
using namespace std;

const string ColorMap::_modeDescription[MAPPING_MAX] =
{
    "None",
    "Speed",
    "Accel",
    "Age",
    "XPlane",
    "Index",
    "Line"
};

const string ColorMap::_schemeDescription[COLOR_SCHEME_MAX] =
{
    "BlueToRed",
    "WhiteFade",
    "RedWhiteBlue"
};

ColorMap::ColorMap()
: _mode(MAPPING_NONE),
  _scheme(COLOR_SCHEME_BLUE_RED),
  _min(0.0),
  _max(1.0)
{
    _map[COLOR_SCHEME_BLUE_RED].addEntry(0.00,darkBlue);
    _map[COLOR_SCHEME_BLUE_RED].addEntry(0.05,darkGrey);
    _map[COLOR_SCHEME_BLUE_RED].addEntry(0.30,grey);
    _map[COLOR_SCHEME_BLUE_RED].addEntry(1.00,red);

    _map[COLOR_SCHEME_WHITE_TRANS].addEntry(0.00,white,1.0);
    _map[COLOR_SCHEME_WHITE_TRANS].addEntry(1.00,white,0.0);

    _map[COLOR_SCHEME_RED_WHITE_BLUE].addEntry(0.00,red);
    _map[COLOR_SCHEME_RED_WHITE_BLUE].addEntry(0.50,white);
    _map[COLOR_SCHEME_RED_WHITE_BLUE].addEntry(1.00,blue);
}

ColorMap::~ColorMap()
{
}

void
ColorMap::update(ParticleSystem &system) const
{
    // Update colours of all bodies

    switch (_mode)
    {

    case MAPPING_SPEED:
        {
            // Avoid divide by zero

            assert(fabs(_max-_min)>1e-5);
            if (fabs(_max-_min)<1e-5)
                return;

            // Pre-calculate scale factor

            const double scale = 1.0/(_max-_min);

            for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
            {
                Particle &a = *i;
                const double t = (a._velocity.length()-_min)*scale;
                a._color = _map[_scheme].lookup(t);
            }
        }
        break;

    case MAPPING_ACCEL:
        {
            for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
            {
                Particle &a = *i;
                a._color = a._velocity*a._acceleration>0.0 ? red : blue;
            }
        }
        break;

    case MAPPING_AGE:
        {
            const double scale = 1.0/(_max-_min);

            for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
            {
                Particle &a = *i;
                a._color = _map[_scheme].lookup((a._age-_min)*scale);
            }
        }
        break;

    case MAPPING_XPLANE:
        {
            for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
            {
                Particle &a = *i;
                a._color = a._position.x()<0.0 ? red : blue;
            }
        }
        break;

    case MAPPING_INDEX:
        {
            const GltColor colors[6] = {red,green,blue,orange,purple,white};
            int j=0;

            for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++,j=(j+1)%6)
                i->_color = colors[j];
        }
        break;

    case MAPPING_LINE:
        {
            const double max = std::max(1,system.size()-1);
            int j = 0;

            for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++,j++)
                i->_color = lerp(red,blue,double(j)/max);
        }
        break;

    default:
        break;
    }
}


GltFieldPtr
ColorMap::settings()
{
    GltFields *root = new GltFields("colmap");
    root->add((int &) _mode,  MAPPING_MAX,_modeDescription,"mode");
    root->add((int &) _scheme,COLOR_SCHEME_MAX,_schemeDescription,"scheme");
    root->add(_min,0.2, "min");
    root->add(_max,0.2, "max");
    return root;
}

