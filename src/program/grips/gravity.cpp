#include "gravity.h"

#include "psystem.h"
#include "particle.h"

#include <math/vector3.h>
#include <node/fields.h>

#include <iostream>
#include <cmath>
using namespace std;

EngineGravity::EngineGravity()
: _Grav(1.0)
{
}

EngineGravity::~EngineGravity()
{
}

Vector
EngineGravity::field(const ParticleSystem &system,const Vector &x) const
{
    Vector f = Vector0;

    for (ParticleSystem::const_iterator i=system.begin(); i!=system.end(); i++)
    {
        const Particle &a = *i;

        if (a._position==x)
            continue;

        Vector direction = a._position - x;
        const double r2 = direction*direction;

        if (r2<1e-8)
            continue;

        direction.normalize();
        f += _Grav*(a._mass/r2)*direction;
    }

   return f;
}

void
EngineGravity::boundingBox(BoundingBox &box,const ParticleSystem &system,const double f) const
{
    box.reset();
    for (ParticleSystem::const_iterator i=system.begin(); i!=system.end(); i++)
    {
        BoundingBox tmp;
        boundingBox(tmp,system,f,*i);
        box += tmp;
    }
}

void
EngineGravity::boundingBox(BoundingBox &box,const ParticleSystem &system,const double f,const Particle &body) const
{
    box.reset();

    if (f<1e-8)
        return;

    const double r = sqrt(_Grav*body._mass/f);
    const Vector R(r,r,r);
    box = BoundingBox(body._position-R,body._position+R);
}

void
EngineGravity::update(ParticleSystem &system) const
{
    // Calculate acceleration for each moving
    // object in the system

    ParticleSystem::iterator i;

    for (i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        // Reset acceleration to zero,
        a._acceleration = Vector0;

        if (!a._fixed)
        {
            // Sum the combined gravitation attraction
            // of other objects in the system

            a._acceleration += field(system,a._position);
        }
    }

    // Update position of each moving object

    for (i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        // Only update the velocity & position of non-fixed objects

        if (!a._fixed)
        {
            switch (_integrator)
            {

            //
            // Euler Method
            //
            // Vnext = Vprev + dt * Aprev
            // Pnext = Pprev + dt * Vprev
            //

            case INTEGRATE_EULER:
                a._position += a._velocity*_dt;
                a._velocity += a._acceleration*_dt;
                break;

            //
            // Midpoint method
            //
            // Vnext = Vprev + dt * Aprev
            // Pnext = Pprev + dt * (Vprev + Vnext)/2
            //

            case INTEGRATE_MIDPOINT:
                {
                    const Vector v = a._velocity;
                    a._velocity += a._acceleration*_dt;
                    a._position += (a._velocity+v)*_dt*0.5;
                }
                break;

            //
            // Euler-Cromer Method
            //
            // Vnext = Vprev + dt * Aprev
            // Pnext = Pprev + dt * Vnext
            //

            case INTEGRATE_EULER_CROMER:
            default:
                a._velocity += a._acceleration*_dt;
                a._position += a._velocity*_dt;
                break;
            }

            // Make things bounce off the bounding-box walls,
            // if it's defined.

            if (_boundingBox.defined())
                for (int j=0; j<3; j++)
                {
                    if (a._position[j]<_boundingBox.min()[j])
                    {
                        a._velocity = Vector0;
//                      a._velocity[j] *= -1.0;
                        a._position[j] = _boundingBox.min()[j];
                    }

                    if (a._position[j]>_boundingBox.max()[j])
                    {
                        a._velocity = Vector0;
//                      a._velocity[j] *= -1.0;
                        a._position[j] = _boundingBox.max()[j];
                    }
                }
        }
    }

    system._t += _dt;
    system._i++;
}

void
EngineGravity::print(ostream &os) const
{
    os << "G:            " << _Grav << endl;
    os << endl;

    Integrator::print(os);
}

GltFieldPtr
EngineGravity::settings()
{
    GltFields *root = new GltFields("gravity");
    root->merge(Integrator::settings());
    root->add(_Grav,0.1,"G");
    return root;
}
