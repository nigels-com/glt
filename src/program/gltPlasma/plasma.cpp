/*
 * Copyright (C) 2002  Terence M. Welsh
 *
 * Plasma is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Plasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "plasma.h"

#include <glt/gl.h>
#include <glt/error.h>

#include <math/real.h>
#include <math/random.h>

#include <node/fields.h>

#include <cmath>
#include <ctime>
using namespace std;

//

Plasma::Settings::Settings()
: _zoom(10),
  _focus(10),
  _speed(20),
  _resolution(25)
{
}

Plasma::Settings::~Settings()
{
}

GltFieldPtr
Plasma::Settings::settings()
{
    GltFields *root = new GltFields("plasma");

        root->add(_zoom,      "zoom");
        root->add(_focus,     "focus");
        root->add(_speed,     "speed");
        root->add(_resolution,"resolution");

    return root;
}

//

const uint32 Plasma::_n(18);

Plasma::Plasma()
: _init(false),
  _plasmaSize(64)
{
    _c.resize(_n);
    _ct.resize(_n);
    _cv.resize(_n);
}

Plasma::~Plasma()
{
}

void
Plasma::init(uint32 width,uint32 height)
{
    // Do sanity checking for the settings

    _settings._resolution = std::max(_settings._resolution,10);
    _settings._zoom       = std::max(_settings._zoom,5);

    //

    GLERROR

    _viewport.set(width,height);

    if (width>height)
    {
        _wide = 30.0f / float(_settings._zoom);
        _high = _wide * float(height) / float(width);
    }
    else
    {
        _high = 30.0f / float(_settings._zoom);
        _wide = _high * float(width) / float(height);
    }

    // Set resolution of plasma
    uint32 size = std::max(width,height)/_settings._resolution;

    // Clamp size to maximum supported OpenGL texture size

    int maxSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE,&maxSize);

    size = clamp<uint32>(size,0,maxSize);

    // Set resolution of texture

    _plasmaSize = 16;
    while ((_plasmaSize<<1)<=size)
        _plasmaSize <<= 1;

    // Initialize memory and positions

    uint32 i;

    // Plasma Map

    _plasmaMap.clear();
    _plasmaMap.resize(_plasmaSize*_plasmaSize*3);
    for (i=0; i<_plasmaMap.size(); i++)
        _plasmaMap[i] = 0.0f;

    // Plasma

    _plasma.clear();
    _plasma.resize(_plasmaSize*_plasmaSize*3);
    for (i=0; i<_plasma.size(); i++)
        _plasma[i] = 0.0f;

    // Position

    _position.clear();
    _position.resize(_plasmaSize*_plasmaSize*2);

    std::vector<float>::iterator k=_position.begin();

    for (i=0; i<_plasmaSize; i++)
        for (uint32 j=0; j<_plasmaSize; j++)
        {
            *(k++) = float(i * _wide) / float(_plasmaSize - 1) - (_wide * 0.5f);
            *(k++) = float(j * _high) / float(_plasmaSize - 1) - (_high * 0.5f);
        }

    assert(k==_position.end());

    // Initialize constants

    GltRandomLCG::rng.seed(time(NULL));
    GltRandomDouble<GltRandomLCG> rt(0.0,M_2PI);
    GltRandomDouble<GltRandomLCG> rv(0.0,0.005f * float(_settings._speed));

    for (i=0; i<_n; i++)
    {
        _c[i]  = rt.rand();
        _ct[i] = rt.rand();
        _cv[i] = rv.rand() + 0.0001f;
    }

    // Make texture

    static GLuint _id;

    glGenTextures(1,&_id);
    glBindTexture(GL_TEXTURE_2D,_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, _plasmaSize, _plasmaSize, 0,
        GL_RGB, GL_FLOAT, &_plasmaMap[0]);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, _plasmaSize);

    GLERROR

    _init = true;
}

void
Plasma::update()
{
    if (!_init)
        return;

    GLERROR

    const float focus = float(_settings._focus) / 50.0f + 0.3f;
    const float maxdiff = 0.004f * float(_settings._speed);

    // Update constants

    uint32 i;

    for (i=0; i<_n; i++)
    {
        _ct[i] += _cv[i];
        if (_ct[i] > M_2PI)
            _ct[i] -= float(M_2PI);
        _c[i] = sinf(_ct[i]) * focus;
    }

    assert(_plasma.size());
    assert(_plasmaMap.size());
    assert(_position.size());

    // Update colors

    float *k = &_plasma[0];
    float *m = &_plasmaMap[0];
    float *n = &_position[0];

    for(i=0; i<_plasmaSize; i++)
    {
        for(uint32 j=0; j<_plasmaSize; j++)
        {
            float &red   = *(k++);
            float &green = *(k++);
            float &blue  = *(k++);

            const float &x = *(n++);
            const float &y = *(n++);

            // Store old value temporarily

            const float redTmp   = red;
            const float greenTmp = green;
            const float blueTmp  = blue;

            // Calculate vertex colors

            red = 0.7f
                            * (_c[0] * x + _c[1] * y
                            + _c[2] * (x * x + 1.0f)
                            + _c[3] *  x * y
                            + _c[4] * greenTmp + _c[5] * blueTmp);
            green = 0.7f
                            * (_c[6] * x + _c[7] * y
                            + _c[8] * x * x
                            + _c[9] * (y * y - 1.0f)
                            + _c[10] * redTmp + _c[11] * blueTmp);
            blue = 0.7f
                            * (_c[12] * x + _c[13] * y
                            + _c[14] * (1.0f - x * y)
                            + _c[15] * y * y
                            + _c[16] * redTmp + _c[17] * greenTmp);

            // Don't let the colors change too much
            float temp;
            temp = red - redTmp;
            if(temp > maxdiff)
                red = redTmp + maxdiff;
            if(temp < -maxdiff)
                red = redTmp - maxdiff;

            temp = green - greenTmp;
            if(temp > maxdiff)
                green = greenTmp + maxdiff;
            if(temp < -maxdiff)
                green = greenTmp - maxdiff;

            temp = blue - blueTmp;
            if(temp > maxdiff)
                blue = blueTmp + maxdiff;
            if(temp < -maxdiff)
                blue = blueTmp - maxdiff;

            // Put colors into texture

            *(m++) = fabstrunc(red);
            *(m++) = fabstrunc(green);
            *(m++) = fabstrunc(blue);
        }
    }

    // Update texture
    glTexSubImage2D
    (
        GL_TEXTURE_2D,
        0,0,0,
        _plasmaSize,
        _plasmaSize,
        GL_RGB,
        GL_FLOAT,
        &_plasmaMap[0]
    );

    GLERROR
}

void
Plasma::draw()
{
    if (!_init)
        return;

    GLERROR

    int &w = _viewport.width();
    int &h = _viewport.height();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2i(0,0); glVertex2i(0,0);
        glTexCoord2i(0,1); glVertex2i(w,0);
        glTexCoord2i(1,0); glVertex2i(0,h);
        glTexCoord2i(1,1); glVertex2i(w,h);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    GLERROR
}

GltFieldPtr
Plasma::settings()
{
    return _settings.settings();
}

