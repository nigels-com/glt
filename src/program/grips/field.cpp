#include "field.h"

#include "psystem.h"
#include "integrat.h"

#include <glt/rgb.h>

Field:: Field(const double size,const double min,const double max)
:
    _enable(false),
    _size(size),
    _n(10000),
    _min(min),
    _max(max),
    _color1(grey),
    _color2(white)
{
}

Field::~Field()
{
}

void
Field::draw(const ParticleSystem &system,const Integrator &engine) const
{
    if (!_enable)
        return;

    BoundingBox box;
    engine.boundingBox(box,system,_min);

    if (box.defined())
    {
        const Vector &min = box.min();
        const Vector &max = box.max();

        const Vector o
        (
            min.x()-fmod(min.x(),_size),
            min.y()-fmod(min.y(),_size),
            0
        );

        Vector dx(max.x()-min.x()+_size,0,0);
        Vector dy(0,max.y()-min.y()+_size,0);

        const int imax = int(dx.length()/_size);
        const int jmax = int(dy.length()/_size);

        if (double(imax)*double(jmax)>double(_n))
            return;

        dx.normalize();
        dy.normalize();

        dx *= _size;
        dy *= _size;

        glBegin(GL_LINES);

        //

        const double delta  = _max-_min;
        const double idelta = 1.0/delta;

        //

        Vector pos;

        for (int i=0; i<imax; i++)
        {
            pos = o + dx*double(i);

            for (int j=0; j<jmax; j++)
            {
                Vector f = engine.field(system,pos);
                double fl = f.length();

                if (fl>_min)
                {
                    f.normalize();

                    if (fl<_max)
                    {
                        f *= _size*0.5*(fl-_min)*idelta;
                        _color1.glColor();  (pos-f).glVertex();
                        _color2.glColor();  (pos+f).glVertex();
                    }
                    else
                    {
                        f *= _size*0.5;
                        _color1.glColor();  (pos-f).glVertex();
                        _color2.glColor();  (pos+f).glVertex();
                    }
                }

                pos += dy;
            }
        }

        glEnd();
    }
}

GltFieldPtr
Field::settings()
{
    GltFields *root = new GltFields("field");
    root->add(_enable  ,"enable");
    root->add(_color1  ,"color1");
    root->add(_color2  ,"color2");
    root->add(_size,0.5,"size"  );
    root->add(_min ,1.0,"min"   );
    root->add(_max ,1.0,"max"   );
    return root;
}
