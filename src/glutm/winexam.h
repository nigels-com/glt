#ifndef GLUTM_WINEXAM_H
#define GLUTM_WINEXAM_H

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
    \brief   Examiner Style Window Class
    \ingroup GlutMaster
*/

#include <glutm/window.h>

#include <glt/project.h>

#include <math/matrix4.h>
#include <math/vector3.h>

/////////////////////////// GlutWindowExaminer ////////////////////////////////////

/*! \class   GlutWindowExaminer
    \brief   Examiner Style Window Class
    \ingroup GlutMaster
*/

class GlutWindowExaminer : public GlutWindow
{
public:
    /// Constructor
    GlutWindowExaminer
    (
        const std::string &title = titleDefault,
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault,
        unsigned int displayMode = displayModeDefault
    );
    /// Destructor
    virtual ~GlutWindowExaminer();

    void OnOpen();
    void OnClose();
    void OnReshape(int w, int h);
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);
    void OnMenu(int value);
    void OnMouse(int button, int state, int x, int y);
    void OnMotion(int x, int y);
    void OnPassiveMotion(int x, int y);

    /// Callback handler for changes in viewing direction
    virtual void OnOrient(const Matrix &viewing,const Matrix &inverse);

    /// Callback handler for getting a refernce point from mouse x and y
    virtual Vector getReferencePoint(int x,int y,const Vector &pos,const Matrix &modelView,const Matrix &modelViewInverse) const;

    /// Current reference point
    Vector &referencePoint();

    //
    // Config
    //


    bool &mouseZoom();              ///< Enable mouse zooming
    bool &mousePan();               ///< Enable mouse panning
    bool &mouseRotate();            ///< Enable mouse rotation

    /// Mouse zoom-pan-rotate mode
    typedef enum
    {
        MODE_MOUSE_ONLY = 0,
        MODE_MOUSE_LEFT,
        MODE_MOUSE_RIGHT,
        MODE_MAX
    } MouseMode;

    MouseMode &mouseMode();         ///< Mouse mode

protected:

    void OnPreDisplay();                ///< Apply current transformation matrix before doing anything else

    bool mousePressed() const;          ///< Is any mouse button currently pressed?

    Vector xAxisOfRotation() const;                ///< Calculate x-axis rotation in transformed co-ordinates
    Vector yAxisOfRotation() const;                ///< Calculate y-axis rotation in transformed co-ordinates
    Vector axisOfRotation(const Vector &v) const;  ///< Calculate rotation axis in transformed co-ordinates
    Vector dragPos(const int x,const int y) const; ///< Convert from screen co-ordinates to world co-ordinates


    Matrix    _viewMatrix;          ///< Current transformation matrix
    Matrix    _viewMatrixInverse;   ///< Current transformation matrix inverse
    GltOrtho  _ortho;               ///< Current viewing setup

private:

    bool      _mouseZoom;           ///< Mouse zooming enabled
    bool      _mousePan;            ///< Mouse panning enabled
    bool      _mouseRotate;         ///< Mouse rotation enabled

    MouseMode _mouseMode;           ///< Current mouse mode

    Vector    _referencePoint;      ///< Reference point for zooming and rotation

    //

    bool   _mouseLeft;
    bool   _mouseMiddle;
    bool   _mouseRight;
    int    _mouseX;
    int    _mouseY;
    bool   _wasIdle;                ///< Stop idle while manipulating with mouse
    int    _oldCursor;              ///< Remember old cursor while manipulating
    Vector _dragPosPrev;            ///< Previous drag position
};

#endif
