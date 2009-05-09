#ifndef CSG_CAPTURE_H
#define CSG_CAPTURE_H

/** \file
 *  \brief   Frame-buffer capturing class
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 *  \todo    Remove dependency on GlutWindow and migrate to GLT?
 */

#include <node/field.h>

class GlutWindow;

class GltBufferCapture
{
public:
    GltBufferCapture(GlutWindow &window);
    ~GltBufferCapture();

    void capture();

    bool &active();
    int  &countColor();
    int  &countDepth();
    int  &countStencil();
    int  &countColorCRC();

    bool finished() const;

    GltFieldPtr settings();

private:
    GlutWindow &_window;

    bool _active;

    int  _countColor;
    int  _countDepth;
    int  _countStencil;

    int  _countColorCRC;

    bool _finished;
};

#endif
