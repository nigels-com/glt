#pragma once

#include <vector>

#include <node/field.h>
#include <misc/observer.h>

#include "particle.h"

class BoundingBox;
class Vector3;

class ParticleSystem : public GltSubject
{
public:
    ParticleSystem();
    ~ParticleSystem();

    //
    // Fields
    //

    GltFieldPtr settings();

    //
    // Extract information
    //

    Vector3 centerOfMass() const;

    //
    // Manipulate container
    //

    void resize(const int size);
    void reset();
    void resetTrails();
    void updateAge(const double dt);

    //
    // Access container
    //

    typedef std::vector<Particle>::iterator       iterator;
    typedef std::vector<Particle>::const_iterator const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const int size() const;

          Particle &operator[](const int n);
    const Particle &operator[](const int n) const;

    //
    // Derived information
    //

    double            _t;               // Elapsed time (cumulative sum of _dt)
    int               _i;               // Number of iterations

private:

    std::vector<Particle> _particle;        // Container of particles
};
