#include "project.h"

#include "psystem.h"
#include "particle.h"

#include <math/vector3.h>
#include <node/fields.h>

#include <misc/image.h>
#include <misc/string.h>

#include "textures.h"
#include <glt/texture.h>

#include <iostream>
#include <cmath>
using namespace std;

EngineProjectile::EngineProjectile()
: _g(9.8), _e(0.0), _b(0.0)
{

    /*
//  string data;
//  readFile("CamTest3.png",data);
//  decode(width,height,_image,handmaskTexture);

    uint32 width = 0;
    uint32 height = 0;
    uint32 format,components;

    GltTexture::decodeImage(handmaskTexture,format,components,width,height,_image);
    assert(_image.size()==256*256);
*/
}

EngineProjectile::~EngineProjectile()
{
}

void
EngineProjectile::update(ParticleSystem &system) const
{
#if 0
    {
        for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
            for (ParticleSystem::iterator j=i+1; j!=system.end(); j++)
            {
                Particle &a = *i;
                Particle &b = *j;

                if (!a._expired && !b._expired /* && a._age>10.0 && b._age>10.0 */ )
                {
                    if (a._position.dist(b._position)<sqr(a._radius+b._radius))
                    {
                        Vector d = b._position-a._position;
                        d.z() = 0.0;
                        d.normalize();
                        d *= _dt;

                        if (!a._fixed)
                            a._velocity -= d;

                        if (!b._fixed)
                            b._velocity += d;

//                      if (int(floor(a._age*b._age))%2)
//                      if (a._radius/b._radius > 3)
//                      if (b._radius<0.04 && a._radius>0.04)
/*
                        real x = MAX(a._radius,b._radius)+MIN(a._radius,b._radius)*0.5;
                        real y = MIN(a._radius,b._radius)*0.5;

                        if (x>0.1)
                        {
                            x = MAX(a._radius,b._radius);
                            y = MIN(a._radius,b._radius);
                        }

                        a._radius  = x;
                        b._radius  = y;
                        b._expired = true;
*/
                    }
                }
            }
    }
#endif

    // Update position of each moving object

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        // Only update position of non-fixed objects

        if (!a._fixed && !a._expired)
            switch (_integrator)
            {

            //
            // Euler Method
            //
            // Vnext = Vprev + dt * Aprev
            // Pnext = Pprev + dt * Vprev
            //

            //
            // Midpoint method
            //
            // Vnext = Vprev + dt * Aprev
            // Pnext = Pprev + dt * (Vprev + Vnext)/2
            //

            //
            // Euler-Cromer Method
            //
            // Vnext = Vprev + dt * Aprev
            // Pnext = Pprev + dt * Vnext
            //

            case INTEGRATE_EULER:
            case INTEGRATE_MIDPOINT:

            case INTEGRATE_EULER_CROMER:
            default:

                if (!a._fixed)
                {
                    a._velocity     -= a._velocity*_b*_dt;      // Apply drag
                    a._velocity.z() -= _g*_dt;

                    a._position += a._velocity*_dt;

                    // Detect particles that have
                    // hit the ground.

                    if (a._position.z()<0.0)
                    {
                        a._velocity.x() *=  _e;
                        a._velocity.y() *=  _e;
                        a._velocity.z() *= -_e;
                        a._position.z() = 0.0;

                        if (a._velocity.z()<0.001 && a._velocity==0.0)
                        {
                            a._velocity = Vector0;
                            a._expired = true;
                        }
                    }
                }

/*              // Fix particles that hit image

                int x = floor(a._position.x()*256/8.0);
                int y = floor(a._position.z()*256/8.0);

                if (x>=0 && y>=0 && x<256 && y<256)
                {
                    if ((byte &)(_image[x+y*256])>128)
                    {
                        a._fixed = true;
                        a._velocity = Vector0;
//                        a._expired = true;
                    }
                    else
                    {
                        a._fixed = false;
                    }
                }
*/
                break;
            }
    }

    system.updateAge(_dt);

    system._t += _dt;
    system._i++;
}

void
EngineProjectile::print(ostream &os) const
{
    os << "g:            " << _g << endl;
    os << "e:            " << _e << endl;
    os << "b:            " << _b << endl;
    os << endl;

    Integrator::print(os);
}

GltFieldPtr
EngineProjectile::settings()
{
    GltFields *root = new GltFields("projectile");
    root->merge(Integrator::settings());
    root->add(_g,0.1,"g");
    root->add(_e,0.1,"e");
    root->add(_b,0.1,"b");
    return root;
}
