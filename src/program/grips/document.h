#ifndef GRIPS_DOCUMENT_H
#define GRIPS_DOCUMENT_H

#include "gravity.h"
#include "lorenz.h"
#include "rossler.h"
#include "project.h"
#include "hockey.h"
#include "recode.h"

#include "psystem.h"

#include "init.h"
#include "field.h"
#include "rain.h"
#include "video.h"
#include "colmap.h"
#include "fade.h"
#include "plot.h"

#include <math/vector3.h>
#include <node/field.h>
#include <node/histogrm.h>

class Document : public GltSubject /* , public GltObserver<ParticleSystem> */
{
public:
    Document();
    ~Document();

    void init();
    void iterate(const int steps = 1);

    //

    GltFieldPtr      settings();

          ParticleSystem &particles();
    const ParticleSystem &particles() const;

          Integrator     *integrator();
    const Integrator     *integrator() const;

    //

//  void OnNotify(const ParticleSystem *system);

    //

    typedef enum
    {
        SYSTEM_NONE = 0,
        SYSTEM_GRAVITY,
        SYSTEM_LORENZ,
        SYSTEM_ROSSLER,
        SYSTEM_PROJECTILE,
        SYSTEM_HOCKEY,
        SYSTEM_RECODE,
        SYSTEM_MAX
    } IntegratorType;

    static std::string _integratorTypeDescription[SYSTEM_MAX];

private:

    // Defaults for initialised particles

    class ParticleDefaults
    {
    public:
        ParticleDefaults();

        // Initial defaults

        double     mass;
        double     radius;
        double     age;
        Vector     position;
        Vector     velocity;
        Vector     acceleration;
        bool       fixed;
        bool       expired;
        GltColor   color;
    };

    // Initialisation options, including particle defaults
    // and randomised placement & velocities

    class InitOptions
    {
    public:
        InitOptions();

        int                 n;
        ParticleDefaults    defaults;
    };

    //

    ParticleSystem         _particles;

    // Integrators

    IntegratorType         _integrator;

    EngineGravity          _gravity;
    EngineLorenz           _lorenz;
    EngineRossler          _rossler;
    EngineProjectile       _projectile;
    EngineHockey           _hockey;
    EngineRecode           _recode;

    // Initialisation Engines

    InitPosition _initPosition;
    InitVelocity _initVelocity;
    InitColor    _initColor;

    // Other Engines

    TrailUpdate _trailUpdate;
    Rain        _rain;
    Fountain    _fountain;
    LineSpray   _lineSpray;
    Exhaust     _exhaust;
    ColorMap    _colmap;
    Fade        _fade;
    Plot        _plot;

    //

    InitOptions _init;

    double      _maxTime;

public:

    Video       _video;

    // Histograms

    GltHistogram _histogramVx;
    GltHistogram _histogramVy;
    GltHistogram _histogramVz;
    GltHistogram _histogramSpeed;
};

#endif
