#include "lightm.h"

/*! \file
    \ingroup GLT

    $Id: lightm.cpp,v 2.0 2004/02/08 19:44:11 nigels Exp $

    $Log: lightm.cpp,v $
    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.7  2002/11/27 00:57:28  nigels
    expand

    Revision 1.6  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.5  2002/10/09 15:09:38  nigels
    Added RCS Id and Log tags


*/

#include <glt/error.h>

#include <cstring>
using namespace std;

GltLightModel::GltLightModel(const bool getIt)
{
    memset(_ambient,0,sizeof(_ambient));
    _localViewer = false;
    _twoSide = false;

    if (getIt)
        get();
}

GltLightModel::~GltLightModel()
{
}

void
GltLightModel::get()
{
    GLint localViewer;
    GLint twoSide;

    GLERROR

    glGetFloatv(GL_LIGHT_MODEL_AMBIENT,_ambient);
    glGetIntegerv(GL_LIGHT_MODEL_LOCAL_VIEWER,&localViewer);
    glGetIntegerv(GL_LIGHT_MODEL_TWO_SIDE,&twoSide);

    GLERROR

    _localViewer = localViewer!=0;
    _twoSide     = twoSide!=0;
}

void
GltLightModel::set()
{
    GLERROR

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,_localViewer ? 1 : 0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,_twoSide ? 1 : 0);

    GLERROR
}

void
GltLightModel::setAmbient(const GLfloat r,const GLfloat g,const GLfloat b,const GLfloat a)
{
    GLERROR

    _ambient[0] = r;
    _ambient[1] = g;
    _ambient[2] = b;
    _ambient[3] = a;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,_ambient);

    GLERROR
}

void
GltLightModel::setLocalViewer(const GLboolean localViewer)
{
    GLERROR

    _localViewer = localViewer;
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,_localViewer ? 1 : 0);

    GLERROR
}

void
GltLightModel::setTwoSide(const GLboolean twoSide)
{
    GLERROR

    _twoSide = twoSide;
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,_twoSide ? 1 : 0);

    GLERROR
}

GLfloat   *GltLightModel::ambient()     { return _ambient;       }
GLboolean &GltLightModel::localViewer() { return _localViewer;   }
GLboolean &GltLightModel::twoSide()     { return _twoSide;       }

