#ifndef GRIPS_FIELD_H
#define GRIPS_FIELD_H

#include <glt/color.h>
#include <node/field.h>

class ParticleSystem;
class Integrator;

class Field
{
public:

    Field(const double size,const double min,const double max);
    ~Field();

    void draw(const ParticleSystem &system,const Integrator &engine) const;

    GltFieldPtr settings();

private:

    bool    _enable;        //
    double  _size;          // Grid spacing
    int     _n;             // Maximum number of lines
    double  _min;           // Minimum force, must be nonzero
    double  _max;           // Maximum force, larger forces are clamped

    GltColor _color1;        // Color
    GltColor _color2;        // Color
};

#endif

