#ifndef GRIPS_PLOT_H
#define GRIPS_PLOT_H

#include <math/vector3.h>
#include <node/field.h>

#include <string>

#include "engine.h"

class Plot : public Engine
{
public:
    Plot();
    ~Plot();

    void update(ParticleSystem &system) const;

    GltFieldPtr settings();

private:

    typedef enum
    {
        PLOT_X,
        PLOT_Y,
        PLOT_Z,

        PLOT_XY,
        PLOT_XYZ,

        PLOT_MAX

    } PlotMode;

    bool     _enable;
    PlotMode _mode;
    int      _particle;

    //

    static const std::string _plotModeDescription[PLOT_MAX];
};

#endif
