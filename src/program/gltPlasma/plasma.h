#ifndef PLASMA_H
#define PLASMA_H

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

#include <vector>

#include <node/field.h>
#include <glt/viewport.h>

class Plasma
{
public:
    Plasma();
    ~Plasma();

    void init(const uint32 width,const uint32 height);
    void update();
    void draw();

    GltFieldPtr settings();

private:

    GltViewport _viewport;

    bool  _init;

    float _wide;
    float _high;

    static const uint32 _n;
    std::vector<float>  _c;   // constant
    std::vector<float>  _ct;  // temporary value of constant
    std::vector<float>  _cv;  // velocity of constant

    uint32             _plasmaSize;
    std::vector<float> _plasmaMap;
    std::vector<float> _plasma;
    std::vector<float> _position;

    //

    class Settings
    {
    public:
        Settings();
        ~Settings();

        GltFieldPtr settings();

        int _zoom;
        int _focus;
        int _speed;
        int _resolution;
    };

    Settings _settings;

    //

    inline float fabstrunc(float f)
    {
        if(f >= 0.0f)
            return (f <= 1.0f ? f : 1.0f);
        else
            return (f >= -1.0f ? -f : 1.0f);
    }
};

#endif
