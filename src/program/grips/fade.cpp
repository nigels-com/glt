#include "fade.h"

#include "psystem.h"

#include <node/field.h>
#include <node/fields.h>

#include <glt/color.h>
#include <glt/rgb.h>

Fade::Fade()
: _enable(false), _color(grey)
{
    _color.alpha() = 0.98;
}

Fade::~Fade()
{
}

void
Fade::update(ParticleSystem &system) const
{
    if (_enable)
        for (int i=0; i<system.size(); i++)
        {
            Particle &a = system[i];
            a._color = a._color*_color.alpha() + _color*(1.0-_color.alpha());
        }
}

GltFieldPtr
Fade::settings()
{
    GltFields *root = new GltFields("fade");
    root->add(_enable, "enable");
    root->add(_color,  "color");
    return root;
}

