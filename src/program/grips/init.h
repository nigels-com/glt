#ifndef GRIPS_INIT_H
#define GRIPS_INIT_H

#include "engine.h"

#include <math/vector3.h>
#include <glt/color.h>

class InitPosition : public Engine
{
public:
    InitPosition();
    ~InitPosition();

    void update(ParticleSystem &) const;

    GltFieldPtr settings();

protected:

    static bool initLine  (ParticleSystem &system,const Vector &a,const Vector &b);
    static bool initGrid  (ParticleSystem &system,const Vector &a,const Vector &b);
    static bool initBox   (ParticleSystem &system,const Vector &a,const Vector &b);
    static bool initCircle(ParticleSystem &system,const Vector &a,const double radius);
    static bool initDisk  (ParticleSystem &system,const Vector &a,const double radius);
    static bool initSphere(ParticleSystem &system,const Vector &a,const double radius);

    class InitPositionOptions
    {
    public:
        InitPositionOptions();

        bool       line;
        bool       box;
        bool       circle;
        bool       disk;
        bool       sphere;
        Vector     a;
        Vector     b;
        double     radius;
        int        seed;
    };

    InitPositionOptions _options;
};


class InitVelocity : public Engine
{
public:
    InitVelocity();
    ~InitVelocity();

    void update(ParticleSystem &) const;

    GltFieldPtr settings();

protected:

    static bool initVelocityCircular (ParticleSystem &system,const double speed);
    static bool initVelocitySpherical(ParticleSystem &system,const double speed);

    class InitVelocityOptions
    {
    public:
        InitVelocityOptions();

        bool       circular;
        bool       spherical;
        double     speed;
        int        seed;
    };

    InitVelocityOptions _options;
};

class InitColor : public Engine
{
public:
    InitColor();
    ~InitColor();

    void update(ParticleSystem &) const;

    GltFieldPtr settings();

protected:

    static bool initColorBlend(ParticleSystem &system,const GltColor &a,const GltColor &b);
    static bool initColorBlend(ParticleSystem &system,const GltColor &a,const GltColor &b,const GltColor &c);

    class InitColorOptions
    {
    public:
        InitColorOptions();

        bool blend;
        bool blend3;
        GltColor a;
        GltColor b;
        GltColor c;
    };

    InitColorOptions _options;
};

#endif

