#ifndef GLT_LIGHT_H
#define GLT_LIGHT_H

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
    \brief OpenGL Light Source Class
    \ingroup GLT

    $Id: light.h,v 2.0 2004/02/08 19:44:11 nigels Exp $

    $Log: light.h,v $
    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.11  2003/03/06 12:20:53  nigels
    Documentation refinements

    Revision 1.10  2002/11/27 00:57:28  nigels
    expand

    Revision 1.9  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.8  2002/10/07 16:33:35  nigels
    Added CVS info


*/

#include <glt/gl.h>

#include <iosfwd>

#include <math/vector3.h>
#include <glt/color.h>

///////////////////////////// GltLight ///////////////////////////////////////

/*! \class GltLight
    \brief OpenGL Light Source Class
    \ingroup GLT

    Convenient manipulation of OpenGL lightsource configuration.
*/

class GltLight
{
public:

    GltLight(const GLenum light = GL_LIGHT0,const bool getIt = false); ///< Constructor
    ~GltLight();                                                       ///< Destructor

    void get();                                     ///< Get the current OpenGL light settings
    void set() const;                               ///< Set the current OpenGL light settings

    GLenum   &light();                              ///< OpenGL light source identifier
    bool     &enabled();                            ///< Enabled
    GltColor &ambient();                            ///< Ambient contribution
    GltColor &diffuse();                            ///< Diffuse contribution
    GltColor &specular();                           ///< Specular contribution
    Vector   &position();                           ///< Light source position
    Vector   &spotDirection();                      ///< Light source direction
    GLfloat  &spotExponent();                       ///< Spotlight exponent
    GLfloat  &spotCutoff();                         ///< Spotlight cutoff radius
    GLfloat  &attenutationConstant();               ///< Constant attenuation factor
    GLfloat  &attenutationLinear();                 ///< Linear attenuation factor
    GLfloat  &attenutationQuadratic();              ///< Quadratic attenuation factor

    const GLenum   &light() const;                  ///< OpenGL light source identifier
    const bool     &enabled() const;                ///< Enabled
    const GltColor &ambient() const;                ///< Ambient contribution
    const GltColor &diffuse() const;                ///< Diffuse contribution
    const GltColor &specular() const;               ///< Specular contribution
    const Vector   &position() const;               ///< Light source position
    const Vector   &spotDirection() const;          ///< Light source direction
    const GLfloat  &spotExponent() const;           ///< Spotlight exponent
    const GLfloat  &spotCutoff() const;             ///< Spotlight cutoff radius
    const GLfloat  &attenutationConstant() const;   ///< Constant attenuation factor
    const GLfloat  &attenutationLinear() const;     ///< Linear attenuation factor
    const GLfloat  &attenutationQuadratic() const;  ///< Quadratic attenuation factor

private:

    GLenum  _light;
    bool    _enabled;

    GltColor _ambient;
    GltColor _diffuse;
    GltColor _specular;
    Vector   _position;
    Vector   _spotDirection;
    GLfloat  _spotExponent;
    GLfloat  _spotCutoff;
    GLfloat  _attenuationConstant;
    GLfloat  _attenuationLinear;
    GLfloat  _attenuationQuadratic;

    const static GltColor _ambientDefault;
    const static GltColor _diffuseDefault;
    const static GltColor _specularDefault;
    const static Vector   _positionDefault;
    const static Vector   _spotDirectionDefault;
    const static GLfloat  _spotExponentDefault;
    const static GLfloat  _spotCutoffDefault;
    const static GLfloat  _attenuationConstantDefault;
    const static GLfloat  _attenuationLinearDefault;
    const static GLfloat  _attenuationQuadraticDefault;
};

#endif
