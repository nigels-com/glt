#ifndef GRIPS_RAIN_H
#define GRIPS_RAIN_H

#include <math/vector3.h>
#include <node/field.h>

#include "engine.h"

class Rain : public Engine
{
public:
    Rain();
    ~Rain();

    void update(ParticleSystem &system) const;

    GltFieldPtr settings();

private:
    bool    _enable;
    double  _lifetime;
    Vector  _min;
    Vector  _max;
};

// Spray particles from a point

class Fountain : public Engine
{
public:
    Fountain();
    ~Fountain();

    void update(ParticleSystem &system) const;

    GltFieldPtr settings();

private:
    bool    _enable;
    double  _lifetime;
    Vector  _position;
    Vector  _direction;
    double  _angle;
};

// Spray particles from a line

class LineSpray : public Engine
{
public:
    LineSpray();
    ~LineSpray();

    void update(ParticleSystem &system) const;

    GltFieldPtr settings();

private:
    bool    _enable;
    double  _lifetime;
    Vector  _a;
    Vector  _b;
    Vector  _direction;
    double  _angle;
};

// Spray particles from first particle

class Exhaust : public Engine
{
public:
    Exhaust();
    ~Exhaust();

    void update(ParticleSystem &system) const;

    GltFieldPtr settings();

private:
    bool    _enable;
    double  _lifetime;
    double  _speed;
    double  _angle;
};

#endif
