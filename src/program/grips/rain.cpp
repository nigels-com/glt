#include "rain.h"
#include "psystem.h"

#include <math/random.h>
#include <node/fields.h>

Rain::Rain()
: _enable(false),
  _lifetime(0.0),
  _min(-Vector1),
  _max(Vector1)
{
}

Rain::~Rain()
{
}

void
Rain::update(ParticleSystem &system) const
{
    GltRandomDouble<GltRandomLFSRMix> rx(_min.x(),_max.x());
    GltRandomDouble<GltRandomLFSRMix> ry(_min.y(),_max.y());
    GltRandomDouble<GltRandomLFSRMix> rz(_min.z(),_max.z());
    GltRandomDouble<GltRandomLFSRMix> ra(0,_lifetime);

    if (_enable)
        for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
        {
            Particle &p = *i;

            if (p._age>p._ageLimit || p._expired)
            {
                p._position = Vector(rx.rand(),ry.rand(),rz.rand());
                p._velocity = Vector0;
                p._acceleration = Vector0;
                p._trail.clear();
                p._age = ra.rand();
                p._expired = false;
                p._fixed = false;
            }
        }
}

GltFieldPtr
Rain::settings()
{
    GltFields *root = new GltFields("rain");
    root->add(_enable,       "enable");
    root->add(_lifetime,0.25,"lifetime");
    root->add(_min,          "min");
    root->add(_max,          "max");
    return root;
}

//////////////////////////////////////////////////////

Fountain::Fountain()
: _enable(false),
  _lifetime(0.0),
  _position(Vector0),
  _direction(VectorY),
  _angle(45.0)
{
}

Fountain::~Fountain()
{
}

void
Fountain::update(ParticleSystem &system) const
{
    GltRandomDouble<GltRandomLFSRMix> rot1(-_angle,_angle);
    GltRandomDouble<GltRandomLFSRMix> rot2(0.0,360.0);

    GltRandomDouble<GltRandomLFSRMix> ra(0,_lifetime);

    if (_enable)
        for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
        {
            Particle &p = *i;

            if (p._age>p._ageLimit || p._expired)
            {
                p._position = _position;
                p._velocity = _direction;
                p._velocity *= matrixRotate(VectorX,rot1.rand());
                p._velocity *= matrixRotate(_direction,rot2.rand());
                p._acceleration = Vector0;
                p._trail.clear();
                p._age = 0.0;
                p._ageLimit = ra.rand();
                p._expired = false;
                p._fixed = false;
            }
        }
}

GltFieldPtr
Fountain::settings()
{
    GltFields *root = new GltFields("fountain");
    root->add(_enable,       "enable");
    root->add(_lifetime,0.25,"lifetime");
    root->add(_position,     "position");
    root->add(_direction,    "direction");
    root->add(_angle,        "angle");
    return root;
}

////////////////////////

LineSpray::LineSpray()
: _enable(false),
  _lifetime(0.0),
  _a(Vector0),
  _b(VectorX),
  _direction(VectorZ),
  _angle(10.0)
{
}

LineSpray::~LineSpray()
{
}

void
LineSpray::update(ParticleSystem &system) const
{
    GltRandomDouble<GltRandomLFSRMix> t(0.0,1.0);
    GltRandomDouble<GltRandomLFSRMix> rot(-_angle,_angle);
    GltRandomDouble<GltRandomLFSRMix> ra(0,_lifetime);

    const Vector delta = _b-_a;

    if (_enable)
        for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
        {
            Particle &p = *i;

            if (p._age>p._ageLimit || p._expired)
            {
                p._position = _a + delta*t.rand();
                p._velocity = _direction;
                p._velocity *= matrixRotate(delta,rot.rand());
                p._acceleration = Vector0;
                p._trail.clear();
                p._age = 0.0;
                p._ageLimit = ra.rand();
                p._expired = false;
                p._fixed = false;
            }
        }
}

GltFieldPtr
LineSpray::settings()
{
    GltFields *root = new GltFields("lineSpray");
    root->add(_enable,       "enable");
    root->add(_lifetime,0.25,"lifetime");
    root->add(_a,            "a");
    root->add(_b,            "b");
    root->add(_direction,    "direction");
    root->add(_angle,        "angle");
    return root;
}

//////////////////////////////

Exhaust::Exhaust()
: _enable(false),
  _lifetime(0.0),
  _speed(0.0),
  _angle(10.0)
{
}

Exhaust::~Exhaust()
{
}

void
Exhaust::update(ParticleSystem &system) const
{
    GltRandomDouble<GltRandomLFSRMix> t(0.0,1.0);
    GltRandomDouble<GltRandomLFSRMix> rot1(-_angle,_angle);
    GltRandomDouble<GltRandomLFSRMix> rot2(0.0,360.0);
    GltRandomDouble<GltRandomLFSRMix> ra(0,_lifetime);

    if (_enable)
    {
        ParticleSystem::iterator i=system.begin();
        Particle &src = *i;
        i++;

        if (i!=system.end() && !i->_expired)
        {
            src._age = 0.0;

            for (; i!=system.end(); i++)
            {
                Particle &p = *i;

                if (p._age>p._ageLimit || p._expired)
                {
                    // Create frame of reference
                    // w.r.t velocity

                    Vector a,b,c;
                    a = src._velocity;
                    orthogonalSystem(a,b,c);

                    //

                    p._position = src._position;
                    p._velocity = src._velocity*_speed;
                    p._velocity *= matrixRotate(b,rot1.rand());
                    p._velocity *= matrixRotate(a,rot2.rand());
                    p._acceleration = Vector0;
                    p._trail.clear();
                    p._age = 0.0;
                    p._ageLimit = ra.rand();
                    p._expired = false;
                    p._fixed = false;
                }
            }
        }
    }
}

GltFieldPtr
Exhaust::settings()
{
    GltFields *root = new GltFields("exhaust");
    root->add(_enable,       "enable");
    root->add(_lifetime,0.25,"lifetime");
    root->add(_speed,        "speed");
    root->add(_angle,        "angle");
    return root;
}

