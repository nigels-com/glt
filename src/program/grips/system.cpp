#include "system.h"

#error OBSOLETE

#include <misc/string.h>
#include <node/fields.h>

using namespace std;

const string System::_integratorDescription[INTEGRATE_MAX] =
{
    "Euler",
    "Euler-Cromer",
    "Midpoint"
};

System::System()
:
    _dt(1.0),
    _integrator(INTEGRATE_EULER_CROMER),
    _trailSize(16),
    _t(0.0),
    _i(0)
{
}

System::~System()
{
}

/////////////////////////////////////////////////////////

Particle &
System::push_front()
{
    _body.push_front(new Particle());
    return front();
}

Particle &
System::push_back()
{
    _body.push_back(new Particle());
    return back();
}

const int System::size() const { return _body.size();  }

System::iterator System::begin() { return _body.begin(); }
System::iterator System::end()   { return _body.end();   }

System::const_iterator System::begin() const { return _body.begin(); }
System::const_iterator System::end()   const { return _body.end();   }

Particle &System::front() { return *_body.front(); }
Particle &System::back()  { return *_body.back();  }

const Particle &System::front() const { return *_body.front(); }
const Particle &System::back()  const { return *_body.back();  }

      Particle &System::body(System::iterator       &i) { return *(i->get()); }
const Particle &System::body(System::const_iterator &i) { return *(i->get()); }

/////////////////////////////////////////////////////////

Vector
System::field(const Vector &x) const
{
    return Vector0;
}

Vector
System::centerOfMass() const
{
    Vector pos;
    double mass = 0.0;

    for (const_iterator i=begin(); i!=end(); i++)
    {
        pos  += body(i)._mass * body(i)._position;
        mass += body(i)._mass;
    }

    if (mass>1e-4)
        return pos/mass;
    else
        return Vector0;
}

void
System::updateTrails()
{
    for (iterator i=begin(); i!=end(); i++)
    {
        Particle &p = body(i);
        p._trail.resize(_trailSize);
        if (!p._fixed && !p._expired)
            p._trail.push(p._position);
    }
}

void
System::updateAge(const double dt)
{
        for (iterator i=begin(); i!=end(); i++)
            body(i)._age += dt;
}

void
System::flushExpired()
{
    // Erase all particles marked expired

    for (iterator i=begin(); i!=end(); )
        if (i->get()->_expired)
             i = _body.erase(i);
        else
            i++;
}

bool
System::boundingBox(Vector &min,Vector &max,const double f,const Particle &body) const
{
    return false;
}

bool
System::boundingBox(Vector &min,Vector &max,const double f) const
{
    if (size()==0)
        return false;

    // Start with bounding box of first body

    const_iterator i = begin();

    if (!boundingBox(min,max,f,body(i)))
        return false;

    // Combine with bounding boxes of other bodies

    for (;i!=end(); i++)
    {
        Vector tmin,tmax;
        if (!boundingBox(tmin,tmax,f,body(i)))
            return false;

        min = min.vmin(tmin);
        max = max.vmax(tmax);
    }

    return true;
}

void
System::print(ostream &os) const
{
    os << "Time:         " << _t << endl;
    os << "Time step:    " << _dt << endl;
    os << "Iterations:   " << _i  << endl;
    os << "Integrator:   " << _integratorDescription[_integrator] << endl;
    os << "Bodies:       " << _body.size() << endl;
    os << "CenterOfMass: "; printVec(os,_centerOfMass) << endl;
    os << endl;
}

GltFieldPtr
System::settings()
{
    GltFields *root = new GltFields("system","System Settings");
    root->add((int &) _integrator,INTEGRATE_MAX,_integratorDescription,"integrator");
    root->add(_dt       ,0.01,"step"     );
    root->add(_trailSize,     "trailSize");
    return root;
}

