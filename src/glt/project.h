#ifndef GLT_PROJECT_H
#define GLT_PROJECT_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2003 Nigel Stewart

  Email:  nigels@nigels.com
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

/*! \file
    \brief   OpenGL Projection Classes
    \ingroup GLT

    $Id: project.h,v 1.1 2004/02/08 11:46:28 jgasseli Exp $

    $Log: project.h,v $
    Revision 1.1  2004/02/08 11:46:28  jgasseli
    Initial revision

    Revision 1.20  2003/03/14 15:34:31  nigels
    Some cleanup, added mult(), rethinking tiling

    Revision 1.19  2003/03/06 12:21:40  nigels
    *** empty log message ***

    Revision 1.18  2003/02/07 09:57:35  nigels
    *** empty log message ***

    Revision 1.13  2002/11/27 00:57:28  nigels
    expand

    Revision 1.12  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.11  2002/10/07 16:33:35  nigels
    Added CVS info


*/

#include <glt/config.h>
#include <glt/gl.h>

/*! \class   GltOrtho
    \brief   OpenGL Orthographic Camera Class
    \ingroup GLT
*/

class GltOrtho
{
public:

    /// Constructor
    GltOrtho();
    /// Destructor
    ~GltOrtho();

    /// Set OpenGL projection matrix
    void set() const;
    /// Set OpenGL projection matrix
    void set(int width,int height);

    /// Multiply with OpenGL projection matrix
    void mult() const;

                                    /// Left position
    GLdouble &left();
                                    /// Right position
    GLdouble &right();
                                    /// Bottom position
    GLdouble &bottom();
                                    /// Top position
    GLdouble &top();
                                    /// zNear position
    GLdouble &zNear();
                                    /// zFar position
    GLdouble &zFar();

                                    /// Left position
    const GLdouble &left()   const;
                                    /// Right position
    const GLdouble &right()  const;
                                    /// Bottom position
    const GLdouble &bottom() const;
                                    /// Top position
    const GLdouble &top()    const;
                                    /// zNear position
    const GLdouble &zNear()  const;
                                    /// zFar position
    const GLdouble &zFar()   const;

    /// Calculate the n'th tile of a grid: dx*dy
    bool tile(GltOrtho &frust,const int dx,const int dy,const int n) const;

private:

    GLdouble _left;
    GLdouble _right;
    GLdouble _bottom;
    GLdouble _top;
    GLdouble _zNear;
    GLdouble _zFar;
};

/*! \class   GltFrustum
    \brief   OpenGL Perspective Camera Class
    \ingroup GLT
*/

class GltFrustum
{
public:

    /// Constructor
    GltFrustum();
    /// Destructor
    ~GltFrustum();

    /// Set OpenGL projection matrix
    void set() const;
    /// Set OpenGL projection matrix
    void set(int width,int height);

    /// Multiply with OpenGL projection matrix
    void mult() const;

                                    /// Left position
    GLdouble &left();
                                    /// Right position
    GLdouble &right();
                                    /// Bottom position
    GLdouble &bottom();
                                    /// Top position
    GLdouble &top();
                                    /// zNear position
    GLdouble &zNear();
                                    /// zFar position
    GLdouble &zFar();

                                    /// Left position
    const GLdouble &left()   const;
                                    /// Right position
    const GLdouble &right()  const;
                                    /// Bottom position
    const GLdouble &bottom() const;
                                    /// Top position
    const GLdouble &top()    const;
                                    /// zNear position
    const GLdouble &zNear()  const;
                                    /// zFar position
    const GLdouble &zFar()   const;

    /// Calculate the n'th tile of a grid: dx*dy
    bool tile(GltFrustum &frust,const int dx,const int dy,const int n) const;

private:

    GLdouble _left;
    GLdouble _right;
    GLdouble _bottom;
    GLdouble _top;
    GLdouble _zNear;
    GLdouble _zFar;
};

/*! \class   GltPerspective
    \brief   OpenGL Perspective Camera Class
    \ingroup GLT
*/

class GltPerspective
{
public:

    /// Constructor
    GltPerspective();
    /// Destructor
    ~GltPerspective();

    /// Set OpenGL projection matrix
    void set() const;
    /// Set OpenGL projection matrix
    void set(int width,int height);

    /// Multiply with OpenGL projection matrix
    void mult() const;
    /// Multiply with OpenGL projection matrix
    void mult(int width,int height);

                                    /// Field of view angle, in degrees in y direction
    GLdouble &fovy();
                                    /// Aspect ratio: width to height
    GLdouble &aspect();
                                    /// Distance to near clipping plane
    GLdouble &zNear();
                                    /// Distance to far clipping plane
    GLdouble &zFar();

                                    /// Field of view angle, in degrees in y direction
    const GLdouble &fovy()   const;
                                    /// Aspect ratio: width to height
    const GLdouble &aspect() const;
                                    /// Distance to near clipping plane
    const GLdouble &zNear()  const;
                                    /// Distance to far clipping plane
    const GLdouble &zFar()   const;

    /// Calculate the n'th tile of a grid: dx*dy
    bool tile(GltPerspective &persp,const int dx,const int dy,const int n) const;

private:

    GLdouble _fovy;
    GLdouble _aspect;
    GLdouble _zNear;
    GLdouble _zFar;

    GLdouble _rotX;
    GLdouble _rotY;
};

#endif
