#ifndef NBODY_H
#define NBODY_H

#error OBSOLETE

#include <list>
#include <iosfwd>

#include <math/vector3.h>
#include <math/bbox.h>
#include <misc/refcount.h>
#include <node/field.h>

#include "particle.h"
//#include "gfield.h"

typedef ReferenceCountPtr<Particle> ParticlePtr;

class System
{
public:
    System();
    ~System();

    //
    // Generic Interface
    //

    virtual void   update() = 0;

    virtual void   print(std::ostream &os) const;

    virtual Vector field(const Vector &x) const;
    virtual bool   boundingBox(Vector &min,Vector &max,const double f) const;
    virtual bool   boundingBox(Vector &min,Vector &max,const double f,const Particle &body) const;

    virtual GltFieldPtr settings();

    //
    //
    //

    Particle &push_front();
    Particle &push_back();

    // Access particles

    typedef std::list<ParticlePtr>::iterator        iterator;
    typedef std::list<ParticlePtr>::const_iterator  const_iterator;

    const int   size() const;

    iterator    begin();
    iterator    end();

    const_iterator  begin() const;
    const_iterator  end()   const;

    Particle &front();
    Particle &back();

    const Particle &front() const;
    const Particle &back()  const;

    // Dereference iterator

    static       Particle &body(iterator       &i);
    static const Particle &body(const_iterator &i);

    //
    //
    //

    typedef enum
    {
        INTEGRATE_EULER = 0,
        INTEGRATE_EULER_CROMER,
        INTEGRATE_MIDPOINT,

        INTEGRATE_MAX

    } Integrator;

    //
    // Configuration
    //

    Integrator        _integrator;      // Type of integrator
    double            _dt;              // Time increment
    int               _trailSize;       // Trail size

    // Optional

    BoundingBox       _boundingBox;     // Bounding box

    //
    // Derived information
    //

    double            _t;               // Elapsed time (cumulative sum of _dt)
    int               _i;               // Number of iterations
    Vector            _centerOfMass;    // Updated by calcCenterOfMass

    //

    static const std::string _integratorDescription[INTEGRATE_MAX];

protected:

    Vector centerOfMass() const;
    void updateTrails();
    void updateAge(const double dt);
    void flushExpired();

private:

    std::list<ParticlePtr> _body;   // Container of particles
};

#endif
