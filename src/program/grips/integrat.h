#ifndef GRIPS_INTEGRAT_H
#define GRIPS_INTEGRAT_H

#include <iosfwd>
#include <string>

#include <node/fields.h>
#include <math/bbox.h>

#include "engine.h"

class Vector3;
class Particle;
class ParticleSystem;

class Integrator : public Engine
{
public:
             Integrator();
    virtual ~Integrator();

    //
    //

    virtual Vector3 field(const ParticleSystem &,const Vector3 &) const;
    virtual void    boundingBox(BoundingBox &box,const ParticleSystem &,const double f) const;
    virtual void    boundingBox(BoundingBox &box,const ParticleSystem &,const double f,const Particle &body) const;

    virtual void   print(std::ostream &os) const;

    virtual GltFieldPtr settings();

    //
    // Integrator
    //

    typedef enum
    {
        INTEGRATE_EULER = 0,
        INTEGRATE_EULER_CROMER,
        INTEGRATE_MIDPOINT,

        INTEGRATE_MAX

    } IntegratorType;

    //
    // Configuration
    //

    IntegratorType    _integrator;      // Type of integrator
    double            _dt;          // Time increment
    BoundingBox       _boundingBox;     // World Limits

private:

    //

    static const std::string _integratorDescription[INTEGRATE_MAX];
};

#endif
