#include "lorenz.h"

#include "psystem.h"
#include "particle.h"

#include <math/vector3.h>
#include <node/fields.h>

#include <iostream>
#include <cmath>
using namespace std;

EngineLorenz::EngineLorenz()
: _r(28.0)
{
}

EngineLorenz::~EngineLorenz()
{
}

Vector
EngineLorenz::field(const ParticleSystem &system,const Vector &a) const
{
    Vector f;

    const double &x = a.x();
    const double &y = a.y();
    const double &z = a.z();

    // Lorenz equations

    f.x() = 10.0*(y-x);
    f.y() = _r*x - y - z*x;
    f.z() = -(8.0/3.0)*z + x*y;

   return f;
}

void
EngineLorenz::update(ParticleSystem &system) const
{
    // Update position of each moving object

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        if (!a._fixed)
        {
            Vector velocity = field(system,a._position);
            a._acceleration = (velocity-a._velocity)/_dt;
            a._velocity  = velocity;
            a._position += velocity*_dt;
            a._age      += _dt;
        }
    }

//  system.updateTrails();

    system._i++;
    system._t += _dt;
}

void
EngineLorenz::print(ostream &os) const
{
    os << "r:            " << _r << endl;
    os << endl;

    Integrator::print(os);
}

GltFieldPtr
EngineLorenz::settings()
{
    GltFields *root = new GltFields("lorenz");
    root->merge(Integrator::settings());
    root->add(_r,0.1,"r");
    return root;
}

