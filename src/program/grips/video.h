#ifndef GRIPS_VIDEO_H
#define GRIPS_VIDEO_H

#include <math/matrix4.h>
#include <node/field.h>
#include <node/sprite.h>

#include <network/httpclient.h>

#include "engine.h"

#include <string>

class Video : public Engine, GltHttpClient
{
public:
    Video();
    ~Video();

    void update(ParticleSystem &system) const;

    void OnReceive(const std::string &data);

    GltFieldPtr settings();

    void draw();

    void ref();

private:

   // Can be manipulated at runtime

    bool     _enable;
    int      _threshold;
    Matrix   _transform;

    GltColor _stopColor;
//    GltColor _startColor;

    // Internal

    uint32       _width;
    uint32       _height;
    std::string  _image;
    std::string  _mask;
    std::string  _maskRef;
    GltSprite    _sprite;
    GltSprite    _spriteMask;
};

#endif
