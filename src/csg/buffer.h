#ifndef CSG_BUFFER_H
#define CSG_BUFFER_H

/** \file
 *  \brief   Frame-buffer helper class for CSG rendering
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <glt/buffer.h>
#include <glt/viewport.h>

class CsgDepthBufferHelper
{
public:
    CsgDepthBufferHelper(const bool useCopy = true);
    ~CsgDepthBufferHelper();

    void read();
    void write(const bool merge = true);
    bool empty() const;

private:

    typedef GltFrameBufferZ      <GLuint, GL_UNSIGNED_INT>  depthBuffer;
    typedef GltFrameBufferStencil<GLubyte,GL_UNSIGNED_BYTE> stencilBuffer;

    bool         _useCopy;
    GltViewport  _viewport;
    depthBuffer *_buffer;
};

#endif

