#include "color.h"

/*! \file
    \ingroup GLT

    $Id: color.cpp,v 2.3 2009/06/22 05:23:19 nigels Exp $
*/

#include <string>
#include <algorithm>

#include <cassert>
#include <cstdio>
#include <cstring>

using namespace std;

#include <glt/rgb.h>
#include <glt/error.h>

#include <misc/hex.h>

#include <math/vector3.h>
#include <math/matrix4.h>

GltColor::GltColor()
: Vector4(Vector0,1.0)
{
}

GltColor::GltColor(const float red,const float green,const float blue,const float alpha)
: Vector4(red,green,blue,alpha)
{
}

GltColor::GltColor(const double red,const double green,const double blue,const double alpha)
: Vector4(red,green,blue,alpha)
{
}

GltColor::GltColor(const int red,const int green,const int blue,const int alpha)
: Vector4(red,green,blue,alpha)
{
}

GltColor::GltColor(const GltColor &col,const real alpha)
: Vector4(col)
{
    w() = alpha;
}

GltColor::GltColor(const Vector3 &col)
: Vector4(col)
{
}

GltColor::GltColor(const Vector4 &col)
: Vector4(col)
{
}

GltColor::GltColor(const GltColor &col)
: Vector4(col)
{
}

GltColor::GltColor(const string &name)
{
    w() = 1.0;

    // Convert from HTML style color string

    if (name.size()>=7)
    {
        if (name[0]=='#')
        {
            const int r = fromHex(name[1],name[2]);
            const int g = fromHex(name[3],name[4]);
            const int b = fromHex(name[5],name[6]);

            red()   = real(r)/255.0;
            green() = real(g)/255.0;
            blue()  = real(b)/255.0;

            return;
        }
    }

    #ifdef GLT_COLOR_NAMES

    // Do a binary search through the list of names

    int i=0;
    int j=_rgbSize;

    for (;;)
    {
        int k = ((j-i)>>1)+i;
        const int res = strcmp(name.c_str(),_rgbName[k]);

        if (res<0)
            j = k;
        else
            if (res>0)
                i = k+1;
            else
            {
                operator=(*_rgbValue[k]);
                return;
            }

        if (i==k && j==k || i==_rgbSize)
        {
            assert(!"Color not found");
            operator=(::black);
            return;
        }
    }

    #endif
}

GltColor::~GltColor()
{
}

GltColor &
GltColor::operator=(const GltColor &col)
{
    red()   = col.red();
    green() = col.green();
    blue()  = col.blue();
    alpha() = col.alpha();

    return *this;
}

const real &
GltColor::operator[](const int i) const
{
    return Vector4::operator[](i);
}

real &
GltColor::operator[](const int i)
{
    return Vector4::operator[](i);
}

GltColor::operator real *()
{
    return Vector4::operator real *();
}

GltColor::operator const real *() const
{
    return Vector4::operator const real *();
}

      real &GltColor::red()    { return x();    }
      real &GltColor::green()  { return y();    }
      real &GltColor::blue()   { return z();    }
      real &GltColor::alpha()  { return w();    }

const real &GltColor::red()    const { return x();    }
const real &GltColor::green()  const { return y();    }
const real &GltColor::blue()   const { return z();    }
const real &GltColor::alpha()  const { return w();    }

const real
GltColor::brightness() const
{
    // (from Colorspace FAQ)
    //  Y = 0.212671 * R + 0.715160 * G + 0.072169 * B;

    return 0.212671*red() + 0.715160*green() + 0.072169*blue();
}

void
GltColor::toHSV(real &h,real &s,real &v) const
{
    // Based on http://www.cs.rit.edu/~ncs/color/t_convert.html

    const real min = std::min(red(),std::min(green(),blue()));
    const real max = std::max(red(),std::max(green(),blue()));

    v = max;

    const real delta = max-min;

    if (max!=0.0)
        s = delta/max;
    else
    {
        // Black
        h = 0.0;
        s = 0.0;
        return;
    }

    if (delta==0.0)
    {
        h = 0.0;
        s = 0.0;
    }
    else
        if (red()==max)
            h = (green()-blue()) / delta;           // between yellow & magenta
        else
            if(green()==max)
                h = 2.0 + (blue()-red())/delta;     // between cyan & yellow
            else
                h = 4.0 + (red()-green())/delta;    // between magenta & cyan

    // Scale h to degrees

    h *= 60;

    if (h<0.0)
        h += 360.0;
}

void
GltColor::fromHSV(const real h,const real s,const real v)
{
    // Based on http://www.cs.rit.edu/~ncs/color/t_convert.html

    // Achromatic case (grey)

    if (s==0.0)
    {
        red() = green() = blue() = v;
        return;
    }


    const real hue = h/60.0;    // sector 0 to 5
    const int  i   = int(floor(hue));
    const real f   = hue-i;     // factorial part of h
    const real p = v*(1-s);
    const real q = v*(1-s*f);
    const real t = v*(1-s*(1-f));

    switch (i)
    {
    case 0:
        red()   = v;
        green() = t;
        blue()  = p;
        break;
    case 1:
        red()   = q;
        green() = v;
        blue()  = p;
        break;
    case 2:
        red()   = p;
        green() = v;
        blue()  = t;
        break;
    case 3:
        red()   = p;
        green() = q;
        blue()  = v;
        break;
    case 4:
        red()   = t;
        green() = p;
        blue()  = v;
        break;
    default:        // case 5:
        red()   = v;
        green() = p;
        blue()  = q;
        break;
    }
}

//

const bool
GltColor::isGrey() const
{
    return red()==green() && green()==blue();
}

std::string
GltColor::html() const
{
    const int r = clamp<int>((int) floor(red()  *255.0+0.5),0,255);
    const int g = clamp<int>((int) floor(green()*255.0+0.5),0,255);
    const int b = clamp<int>((int) floor(blue() *255.0+0.5),0,255);

    char buffer[8];
    sprintf(buffer,"#%02X%02X%02X",r,g,b);
    return buffer;
}

bool GltColor::operator< (const GltColor &c) const
{
    if (red()!=c.red())     return red()<c.red();
    if (green()!=c.green()) return green()<c.green();
    return blue()<c.blue();
}

bool GltColor::operator> (const GltColor &c) const
{
    if (red()!=c.red())     return red()>c.red();
    if (green()!=c.green()) return green()>c.green();
    return blue()>c.blue();
}

bool GltColor::operator==(const GltColor &c) const
{
    return red()==c.red() && green()==c.green() && blue()==c.blue();
}

/*!
    \brief Scale color
    \ingroup GLT
*/
GltColor operator*(const GltColor  &c, const real x)
{
    return GltColor(c.red()*x,c.green()*x,c.blue()*x,c.alpha()*x);
}

/*!
    \brief Scale color
    \ingroup GLT
*/
GltColor operator/(const GltColor  &c, const real x)
{
    const double s = 1.0/x;
    return GltColor(c.red()*s,c.green()*s,c.blue()*s,c.alpha()*s);
}

/*!
    \brief Scale color
    \ingroup GLT
*/
GltColor operator*(const real      x, const GltColor &c)
{
    return GltColor(c.red()*x,c.green()*x,c.blue()*x,c.alpha()*x);
}

/*!
    \brief Add red, green and blue components
    \ingroup GLT
*/
GltColor operator+(const GltColor &c1, const GltColor &c2)
{
    return GltColor(c1.red()+c2.red(),c1.green()+c2.green(),c1.blue()+c2.blue(),c1.alpha()+c2.alpha());
}

/*!
    \brief Subtract red, green and blue components
    \ingroup GLT
*/
GltColor operator-(const GltColor &c1, const GltColor &c2)
{
    return GltColor(c1.red()-c2.red(),c1.green()-c2.green(),c1.blue()-c2.blue(),c1.alpha()-c2.alpha());
}

///////////////////////// OpenGL

#include <glt/gl.h>

void
GltColor::glColor() const
{
    #ifdef GLT_FAST_FLOAT
    ::glColor4fv(operator const real *());
    #else
    ::glColor4dv(operator const real *());
    #endif
}

void
GltColor::glColor(const GLdouble alpha) const
{
    #ifdef GLT_FAST_FLOAT
    ::glColor4f(red(),green(),blue(),GLfloat(alpha));
    #else
    ::glColor4d(red(),green(),blue(),alpha);
    #endif
}

void
GltColor::glClearColor() const
{
    ::glClearColor((GLfloat) red(),(GLfloat) green(),(GLfloat) blue(),(GLfloat) alpha());
}

void
GltColor::glFogColor() const
{
    const GLfloat col[4] = { (GLfloat) x(), (GLfloat) y(), (GLfloat) z(), (GLfloat) alpha() };
    ::glFogfv(GL_FOG_COLOR, col);
}

void
GltColor::glMaterial(const GLenum face,const GLenum field) const
{
    assert(face==GL_FRONT_AND_BACK || face==GL_FRONT || face==GL_BACK);
    assert(field==GL_AMBIENT || field==GL_DIFFUSE || field==GL_SPECULAR || field==GL_EMISSION);

    GLERROR

    const GLfloat val[4] = { (GLfloat) x(), (GLfloat) y(), (GLfloat) z(), (GLfloat) alpha() };
    ::glMaterialfv(face,field,val);

    GLERROR
}

void
GltColor::glLight(const GLenum light,const GLenum field) const
{
    assert(light>=GL_LIGHT0 && light<=GL_LIGHT7);
    assert(field==GL_AMBIENT || field==GL_DIFFUSE || field==GL_SPECULAR || field==GL_POSITION || field==GL_SPOT_DIRECTION);

    GLERROR

    const GLfloat val[4] = { (float) x(), (float) y(), (float) z(), (float) alpha() };
    ::glLightfv(light,field,val);

    GLERROR
}

void
GltColor::glGet()
{
    GLERROR

    #ifdef GLT_FAST_FLOAT
    ::glGetFloatv(GL_CURRENT_COLOR,operator real *());
    #else
    ::glGetDoublev(GL_CURRENT_COLOR,operator real *());
    #endif

    GLERROR
}

void
GltColor::glGetMaterial(const GLenum face,const GLenum field)
{
    assert(face==GL_FRONT_AND_BACK || face==GL_FRONT || face==GL_BACK);
    assert(field==GL_AMBIENT || field==GL_DIFFUSE || field==GL_SPECULAR || field==GL_EMISSION);

    GLERROR

    GLfloat val[4];
    ::glGetMaterialfv(face,field,val);
    x() = val[0]; y() = val[1]; z() = val[2]; alpha() = val[3];

    GLERROR
}

void
GltColor::glGetLight(const GLenum light,const GLenum field)
{
    assert(light>=GL_LIGHT0 && light<=GL_LIGHT7);
    assert(field==GL_AMBIENT || field==GL_DIFFUSE || field==GL_SPECULAR || field==GL_POSITION || field==GL_SPOT_DIRECTION);

    GLERROR

    GLfloat val[4];
    ::glGetLightfv(light,field,val);
    x() = val[0]; y() = val[1]; z() = val[2]; alpha() = val[3];

    GLERROR
}

///////////////////////////////////////////////////////////

GltClearColor::GltClearColor(bool getIt)
{
    if (getIt)
        get();
}

GltClearColor::~GltClearColor()
{
}

void
GltClearColor::get()
{
    #ifdef GLT_FAST_FLOAT
    ::glGetFloatv(GL_COLOR_CLEAR_VALUE,operator real *());
    #else
    ::glGetDoublev(GL_COLOR_CLEAR_VALUE,operator real *());
    #endif
}

void
GltClearColor::set() const
{
    GltColor::glClearColor();
}

void
GltClearColor::set(const GltColor &col)
{
    GltColor::operator=(col);
    GltColor::glClearColor();
}
