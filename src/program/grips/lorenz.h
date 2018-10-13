#pragma once

#include "integrat.h"

class EngineLorenz : public Integrator
{
public:
    EngineLorenz();
    ~EngineLorenz();

    void        update(ParticleSystem &) const;

    Vector      field(const ParticleSystem &,const Vector &) const;
    void        print(std::ostream &os) const;
    GltFieldPtr settings();

protected:

    double _r;  // constant parameter
};
