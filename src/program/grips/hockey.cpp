#include "hockey.h"

#include "psystem.h"
#include "particle.h"

#include <math/vector3.h>
#include <node/fields.h>
#include <glt/rgb.h>

#include <iostream>
#include <cmath>
using namespace std;

EngineHockey::EngineHockey()
:
    _e(1.0),
    _collision(true),
    _colorCode(true),
    _wallImpact(blue),
    _ballImpact(white)
{
    _boundingBox = BoundingBox(Vector(-10,-10,-10),Vector(10,10,10));
}

EngineHockey::~EngineHockey()
{
}

void
EngineHockey::update(ParticleSystem &system) const
{
    ParticleSystem::iterator i;

    // Update position of each puck

    for (i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        if (!a._fixed)
            a._position += a._velocity*_dt;
    }

    // Check for collision with walls

    for (i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        if (!a._fixed)
            for (int j=0; j<3; j++)
            {
                const double dmin = (a._position[j]-a._radius)-_boundingBox.min()[j];
                if (dmin<0)
                {
                    a._position[j] -= dmin;
                    a._velocity[j] *= -1.0;

                    if (_colorCode)
                        a._color = _wallImpact;
                }

                const double dmax = (a._position[j]+a._radius)-_boundingBox.max()[j];
                if (dmax>0)
                {
                    a._position[j] -= dmax;
                    a._velocity[j] *= -1.0;

                    if (_colorCode)
                        a._color = _wallImpact;
                }
            }
    }

    // Check for collision between balls

    if (_collision)
        for (i=system.begin(); i!=system.end(); i++)
        {
            Particle &a = *i;
            ParticleSystem::iterator j;

            j = i;
            j++;

            for (; j!=system.end(); j++)
            {
                Particle &b = *j;

                const double A = (a._velocity-b._velocity).norm();
                const double B = -2.0*(a._position-b._position)*(a._velocity-b._velocity);
                const double C = (a._position-b._position).norm() - sqr(a._radius + b._radius);

                const double q = B*B - 4*A*C;

                if (q>=0.0 && fabs(A)>1e-5)
                {
                    // TODO - Rethink this!
                    const double sqrt_q = sqrt(q);
                    const double inv2a  = 0.5 / A;

                    const double tMin = (-B+sqrt_q)*inv2a;
                    const double tMax = (-B-sqrt_q)*inv2a;

                    assert(A>=0.0);

                    // The flaw here is that the particles have
                    // already been advanced by the timestep,
                    // and here we are checking for the _next_
                    // timestep! oops!

                    const double t = (tMin>0.0 ? tMin : tMax);

                    if (t>=0.0 && t<=_dt)
                    {
                        // Collision occurs at t
                        //
                        // Now find line of collision, forming
                        // normal of plane tangent to collision

                        const Vector ca = a._position + a._velocity*t;
                        const Vector cb = b._position + b._velocity*t;
                        Vector n  = ca - cb;
                        n.normalize();

                        // Now find velocity in n for a and b

                        const double van = a._velocity * n;
                        const double vbn = b._velocity * n;

                        // Momentum is mass * velocity

                        const double momentum = a._mass * van + b._mass * vbn;

                        ///
                        // NOTE
                        //
                        // Well it works, but what's this about?
                        //

                        const double xxx = _e * (van - vbn);

                        // Now calculate new velocities for a and b in direction of n

                        const double vpan = (momentum-xxx*b._mass)/(a._mass + b._mass);
                        const double vpbn = xxx + vpan;

                        // Adjust velocities and continue...

                        // NOTE
                        //
                        // We shift the particles forward to the point
                        // of collision, but we may collide others
                        // along the way, and these won't be correctly
                        // handled.  This is a bug in addition to the
                        // fact that we are incrementing by more than
                        // the timeframe defined by _dt

                        a._position = ca;
                        b._position = cb;

                        a._velocity += (vpan-van)*n;
                        b._velocity += (vpbn-vbn)*n;

                        if (_colorCode)
                            a._color = b._color = _ballImpact;
                    }
                }
            }
        }

    system._t += _dt;
    system.updateAge(_dt);
    system._i++;
}

void
EngineHockey::print(ostream &os) const
{
    Integrator::print(os);
}

GltFieldPtr
EngineHockey::settings()
{
    GltFields *root = new GltFields("hockey");
    root->merge(Integrator::settings());
    root->add(_collision,   "collision");
    root->add(_e,0.1,       "e");
    root->add(_colorCode,   "colorCode");
    root->add(_wallImpact,  "wallImpact");
    root->add(_ballImpact,  "ballImpact");
    return root;
}

