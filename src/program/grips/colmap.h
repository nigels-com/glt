#ifndef GRIPS_COLMAP_H
#define GRIPS_COLMAP_H

#include <string>

#include <glt/colmap.h>
#include <node/field.h>

#include "engine.h"

class ColorMap : public Engine
{
public:
    ColorMap();
    ~ColorMap();

    void update(ParticleSystem &system) const;

    GltFieldPtr settings();

private:

    typedef enum
    {
        MAPPING_NONE = 0,
        MAPPING_SPEED,
        MAPPING_ACCEL,
        MAPPING_AGE,
        MAPPING_XPLANE,
        MAPPING_INDEX,
        MAPPING_LINE,
        MAPPING_MAX
    } MappingMode;

    static const std::string _modeDescription[MAPPING_MAX];

    typedef enum
    {
        COLOR_SCHEME_BLUE_RED = 0,
        COLOR_SCHEME_WHITE_TRANS,
        COLOR_SCHEME_RED_WHITE_BLUE,
        COLOR_SCHEME_MAX
    } ColorScheme;

    static const std::string _schemeDescription[COLOR_SCHEME_MAX];

    MappingMode _mode;
    ColorScheme _scheme;
    double      _min,_max;

    GltColorMap _map[COLOR_SCHEME_MAX];
};

#endif

