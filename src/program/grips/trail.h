#ifndef GRIPS_TRAIL_H
#define GRIPS_TRAIL_H

#include <math/vector3.h>
#include <node/shape.h>
#include <misc/cbuffer.h>

#include "engine.h"


class Trail : public GltShape, public cbuffer<Vector>
{
    friend class TrailUpdate;

public:

    Trail();
    ~Trail();

    void draw() const;

    GltFieldPtr settings();

private:

    real   _width;
    real   _alpha;
    Vector _normal;
    int    _skip;
};

class TrailUpdate : public Engine
{
public:
    TrailUpdate();
    ~TrailUpdate();

    void update(ParticleSystem &) const;

    GltFieldPtr settings();

private:

    int                   _size;       // Trail size

    bool  _overRide;
    Trail _trail;
};

#endif

