#ifndef GRIPS_PROJECT_H
#define GRIPS_PROJECT_H

#include <iosfwd>
#include <string>
#include "integrat.h"

class EngineProjectile : public Integrator
{
public:
             EngineProjectile();
    virtual ~EngineProjectile();

    void        update(ParticleSystem &) const;

    void        print(std::ostream &os) const;
    GltFieldPtr settings();

protected:

    double _g;          // Gravitational constant, 9.8 by default
    double _e;          // Energy preserved after bounce
    double _b;          // Drag co-efficient

    std::string _image;
};

#endif
