#include "integrat.h"
#include "particle.h"
#include "psystem.h"

#include <iostream>
using namespace std;

const string Integrator::_integratorDescription[INTEGRATE_MAX] =
{
    "Euler",
    "Euler-Cromer",
    "Midpoint"
};

Integrator::Integrator()
:
  _integrator(INTEGRATE_EULER_CROMER),
  _dt(1.0)
{
}

Integrator::~Integrator()
{
}

Vector
Integrator::field(const ParticleSystem &system,const Vector &x) const
{
    return Vector0;
}

void
Integrator::boundingBox(BoundingBox &box,const ParticleSystem &system,const double f) const
{
    box.reset();
}

void
Integrator::boundingBox(BoundingBox &box,const ParticleSystem &system,const double f,const Particle &body) const
{
    box.reset();
}

void
Integrator::print(ostream &os) const
{
    os << "Time step:    " << _dt << endl;
    os << "Integrator:   " << _integratorDescription[_integrator] << endl;
    os << endl;
}

GltFieldPtr
Integrator::settings()
{
    GltFields *root = new GltFields("engine");
    root->add((int &) _integrator,INTEGRATE_MAX,_integratorDescription,"integrator");
    root->add(_dt       ,0.01,"step"     );
    root->add(_boundingBox,"box");

    return root;
}

