#include "recode.h"

#include "psystem.h"
#include "particle.h"

#include <math/vector3.h>
#include <node/fields.h>

#include <glt/rgb.h>
#include <glt/error.h>
#include <glt/buffer.h>

#include <glutm/shape.h>

#include <iostream>
#include <cmath>
using namespace std;

EngineRecode::EngineRecode()
:
    _e(1.0),
    _collision(true),
    _colorCode(true),
    _wallImpact(blue),
    _ballImpact(white)
{
    _boundingBox = BoundingBox(Vector(-10,-10,-10),Vector(10,10,10));
}

EngineRecode::~EngineRecode()
{
}

void
EngineRecode::update(ParticleSystem &system) const
{
    ParticleSystem::iterator i;

    // Update position of each puck

    for (i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        if (!a._fixed)
            a._position += a._velocity*_dt;
    }

    // Check for collision with walls

    for (i=system.begin(); i!=system.end(); i++)
    {
        Particle &a = *i;

        if (!a._fixed)
            for (int j=0; j<3; j++)
            {
                const double dmin = (a._position[j]-a._radius)-_boundingBox.min()[j];
                if (dmin<0)
                {
                    a._position[j] -= dmin;
                    a._velocity[j] *= -1.0;

//                  if (_colorCode)
//                      a._color = _wallImpact;
                }

                const double dmax = (a._position[j]+a._radius)-_boundingBox.max()[j];
                if (dmax>0)
                {
                    a._position[j] -= dmax;
                    a._velocity[j] *= -1.0;

//                  if (_colorCode)
//                      a._color = _wallImpact;
                }
            }
    }

    // Check for collision between balls

    if (_collision)
        recode(system);

    system._t += _dt;
    system.updateAge(_dt);
    system._i++;
}

void
EngineRecode::print(ostream &os) const
{
    Integrator::print(os);
}

GltFieldPtr
EngineRecode::settings()
{
    GltFields *root = new GltFields("recode");
    root->merge(Integrator::settings());
    root->add(_collision,   "collision");
    root->add(_e,0.1,       "e");
    root->add(_colorCode,   "colorCode");
    root->add(_wallImpact,  "wallImpact");
    root->add(_ballImpact,  "ballImpact");
    return root;
}

bool
EngineRecode::recode(ParticleSystem &system) const
{
    const int n=system.size();

    ParticleSystem::iterator i;

    // Construct bounding boxes

    vector<BoundingBox> box(n);

    uint32 a=0;
    for (i=system.begin(); i!=system.end(); i++,a++)
    {
        const double  rad = i->_radius;
        const Vector &pos = i->_position;
        const Vector  delta(rad,rad,rad);

        box[a] += pos - delta;
        box[a] += pos + delta;
    }

    // Project bounding boxes into image-space

    const Matrix      model(GL_MODELVIEW_MATRIX);
    const Matrix      proj(GL_PROJECTION_MATRIX);
    const GltViewport view(true);

    a=0;
    for (i=system.begin(); i!=system.end(); i++,a++)
        box[a].project(model,proj,view);

    // Setup spheres

    GlutSphere sphere1;
    sphere1.slices() = 8;
    sphere1.stacks() = 8;

    GlutSphere sphere2;
    sphere2.slices() = 8;
    sphere2.stacks() = 8;

    // Compare each pair of objects

    a=0;
    for (i=system.begin(); i!=system.end(); i++,a++)
    {
        ParticleSystem::iterator j=i;
        uint32 b=a;
        for (j++,b++; j!=system.end(); j++,b++)
        {
            if (box[a].intersects(box[b]))
            {
                sphere1.position(i->_position,i->_radius);
                sphere2.position(j->_position,j->_radius);

                if (recode(sphere1,sphere2,intersection(box[a],box[b])))
                    i->_color = j->_color = _ballImpact;
            }
        }
    }

    return true;
}

bool
EngineRecode::recode(const GltShape &a,const GltShape &b,const BoundingBox &box) const
{
    bool collide = false;

    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT |
                 GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_VIEWPORT_BIT);

        // Enable writes to depth and stencil buffers only

        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
        glDepthMask(GL_TRUE);
        glStencilMask(~0);

        // Disable stencil testing and normalisation

        glDisable(GL_STENCIL_TEST);
        glDisable(GL_NORMALIZE);

        // Disable lighting

        glDisable(GL_LIGHTING);

#if 0

        // THIS IS NIGEL'S METHOD

        // Draw the furthest front facing surface into z-buffer.

        glClearStencil(0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glClearDepth(0.0);
        glDepthFunc(GL_GREATER);
        glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //

        a.draw();
        b.draw();

        // Count the number of back-facing surfaces behind each pixel.

        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS,0,~0);
        glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);
        glCullFace(GL_FRONT);
        glDepthMask(GL_FALSE);

        a.draw();
        b.draw();

        // Read back stencil buffer for region of overlap

        GltViewport view(true);
        view.resize(box);
        view.set();

        GltFrameBufferStencilUbyte stencil;

        // Collision where stencil == n

        for (uint32 i=0; i<stencil.size(); i++)
            if (stencil[i]==2)
            {
                collide = true;
                break;
            }

#else
    bool secondPass = false;

        // THIS IS RECODE METHOD

        // Draw the back of A into z-buffer

        glClearStencil(0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        glClearDepth(0.0);
        glDepthFunc(GL_ALWAYS);
        glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        a.draw();

        // Check B against back of A

        glDisable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_FALSE);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS,0,~0);
        glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);

        b.draw();

        // Read back stencil buffer for region of overlap

        GltViewport view(true);
        view.resize(box);
        view.set();

        GltFrameBufferStencilUbyte stencil;

        // If there is any pixel with stencil value of 1, collision found
        // If there are pixels with stencil value of 2, second pass necessary
        // Otherwise, no collision between A and B

        for (uint32 i=0; i<stencil.size(); i++)
        {
            if (stencil[i]==1)
            {
                collide = true;
                break;
            }

            if (stencil[i]==2)
                secondPass = true;
        }

        // Do second pass, only if necesary

        if (secondPass && !collide)
        {
            // Clear stencil

            glClear(GL_STENCIL_BUFFER_BIT);

            // Draw the front of A into z-buffer

            glDisable(GL_STENCIL_TEST);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glDepthFunc(GL_ALWAYS);

            a.draw();

            // Check B against front of A

            glDisable(GL_CULL_FACE);
            glDepthFunc(GL_GREATER);
            glDepthMask(GL_FALSE);
            glEnable(GL_STENCIL_TEST);

            b.draw();

            // Check stencil

            stencil.read();

            // Look for value of 1
            // (If B is concave, odd crossings)

            for (uint32 i=0; i<stencil.size(); i++)
            {
                if (stencil[i]==1)
                {
                    collide = true;
                    break;
                }
            }

        }
#endif

    glPopAttrib();                      // Restore OpenGL state
    GLERROR                             // Check for OpenGL errors

    return collide;
}


