#ifndef GRID_H
#define GRID_H

#include <glt/color.h>
#include <node/fields.h>
#include <node/shape.h>

/////////////////////////////////////

class GltGrid : public GltShape
{
public:
    GltGrid();
    ~GltGrid();

    virtual void draw() const;

    void drawQuad() const;

    GltFieldPtr settings();

protected:

    GltColor _axesColor;
    GltColor _majorColor;
    GltColor _minorColor;

    Vector3  _origin;
    Vector3  _right;
    Vector3  _up;

    real     _rightStepMajor;
    uint32   _rightStepMinor;

    real     _upStepMajor;
    uint32   _upStepMinor;
};


#endif
