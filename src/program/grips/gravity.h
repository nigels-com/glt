#ifndef GRIPS_GRAVITY_H
#define GRIPS_GRAVITY_H

#include "integrat.h"

class EngineGravity : public Integrator
{
public:
    EngineGravity();
    ~EngineGravity();

    void        update(ParticleSystem &)  const;

    Vector      field(const ParticleSystem &,const Vector &) const;
    void        boundingBox(BoundingBox &box,const ParticleSystem &,const double f) const;
    void        boundingBox(BoundingBox &box,const ParticleSystem &,const double f,const Particle &p) const;
    void        print(std::ostream &os) const;
    GltFieldPtr settings();

protected:

    double _Grav;                   // Gravitational constant, 1.0 by default
};

#endif
