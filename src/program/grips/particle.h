#pragma once

#include <string>
#include <iosfwd>

#include <node/shapes.h>
#include <node/field.h>
#include <math/vector3.h>
#include <glt/color.h>

#include "trail.h"

class Particle
{
public:
    Particle();
    ~Particle();

    std::string _name;
    double      _mass;
    double      _radius;
    double      _age;
    double      _ageLimit;
    Vector      _position;
    Vector      _velocity;
    Vector      _acceleration;
    bool        _visible;
    bool        _fixed;
    bool        _expired;

    //
    //

    GltColor    _color;
    Trail       _trail;

    //

    GltFieldPtr      settings();

    //

    static bool read (std::istream &is,      Particle &body);
    static bool write(std::ostream &os,const Particle &body);

    //
    //

    friend std::ostream &operator<<(std::ostream &os,const Particle &body);
};

extern std::ostream &printVec(std::ostream &os,const Vector &v);
