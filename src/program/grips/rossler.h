#pragma once

#include "integrat.h"

class EngineRossler : public Integrator
{
public:
    EngineRossler();
    ~EngineRossler();

    void        update(ParticleSystem &) const;

    Vector      field(const ParticleSystem &,const Vector &) const;
    void        print(std::ostream &os) const;
    GltFieldPtr settings();

protected:

    double _a,_b,_c;
};
