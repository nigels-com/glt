#include "trail.h"

#include "psystem.h"

using namespace std;

Trail::Trail()
:
    _width(1.0),
    _alpha(0.5),
    _normal(VectorZ),
    _skip(1)
{
    inheritColor() = true;
}

Trail::~Trail()
{
}

void
Trail::draw() const
{
    if (size()==0 || !visible())
        return;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();

        if (solid())
        {
            glBegin(GL_LINE_STRIP);
            for (uint32 i=0; i<size(); i++)
                (*this)[i].glVertex();
            glEnd();
        }
        else
        {
            if (size()>=2 && _skip>=1)
            {
                glPushAttrib(GL_ENABLE_BIT);

                    glDisable(GL_LIGHTING);
                    glDisable(GL_TEXTURE_2D);
                    glDisable(GL_CULL_FACE);
                    glDisable(GL_DEPTH_TEST);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

                    GltColor inner;
                    GltColor outer;

                    inner.glGet();
                    outer.glGet();
                    outer.alpha() = 0.0;

                    Vector d0 = Vector0;
                    Vector d1;

                    for (uint32 i=0; (i+_skip)<size(); i+=_skip)
                    {
                        const Vector &p0 = (*this)[i  ];
                        const Vector &p1 = (*this)[i+_skip];

                        const Vector delta = p1-p0;

                        d1 = xProduct(delta,_normal);

                        d1.normalize();
                        d1 *= _width;

                        if (d0==Vector0)
                            d0 = d1;

                        glBegin(GL_QUAD_STRIP);

                            outer.glColor();
                            (p1-d1).glVertex();
                            (p0-d0).glVertex();

                            inner.alpha() = (1.0 - double(i+_skip)/(size()-_skip))*_alpha;
                            inner.glColor();
                            (p1   ).glVertex();

                            inner.alpha() = (1.0 - double(i)/(size()-_skip))*_alpha;
                            inner.glColor();
                            (p0   ).glVertex();

                            outer.glColor();
                            (p1+d1).glVertex();
                            (p0+d0).glVertex();

                        glEnd();

                        d0 = d1;
                    }

                glPopAttrib();
            }
        }

    glPopMatrix();
}

GltFieldPtr
Trail::settings()
{
    GltFields *root = new GltFields("trail");

    root->add(visible(),"enable");
    root->add(solid(),"solid");
    root->add(_width ,"width");
    root->add(_alpha ,"alpha");
    root->add(_normal,"normal");
    root->add(_skip  ,"skip");

    return root;
}

////////////////////

TrailUpdate::TrailUpdate()
: _size(10),
  _overRide(true)
{
}

TrailUpdate::~TrailUpdate()
{
}

void
TrailUpdate::update(ParticleSystem &system) const
{
    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
    {
        Particle &p = *i;
        p._trail.resize(_size);

        if (_overRide)
        {
            p._trail.visible() = _trail.visible();
            p._trail.solid()   = _trail.solid();
            p._trail._width    = _trail._width;
            p._trail._alpha    = _trail._alpha;
            p._trail._normal   = _trail._normal;
            p._trail._skip     = _trail._skip;
        }

        if (p._fixed)
        {
            if (p._trail.size())
                p._trail.pop_back();
        }
        else
            p._trail.push_front(p._position);
    }
}

GltFieldPtr
TrailUpdate::settings()
{
    GltFields *root = new GltFields("trail");
    root->add(_size,"size");
    root->add(_overRide,"overRide");
    root->add(_trail.settings());

    return root;
}

