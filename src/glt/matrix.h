#ifndef GLT_MATRIX_H
#define GLT_MATRIX_H

/*
  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2007 Nigel Stewart

  WWW:    http://www.nigels.com/glt/
  Forums: http://sourceforge.net/forum/?group_id=36869

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/* $Id: matrix.h,v 2.2 2007/05/06 16:46:24 nigels Exp $ */

/*! \file
    \brief   OpenGL Matrix Manipulation
    \ingroup GLT
*/

#include <glt/gl.h>

#include <math/vector3.h>

//
//
//

/*! \class GltPushMatrix
    \brief OpenGL Push-Matrix Convenience Class
    \ingroup GLT

    The current OpenGL matrix is pushed by the
    constructor and popped by the destructor.
    This helps prevent stack underflow or
    overflow.
*/

class GltPushMatrix
{
public:
    /// Constructor: glPushMatrix()
    GltPushMatrix(const bool enable = true);
    /// Destructor: glPopMatrix()
    ~GltPushMatrix();

private:
    const bool _enable;
};

//
// TRANSLATE
//

/*! \brief   OpenGL vector translation
    \ingroup GLT
    \param   tr   Distance to translate in x, y and z
*/
inline void glTranslate(const Vector &tr) { glTranslated(tr.x(),tr.y(),tr.z()); }

//
// SCALE
//

/*! \brief   OpenGL non-uniform scale
    \ingroup GLT
    \param   sf   Scaling factor in x, y and z
*/
inline void glScale(const Vector &sf)    { glScaled(sf.x(),sf.y(),sf.z()); }

/*! \brief   OpenGL uniform scale
    \ingroup GLT
    \param   sf   Scaling factor
*/
inline void glScale(const GLdouble sf)   { glScaled(sf,sf,sf); }

/*! \brief   OpenGL uniform scale
    \ingroup GLT
    \param   sf   Scaling factor
*/
inline void glScale(const GLfloat  sf)   { glScalef(sf,sf,sf); }

/*! \brief   OpenGL uniform scale
    \ingroup GLT
    \param   sf   Scaling factor
*/
inline void glScale(const GLint    sf)   { const GLfloat _s = (const GLfloat) sf; glScalef(_s,_s,_s); }

/*! \brief   OpenGL uniform scale
    \ingroup GLT
    \param   sf   Scaling factor
*/
inline void glScale(const GLuint   sf)   { const GLfloat _s = (const GLfloat) sf; glScalef(_s,_s,_s); }

//
// ROTATE
//

/*! \brief   OpenGL rotation
    \ingroup GLT
    \param   angle   Angle in degrees
    \param   axis    Axis of rotation
*/
inline void glRotate(const GLdouble angle,const Vector &axis)
{
    glRotated(angle,axis.x(),axis.y(),axis.z());
}

/*! \brief   OpenGL rotation around X axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateX(const GLdouble angle) { glRotated(angle,1.0,0.0,0.0); }

/*! \brief   OpenGL rotation around X axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateX(const GLfloat  angle) { glRotatef(angle,1.0,0.0,0.0); }

/*! \brief   OpenGL rotation around X axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateX(const GLint    angle) { glRotatef(GLfloat(angle),1.0,0.0,0.0); }

/*! \brief   OpenGL rotation around X axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateX(const GLuint   angle) { glRotatef(GLfloat(angle),1.0,0.0,0.0); }

/*! \brief   OpenGL rotation around Y axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateY(const GLdouble angle) { glRotated(angle,0.0,1.0,0.0); }

/*! \brief   OpenGL rotation around Y axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateY(const GLfloat  angle) { glRotatef(angle,0.0,1.0,0.0); }

/*! \brief   OpenGL rotation around Y axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateY(const GLint    angle) { glRotatef(GLfloat(angle),0.0,1.0,0.0); }

/*! \brief   OpenGL rotation around Y axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateY(const GLuint   angle) { glRotatef(GLfloat(angle),0.0,1.0,0.0); }

/*! \brief   OpenGL rotation around Z axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateZ(const GLdouble angle) { glRotated(angle,0.0,0.0,1.0); }

/*! \brief   OpenGL rotation around Z axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateZ(const GLfloat  angle) { glRotatef(angle,0.0,0.0,1.0); }

/*! \brief   OpenGL rotation around Z axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateZ(const GLint    angle) { glRotatef(GLfloat(angle),0.0,0.0,1.0); }

/*! \brief   OpenGL rotation around Z axis
    \ingroup GLT
    \param   angle   Angle in degrees
*/
inline void glRotateZ(const GLuint   angle) { glRotatef(GLfloat(angle),0.0,0.0,1.0); }

#endif
