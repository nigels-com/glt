#pragma once

#include <node/field.h>
#include <glt/color.h>

#include "engine.h"

class ParticleSystem;

class Fade : public Engine
{
public:
    Fade();
    ~Fade();

    void update(ParticleSystem &system) const;

    GltFieldPtr settings();

private:

    bool        _enable;
    GltColor    _color;
};
