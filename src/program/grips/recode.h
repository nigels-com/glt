#ifndef GRIPS_RECODE_H
#define GRIPS_RECODE_H

#include "integrat.h"

#include <glt/color.h>

class Particle;
class GltShape;
class BoundingBox;

class EngineRecode : public Integrator
{
public:
    EngineRecode();
    ~EngineRecode();

    void        update(ParticleSystem &) const;

    void        print(std::ostream &os) const;
    GltFieldPtr settings();

protected:

    bool recode(ParticleSystem &system) const;
//  bool recode(const Particle &a,const Particle &b) const;
    bool recode(const GltShape &a,const GltShape &b,const BoundingBox &box) const;

    double          _e;             // Constant of restitution
    bool            _collision;     // Do collision checking

    bool            _colorCode;
    GltColor        _wallImpact;
    GltColor        _ballImpact;
};

#endif
