#include "histogrm.h"

#include <glt/buffer.h>
#include <glt/rgb.h>

CsgHistograms::CsgHistograms()
{
    _rBuffer.color()    = red;
    _rBuffer.visible()  = false;
    _rBuffer.size()     = 256;
    _rBuffer.max()      = 256.0;
    _rBuffer.drawLine() = true;

    _gBuffer.color()    = green;
    _gBuffer.visible()  = false;
    _gBuffer.size()     = 256;
    _gBuffer.max()      = 256.0;
    _gBuffer.drawLine() = true;

    _bBuffer.color()    = blue;
    _bBuffer.visible()  = false;
    _bBuffer.size()     = 256;
    _bBuffer.max()      = 256.0;
    _bBuffer.drawLine() = true;

    _zBuffer.color()    = white;
    _zBuffer.visible()  = false;
    _zBuffer.size()     = 100;
    _zBuffer.drawLine() = true;
}

CsgHistograms::~CsgHistograms()
{
}

void
CsgHistograms::draw() const
{
    // Histograms

    ((CsgHistograms *) this)->updateHistograms();

    {
        glPushAttrib(GL_VIEWPORT_BIT);

            GltViewport v(true);
            v.height() >>= 1;
            v.set();

            if (_rBuffer.visible()) _rBuffer.draw();
            if (_gBuffer.visible()) _gBuffer.draw();
            if (_bBuffer.visible()) _bBuffer.draw();
            if (_zBuffer.visible()) _zBuffer.draw();

        glPopAttrib();
    }
}

void
CsgHistograms::updateHistograms()
{
    if (_zBuffer.visible())
    {
        _zBuffer.reset();
        const GltFrameBufferZFloat zBuffer;
        const GLuint step = std::max(1u,zBuffer.size()>>12);
        for (GLuint i=0; i<zBuffer.size(); i+=step)
            _zBuffer.add(zBuffer[i]);
    }

    if (_rBuffer.visible() || _gBuffer.visible() || _bBuffer.visible())
    {
        _rBuffer.reset();
        _gBuffer.reset();
        _bBuffer.reset();

        const GltFrameBufferRGB rgbBuffer;
        const GLuint step = std::max(1u,rgbBuffer.size()>>13);
        for (GLuint i=0; i<rgbBuffer.size(); i+=step)
        {
            const GLubyte *pixel = rgbBuffer[i];
            _rBuffer.add(pixel[0]);
            _gBuffer.add(pixel[1]);
            _bBuffer.add(pixel[2]);
        }
    }
}

bool &CsgHistograms::rBuffer() { return _rBuffer.visible(); }
bool &CsgHistograms::gBuffer() { return _gBuffer.visible(); }
bool &CsgHistograms::bBuffer() { return _bBuffer.visible(); }
bool &CsgHistograms::zBuffer() { return _zBuffer.visible(); }
