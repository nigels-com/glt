#include "document.h"

#include <math/random.h>
#include <glt/rgb.h>

using namespace std;

Document::ParticleDefaults::ParticleDefaults()
:
    mass(1.0),
    radius(1.0),
    age(0.0),
    position(Vector0),
    velocity(Vector0),
    acceleration(Vector0),
    fixed(false),
    expired(false),
    color(white)
{
}

Document::InitOptions::InitOptions()
:
    n(100)
{
}

string Document::_integratorTypeDescription[SYSTEM_MAX] =
{
    "None",
    "Gravity",
    "Lorenz",
    "Rossler",
    "Projectile",
    "Hockey",
    "Recode"
};

///////////////

Document::Document()
:
    _integrator(SYSTEM_NONE),
    _maxTime(0.0)
{
    // Initialise histograms

    _histogramVx.min()  = _histogramVy.min()  = _histogramVz.min() = -2.0;
    _histogramVx.max()  = _histogramVy.max()  = _histogramVz.max() =  2.0;
    _histogramVx.size() = _histogramVy.size() = _histogramVz.size() = 50;

    _histogramVx.color() = red;
    _histogramVy.color() = green;
    _histogramVz.color() = blue;

    _histogramSpeed.min()  = 0.0;
    _histogramSpeed.max()  = 4.0;
    _histogramSpeed.size() = 50;
    _histogramSpeed.color() = grey;

    _histogramVx.name() = "xvelocity";
    _histogramVy.name() = "yvelocity";
    _histogramVz.name() = "zvelocity";
    _histogramSpeed.name () = "speed";
}

Document::~Document()
{
}

      ParticleSystem &Document::particles()        { return _particles;  }
const ParticleSystem &Document::particles()  const { return _particles;  }

Integrator *
Document::integrator()
{
    switch (_integrator)
    {
        case SYSTEM_GRAVITY:    return &_gravity;
        case SYSTEM_LORENZ:     return &_lorenz;
        case SYSTEM_ROSSLER:    return &_rossler;
        case SYSTEM_PROJECTILE: return &_projectile;
        case SYSTEM_HOCKEY:     return &_hockey;
        case SYSTEM_RECODE:     return &_recode;
        default:                return NULL;
    }
}

const Integrator *
Document::integrator() const
{
    switch (_integrator)
    {
        case SYSTEM_GRAVITY:    return &_gravity;
        case SYSTEM_LORENZ:     return &_lorenz;
        case SYSTEM_ROSSLER:    return &_rossler;
        case SYSTEM_PROJECTILE: return &_projectile;
        case SYSTEM_HOCKEY:     return &_hockey;
        case SYSTEM_RECODE:     return &_recode;
        default:                return NULL;
    }
}

GltFieldPtr
Document::settings()
{
    GltFields *root = new GltFields("world");

            GltFields *defaults = new GltFields("defaults");
            defaults->add(_init.defaults.mass  ,0.1,   "mass"        );
            defaults->add(_init.defaults.radius,0.1,   "radius"      );
            defaults->add(_init.defaults.age   ,0.1,   "age"         );
            defaults->add(_init.defaults.position,     "position"    );
            defaults->add(_init.defaults.velocity,     "velocity"    );
            defaults->add(_init.defaults.acceleration, "acceleration");
            defaults->add(_init.defaults.fixed,        "fixed"       );
            defaults->add(_init.defaults.expired,      "expired"     );
            defaults->add(_init.defaults.color,        "color"       );

        GltFields *init = new GltFields("init");
        init->add(_init.n,           "n"     );
        init->add(defaults);
        init->add(_initPosition.settings());
        init->add(_initVelocity.settings());
        init->add(_initColor.settings());
        init->add(new GltFieldFunc<Document>(*this,&Document::init,"init",true));

        GltFields *histogram = new GltFields("histogram");
        histogram->add(_histogramVx.settings());
        histogram->add(_histogramVy.settings());
        histogram->add(_histogramVz.settings());
        histogram->add(_histogramSpeed.settings());

    root->add((int &)_integrator,SYSTEM_MAX,_integratorTypeDescription,"integrator");
    root->add(_gravity.settings());
    root->add(_lorenz.settings());
    root->add(_rossler.settings());
    root->add(_projectile.settings());
    root->add(_hockey.settings());
    root->add(_recode.settings());

    root->add(_rain.settings());
    root->add(_fountain.settings());
    root->add(_lineSpray.settings());
    root->add(_exhaust.settings());
    root->add(_video.settings());
    root->add(_colmap.settings());
    root->add(_fade.settings());
    root->add(_plot.settings());

    root->add(_trailUpdate.settings());
    root->add(histogram);

    root->add(init);
    root->add(_particles.settings());

    return root;
}

void
Document::init()
{
    _particles.reset();

    _particles.resize(_init.n);

    for (ParticleSystem::iterator i=_particles.begin(); i!=_particles.end(); i++)
    {
        Particle &p = *i;
        p._mass         = _init.defaults.mass;
        p._radius       = _init.defaults.radius;
        p._age          = _init.defaults.age;
        p._position     = _init.defaults.position;
        p._velocity     = _init.defaults.velocity;
        p._acceleration = _init.defaults.acceleration;
        p._fixed        = _init.defaults.fixed;
        p._expired      = _init.defaults.expired;
        p._color        = _init.defaults.color;
    }

    //

    _initPosition.update(_particles);
    _initVelocity.update(_particles);
    _initColor.update(_particles);

    NOTIFY;
}

void
Document::iterate(const int steps)
{
    Integrator *current = integrator();

    if (current)
    {
        for (int i=0; i<steps; i++)
        {
            current->update(_particles);
            _trailUpdate.update(_particles);
            _rain       .update(_particles);
            _fountain   .update(_particles);
            _lineSpray  .update(_particles);
            _exhaust    .update(_particles);
            _video      .update(_particles);
            _plot       .update(_particles);

            if (!_histogramVx.cumulative())
                _histogramVx.reset();

            if (!_histogramVy.cumulative())
                _histogramVy.reset();

            if (!_histogramVz.cumulative())
                _histogramVz.reset();

            if (!_histogramSpeed.cumulative())
                _histogramSpeed.reset();

            for (ParticleSystem::iterator j=_particles.begin(); j!=_particles.end(); j++)
            {
                _histogramVx.add(j->_velocity.x());
                _histogramVy.add(j->_velocity.y());
                _histogramVz.add(j->_velocity.z());
                _histogramSpeed.add(j->_velocity.length());
            }
        }

        _colmap.update(_particles);
        _fade.update(_particles);
    }
}

