#ifndef NODE_INTERP_H
#define NODE_INTERP_H

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
    \brief   Interpolation Nodes
    \ingroup Node
*/

#include <glt/colmap.h>

#include <node/shape.h>
#include <misc/timer.h>

class GltColor;
class Matrix;

///////////////////////////// GltInterpolator ///////////////////////////////////////

/*! \class   GltInterpolator
    \brief   Interpolator Base-Class
    \ingroup Node
*/

class GltInterpolator : public GltShape
{
public:
             GltInterpolator();         ///< Constructor
    virtual ~GltInterpolator();         ///< Destructor

    void start(const double duration,const bool loop = false); ///< Start in real-time mode
    void start(const bool loop = false);                       ///< Start in per-frame mode
    void stop();                                               ///< Stop the interpolator
    void restart(void);                                        ///< Restart the interpolator

    //
    // Get/Set
    //

    const bool   &active()   const;     ///< Interpolator currently active
    const bool   &loop()     const;     ///< Loop mode
    const bool   &realTime() const;     ///< Real-time mode
    const double &duration() const;     ///< Duration of interpolation
    const int    &frame()    const;     ///< Current frame

          bool   &active();             ///< Interpolator currently active
          bool   &loop();               ///< Loop mode
          bool   &realTime();           ///< Real-time mode
          double &duration();           ///< Duration of interpolation
          int    &frame();              ///< Current frame

protected:

    bool          _active;              ///< Interpolator currently active
    bool          _loop;                ///< Loop mode
    bool          _realTime;            ///< Real-time mode
    Timer         _timer;               ///< Real-time timer
    double        _duration;            ///< Duration of interpolation
    int           _frame;               ///< Current frame
};

/////////////////////// GltInterpolatorColor /////////////////////////

/*! \class   GltInterpolatorColor
    \brief   Color Interpolator Node
    \ingroup Node
*/

class GltInterpolatorColor : public GltInterpolator
{
public:
              GltInterpolatorColor(GltColor &color);  ///< Constructor
    virtual  ~GltInterpolatorColor();                 ///< Destructor

    virtual void draw() const;

          GltColorMap &colorMap();          ///< Interpolated color-map
    const GltColorMap &colorMap() const;    ///< Interpolated color-map

private:
    GltColor    &_color;
    GltColorMap  _colorMap;
};

/////////////////////// GltInterpolatorRotation /////////////////////////

/*! \class   GltInterpolatorRotation
    \brief   Rotation Interpolator Node
    \ingroup Node
*/

class GltInterpolatorRotation : public GltInterpolator
{
public:
             GltInterpolatorRotation(Matrix &matrix); ///< Constructor
    virtual ~GltInterpolatorRotation();               ///< Destructor

    virtual void draw() const;

          Vector &axis();           ///< Axis of rotation
    const Vector &axis() const;     ///< Axis of rotation

          Vector &center();         ///< Center of rotation
    const Vector &center() const;   ///< Center of rotation

private:
    Matrix    &_matrix;
    Vector     _axis;
    Vector     _center;
};

#endif
