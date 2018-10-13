#pragma once

#include "integrat.h"

#include <glt/color.h>

class EngineHockey : public Integrator
{
public:
    EngineHockey();
    ~EngineHockey();

    void        update(ParticleSystem &) const;

    void        print(std::ostream &os) const;
    GltFieldPtr settings();

protected:

    double          _e;            // Constant of restitution
    bool            _collision;     // Do collision checking

    bool            _colorCode;
    GltColor        _wallImpact;
    GltColor        _ballImpact;
};
