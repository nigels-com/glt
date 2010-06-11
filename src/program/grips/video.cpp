#include "video.h"
#include "psystem.h"

#include <node/fields.h>
#include <glt/rgb.h>
#include <glt/error.h>
#include <misc/image.h>
#include <misc/string.h>

#include "textures.h"

#include <string>
#include <iostream>
using namespace std;

Video::Video()
: _enable(false),
  _threshold(128),
  _stopColor(red)
{
    uint32 format,components;
    GltTexture::decodeImage(handmaskTexture,format,components,_width,_height,_image);
    assert(_image.size()==_width*_height);

    _transform *= matrixScale(5.0) * matrixRotate(VectorX,-90);

    _spriteMask.color() = red;
}

Video::~Video()
{
}

void
Video::draw()
{
   if (!_enable)
      return;

    if (_sprite.empty())
    {
        if (!_sprite.init(_width,_height,_image,false))
            gltWarning("Trouble initialising sprite.");

        _spriteMask.init(_width,_height,_mask,false);
    }

    glPushAttrib(GL_ENABLE_BIT);

        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        glPushMatrix();
            _transform.glMultMatrix();
            glScalef(1.0/_sprite.width(),1.0/_sprite.height(),1.0);
            _sprite.draw();
            _spriteMask.draw();
        glPopMatrix();

    glPopAttrib();
}

void
Video::ref()
{
    _maskRef = _image;
}

void
Video::update(ParticleSystem &system) const
{
    if (_enable)
    {
        const Matrix inv = _transform.inverse();

        for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
        {
            Particle &p = *i;
            p._fixed = false;

            const Vector3 q = inv*p._position;

            const int x = (int) floor(q.x()*_width);
            const int y = (int) floor(q.y()*_height);

            if (x>=0 && y>=0 && x<int(_width) && y<int(_height))
                if ((byte &)(_mask[x+y*_width])>_threshold)
                {
                    p._fixed = true;
                    p._velocity = Vector0;
                    p._color  = _stopColor;
                }
        }
    }
/*
    // Disable this for the sake on non-waterwall systems
   else
        for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
            i->_fixed = false;
*/
}

void
Video::OnReceive(const std::string &data)
{
    #ifndef NDEBUG
    cout << "Data: " << data.size() << endl;
    #endif

    if (!decode(_width,_height,_image,data))
    {
        gltWarning("Trouble decoding image in Video::OnReceive");
        return;
    }

    uint32 components = _image.size()/(_width*_height);

    #ifndef NDEBUG
    cout << "Image: " << _width << "x" << _height << " " << components << endl;
    #endif


    if (components!=1)
    {
        string tmp;
        if (!getChannel(tmp,_image,components,0))
        {
            gltWarning("Trouble extracting channel in Video::OnReceive");
        }

        _image = tmp;
    }
   _sprite.clear();

    assert(_image.size()==_width*_height);

    // Take the difference between current image and
    // reference image

//  if (!_imageRef.size() || _width*_height!=_imageRef.size())
//      _imageRef = _image;

    if (_maskRef.size()==_image.size())
    {
        _mask.resize(_image.size());

        const byte *i = reinterpret_cast<const byte *>(&_maskRef[0]);
        const byte *j = reinterpret_cast<const byte *>(&_image[0]);

        for (uint32 k=0; k<_mask.size(); k++)
            _mask[k] = abs(float(int32(*(i++)) - int32(*(j++))));
//          _mask[k] = *(i++) - *(j++);
    }
    else
    {
        _maskRef = _image;
        memset(&_maskRef[0],0,_mask.size());
    }
}

GltFieldPtr
Video::settings()
{
    GltFields *root = new GltFields("video");
    root->add(_enable,       "enable");
    root->add(_threshold,    "threshold");
    root->add(_transform,    "transform");
    root->add(_stopColor,    "stopColor");
    root->add(new GltFieldFunc<Video>(*this,&Video::ref,"ref"));
    root->add(GltHttpClient::settings());
    root->add(_sprite.settings()    ,"sprite");
    root->add(_spriteMask.settings(),"mask");

    return root;
}

