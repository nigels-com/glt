#include "grid.h"

#include <glt/gl.h>
#include <glt/rgb.h>
#include <glt/error.h>

//////////////////////

GltGrid::GltGrid()
:
    _axesColor(white),
    _majorColor(cyan),
    _minorColor(darkBlue),

    _origin(Vector0),
    _right(VectorX),
    _up(VectorY),

    _rightStepMajor(1.0),
    _rightStepMinor(5),
    _upStepMajor(1.0),
    _upStepMinor(5)
{
    color() = Vector1*0.05;
}

GltGrid::~GltGrid()
{
}

void GltGrid::drawQuad() const
{
    glPushMatrix();

        transformation().glMultMatrix();
        glBegin(GL_QUADS);
            _origin.glVertex();
            (_origin+_right).glVertex();
            (_origin+_right+_up).glVertex();
            (_origin+_up).glVertex();
        glEnd();

    glPopMatrix();
}

void GltGrid::draw() const
{
    const real tol = 1e-3;

    if (!visible() || _rightStepMajor<tol || _upStepMajor<tol)
        return;

    GLERROR;

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

        transformation().glMultMatrix();

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_CULL_FACE);

        glBegin(GL_QUADS);

            glColor();
            _origin.glVertex();
            (_origin+_right).glVertex();
            (_origin+_right+_up).glVertex();
            (_origin+_up).glVertex();
        glEnd();

        glBegin(GL_LINES);


            // Draw minor lines

            _minorColor.glColor();

            if (_rightStepMinor>1)
            {
                      Vector pos1   = _origin;
                      Vector pos2   = _origin+_up;
                const real   length = _right.length();
                const Vector delta  = _right/(length/_rightStepMajor*_rightStepMinor);
                const uint32 n      = (uint32) floor(length/_rightStepMajor*_rightStepMinor);

                for (uint32 i=0; i<=n; i++, pos1 += delta, pos2 += delta)
                    if (i%_rightStepMinor)
                    {
                        pos1.glVertex();
                        pos2.glVertex();
                    }
            }

            if (_upStepMinor>1)
            {
                      Vector pos1   = _origin;
                      Vector pos2   = _origin+_right;
                const real   length = _up.length();
                const Vector delta  = _up/(length/_upStepMajor*_upStepMinor);
                const uint32 n      = (uint32) floor(length/_upStepMajor*_upStepMinor);

                for (uint32 i=0; i<=n; i++, pos1 += delta, pos2 += delta)
                    if (i%_upStepMinor)
                    {
                        pos1.glVertex();
                        pos2.glVertex();
                    }
            }

            // Draw major lines

            _majorColor.glColor();

            {
                      Vector pos1   = _origin;
                      Vector pos2   = _origin+_up;
                const real   length = _right.length();
                const Vector delta  = _right/(length/_rightStepMajor);
                const uint32 n      = (uint32) floor(length/_rightStepMajor+tol);

                for (uint32 i=0; i<=n; i++, pos1 += delta, pos2 += delta)
                    if (i>0)
                    {
                        pos1.glVertex();
                        pos2.glVertex();
                    }
            }

            {
                      Vector pos1   = _origin;
                      Vector pos2   = _origin+_right;
                const real   length = _up.length();
                const Vector delta  = _up/(length/_upStepMajor);
                const uint32 n      = (uint32) floor(length/_upStepMajor+tol);

                for (uint32 i=0; i<=n; i++, pos1 += delta, pos2 += delta)
                    if (i>0)
                    {
                        pos1.glVertex();
                        pos2.glVertex();
                    }
            }

            // Draw axes, if necessary

            _axesColor.glColor();
             _origin        .glVertex();
            (_origin+_right).glVertex();
             _origin        .glVertex();
            (_origin+_up)   .glVertex();

        glEnd();

        glDepthFunc(GL_LESS);

    glPopMatrix();
    glPopAttrib();

    GLERROR;
}

GltFieldPtr
GltGrid::settings()
{
    GltFields *root = new GltFields("grid");

    root->add(visible(),"enable");

    root->add(_origin,"origin");
    root->add(_right ,"right");
    root->add(_up    ,"up");

    root->add(_rightStepMajor,"rMajor");
    root->add(_rightStepMinor,"rMinor");
    root->add(_upStepMajor,   "uMajor");
    root->add(_upStepMinor,   "uMinor");

    root->add(color()    ,"color");
    root->add(_axesColor ,"axesColor");
    root->add(_majorColor,"majorColor");
    root->add(_minorColor,"minorColor");

    return root;
}
