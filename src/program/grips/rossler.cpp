#include "rossler.h"

#include "psystem.h"
#include "particle.h"

#include <math/vector3.h>
#include <node/fields.h>

#include <iostream>
#include <cmath>
using namespace std;

EngineRossler::EngineRossler()
: _a(0.2), _b(0.2), _c(5.7)
{
}

EngineRossler::~EngineRossler()
{
}

Vector
EngineRossler::field(const ParticleSystem &system,const Vector &a) const
{
    Vector f;

    const double &x = a.x();
    const double &y = a.y();
    const double &z = a.z();

    // Rossler equations

    f.x() = -y - z;
    f.y() = x + _a*y;
    f.z() = _b + x*z - _c*z;

   return f;
}

void
EngineRossler::update(ParticleSystem &system) const
{
    // Update position of each moving object

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        if (!a._fixed)
        {
            a._velocity = field(system,a._position);
            a._position += a._velocity*_dt;
            a._age += _dt;
        }
    }

//  system.updateTrails();

    system._i++;
    system._t += _dt;
}

void
EngineRossler::print(ostream &os) const
{
    os << "a:            " << _a << endl;
    os << "b:            " << _b << endl;
    os << "c:            " << _c << endl;
    os << endl;

    Integrator::print(os);
}

GltFieldPtr
EngineRossler::settings()
{
    GltFields *root = new GltFields("rossler");
    root->merge(Integrator::settings());
    root->add(_a,0.1,"a");
    root->add(_b,0.1,"b");
    root->add(_c,0.1,"c");
    return root;
}
