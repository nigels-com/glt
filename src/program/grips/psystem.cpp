#include "psystem.h"

#include <math/bbox.h>
#include <math/random.h>
#include <math/vector3.h>

#include <misc/stlutil.h>
#include <node/fields.h>

#include <cstdio>
using namespace std;

ParticleSystem::ParticleSystem()
: _t(0.0), _i(0)
{
    _particle.reserve(5);
}

ParticleSystem::~ParticleSystem()
{
}

//

GltFieldPtr
ParticleSystem::settings()
{
    GltFields *root = new GltFields("system");

    GltFields *particles = new GltFields("particles");
    for (int i=0; i<size(); i++)
    {
        char buffer[1024];
        sprintf(buffer,"%d",i);
        particles->add(_particle[i].settings(),buffer);
    }

    root->add(particles);
    root->add(new GltFieldFunc<ParticleSystem>(*this,&ParticleSystem::resetTrails,"resetTrails",true));

    return root;
}

void
ParticleSystem::resize(const int size)
{
    _particle.resize(size);
    shrink(_particle);
    notify(this);
}

void
ParticleSystem::reset()
{
    _particle.clear();
    shrink(_particle);
    notify(this);
}

Vector
ParticleSystem::centerOfMass() const
{
    Vector pos;
    double mass = 0.0;

    for (const_iterator i=begin(); i!=end(); i++)
    {
        const Particle &p = *i;
        pos  += p._mass * p._position;
        mass += p._mass;
    }

    if (mass>1e-4)
        return pos/mass;
    else
        return Vector0;
}

void
ParticleSystem::resetTrails()
{
    for (iterator i=begin(); i!=end(); i++)
        i->_trail.clear();
}

void
ParticleSystem::updateAge(const double dt)
{
    for (iterator i=begin(); i!=end(); i++)
        (*i)._age += dt;
}

ParticleSystem::iterator ParticleSystem::begin() { return _particle.begin(); }
ParticleSystem::iterator ParticleSystem::end()   { return _particle.end();   }

ParticleSystem::const_iterator ParticleSystem::begin() const { return _particle.begin(); }
ParticleSystem::const_iterator ParticleSystem::end()   const { return _particle.end();   }

const int ParticleSystem::size() const { return _particle.size(); }

const Particle &ParticleSystem::operator[](const int n) const
{
    assert(n>=0 && n<=size());
    return _particle[n];
}


Particle &ParticleSystem::operator[](const int n)
{
    assert(n>=0 && n<=size());
    return _particle[n];
}
