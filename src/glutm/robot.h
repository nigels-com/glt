#ifndef GLUTM_ROBOT_H
#define GLUTM_ROBOT_H

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
    \brief   GLUT Window Event Trigger Class
    \author  Nigel Stewart (nigels@nigels.com)
    \ingroup GlutMaster
*/

#include <glutm/config.h>
#include <glutm/window.h>
#include <node/shape.h>
#include <node/shapes.h>

///////////////////////////// GlutRobot ///////////////////////////////////////

/*! \class   GlutRobot
    \brief   GLUT Window Event Trigger Class
    \ingroup GlutMaster
    \author  Nigel Stewart (nigels@nigels.com)

    A robot node will send a menu event to a select window
    when a particular node in the scene-graph expires.
    Once the event is sent, the robot will also expire.

*/

class GlutRobot : public GltShape
{
public:

    //
    // Constructor/Destructor
    //

    /*!
        \brief      Constructor
        \param      shape       Wait for shape node to expire
        \param      window      Window to send menu event
        \param      value       Menu event ID
    */
    GlutRobot(GltShapePtr &shape,GlutWindow &window,const GlutWindow::MenuCallbacks value);
    /// Destructor
    ~GlutRobot();

    virtual void draw() const;

private:

    GltShapePtr                      _shape;
    GlutWindow                      &_window;
    const GlutWindow::MenuCallbacks  _value;
};

#endif
