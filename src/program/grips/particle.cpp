#include "particle.h"

#include <glt/rgb.h>
#include <node/fields.h>

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

Particle::Particle()
:
    _mass(0.0),
    _radius(1.0),
    _age(0.0),
    _ageLimit(0.0),
    _position(Vector0),
    _velocity(Vector0),
    _acceleration(Vector0),
    _visible(true),
    _fixed(false),
    _expired(false),
    _color(white)
{
    _trail.resize(100);
}

Particle::~Particle()
{
}

ostream &printVec(ostream &os,const Vector &v)
{
    os << "[ ";
    os << setw(8) << v.x() << ' ';
    os << setw(8) << v.y() << ' ';
    os << setw(8) << v.z();
    os << " ]";

    return os;
}

GltFieldPtr
Particle::settings()
{
    GltFields *root = new GltFields("particle");
    root->add(_mass        ,"mass");
    root->add(_radius      ,"radius");
    root->add(_age         ,"age");
    root->add(_ageLimit    ,"ageLimit");
    root->add(_position    ,"position");
    root->add(_velocity    ,"velocity");
    root->add(_acceleration,"acceleration");
    root->add(_visible     ,"visible");
    root->add(_fixed,       "fixed");
    root->add(_expired,     "expired");
    root->add(_color,       "color");
    root->add(_trail.settings());

    return root;
}

ostream &operator<<(ostream &os,const Particle &body)
{
    if (body._name.size())
        os << body._name << endl;

    os << "Mass:         " << body._mass                    << endl;
    os << "Position:     "; printVec(os,body._position)     << endl;
    os << "Velocity:     "; printVec(os,body._velocity)     << ' ' << setw(8) << body._velocity.length()     << endl;
    os << "Acceleration: "; printVec(os,body._acceleration) << ' ' << setw(8) << body._acceleration.length() << endl;

    return os;
}
