#ifndef GRIPS_ENGINE_H
#define GRIPS_ENGINE_H

#include <node/fields.h>

class ParticleSystem;

class Engine
{
public:
             Engine();
    virtual ~Engine();

    //
    // Iterate
    //

    virtual void update(ParticleSystem &) const = 0;

    virtual GltFieldPtr settings() = 0;
};

#endif
