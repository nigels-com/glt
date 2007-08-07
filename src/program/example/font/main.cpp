/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000 Nigel Stewart
  Email: nigels@nigels.com   WWW: http://www.nigels.com/glt/

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

#include <glutm/main.h>
#include <glutm/window.h>
#include <glutm/winexam.h>
#include <glutm/menu.h>

#include <glt/texture.h>
#include <glt/fontasci.h>
#include <glt/fonttex.h>
#include <glt/error.h>
#include <glt/rgb.h>

#include <fonts/fonts.h>

#include <node/shape.h>
#include <node/text.h>
#include <node/tiled.h>

#include "textures.h"

#include <misc/string.h>

#include <string>
#include <fstream>
using namespace std;

class GlutWindowTextDemo : public GlutWindowExaminer
{
public:
    GlutWindowTextDemo
    (
        int width                = 400,
        int height               = 400,
        int x                    = xDefault,
        int y                    = yDefault
    );
   ~GlutWindowTextDemo();

   void OnOpen();
   void OnClose();
   void OnDisplay();
   void OnMenu(int value);

protected:

    GltFontAscii        _font;
    GltFontTexture      _fontT;
    GltTextOverlay      _info;
    GltTextOverlay      _infoT;
    bool                _asciiFont;

    GltTexture          _texture;
    GltTextureViewport  _background;
    GlutMenu            _menu;

    typedef enum
    {
        TEXT_DEMO_ANTIQUE14,
        TEXT_DEMO_ART16,
        TEXT_DEMO_BROADWAY14,
        TEXT_DEMO_COURIER14,
        TEXT_DEMO_ISO14,
        TEXT_DEMO_LCD14,
        TEXT_DEMO_MAC16,
        TEXT_DEMO_MAC8,
        TEXT_DEMO_POLICE16,
        TEXT_DEMO_ROMAN14,
        TEXT_DEMO_SANSERIF14,
        TEXT_DEMO_SPRANTO14,
        TEXT_DEMO_THINDEMO14,
        TEXT_DEMO_VGA14,
        TEXT_DEMO_VGA8,
        TEXT_DEMO_WIGGLY16,

        TEXT_DEMO_COURIER,
        TEXT_DEMO_COURIER_BOLD,
        TEXT_DEMO_HELVETICA,
        TEXT_DEMO_HELVETICA_BOLD,
        TEXT_DEMO_PALATINO,
        TEXT_DEMO_PALATINO_ITALIC,
        TEXT_DEMO_PALATINO_BOLD,
        TEXT_DEMO_TIMESROMAN,
        TEXT_DEMO_ZAPFCHANCERY,

        TEXT_DEMO_SHADOW,
        TEXT_DEMO_BORDER,

        TEXT_DEMO_FADE0,
        TEXT_DEMO_FADE10,
        TEXT_DEMO_FADE20,
        TEXT_DEMO_FADE30,
        TEXT_DEMO_FADE40,
        TEXT_DEMO_FADE50,
        TEXT_DEMO_FADE75,
        TEXT_DEMO_FADE100,

        TEXT_DEMO_ALIGN_LEFT,
        TEXT_DEMO_ALIGN_HCENTER,
        TEXT_DEMO_ALIGN_RIGHT,
        TEXT_DEMO_ALIGN_TOP,
        TEXT_DEMO_ALIGN_VCENTER,
        TEXT_DEMO_ALIGN_BOTTOM,

        TEXT_DEMO_ARMY,
        TEXT_DEMO_CARVING,
        TEXT_DEMO_ICE,
        TEXT_DEMO_STONE,

        TEXT_DEMO_SCHEME_GREY,
        TEXT_DEMO_SCHEME_GREY2,
        TEXT_DEMO_SCHEME_RED,
        TEXT_DEMO_SCHEME_GREEN,
        TEXT_DEMO_SCHEME_BLUE,
        TEXT_DEMO_SCHEME_YELLOW

    } MenuCallbacks;
};

//

GlutWindowTextDemo::GlutWindowTextDemo(int width,int height,int x,int y)
: GlutWindowExaminer("GLT Font Demo",width,height,x,y,GLUT_RGBA | GLUT_DOUBLE),
  _info(_font,_viewport),
  _infoT(_fontT,_viewport),
  _asciiFont(false),
  _background(_texture,true)
{
}

GlutWindowTextDemo::~GlutWindowTextDemo()
{
}

void
GlutWindowTextDemo::OnOpen()
{
    _infoT.alignHorizontal() = _info.alignHorizontal() = GLT_ALIGN_HCENTER;
    _infoT.alignVertical()   = _info.alignVertical()   = GLT_ALIGN_VCENTER;

    string banner =
        "GLT Font Demo\n" \
        "[Left Mouse Click]\n";

    // VGA font text

    string text1 = banner;
    for (int i=0; i<256; i++)
    {
        if (i%16==0)
            text1 += "\n";
        text1 += (i==0 || i=='\n' ? ' ' : char(i));
    }
    text1 += '\n';

    _info.text() = text1;

    // Texture font text
    string text2 = banner;
    text2 += "\nThe quick brown fox jumps\nover the lazy brown dog.\n";

    _infoT.text() = text2;

    // Initialise the font object(s)

    _font.init(iso14Font);
    _fontT.init(HelveticaBoldFont);

    // Initialise background texture

    _texture.init(iceTexture);

    // Initialise OpenGL

    glClearColor(0.5, 0.5, 0.5, 0.0);

    // Create menus

    GlutMenu &font = _menu.subMenu();

        GlutMenu &fontV = _menu.subMenu();
        fontV.addEntry("Antique"  ,TEXT_DEMO_ANTIQUE14);
        fontV.addEntry("Art"      ,TEXT_DEMO_ART16);
        fontV.addEntry("Broadway" ,TEXT_DEMO_BROADWAY14);
        fontV.addEntry("Courier"  ,TEXT_DEMO_COURIER14);
        fontV.addEntry("ISO"      ,TEXT_DEMO_ISO14);
        fontV.addEntry("LCD"      ,TEXT_DEMO_LCD14);
        fontV.addEntry("Mac Big"  ,TEXT_DEMO_MAC16);
        fontV.addEntry("Mac Small",TEXT_DEMO_MAC8);
        fontV.addEntry("Police"   ,TEXT_DEMO_POLICE16);
        fontV.addEntry("Roman"    ,TEXT_DEMO_ROMAN14);
        fontV.addEntry("Sanserif" ,TEXT_DEMO_SANSERIF14);
        fontV.addEntry("Spranto"  ,TEXT_DEMO_SPRANTO14);
        fontV.addEntry("Thindemo" ,TEXT_DEMO_THINDEMO14);
        fontV.addEntry("VGA Big"  ,TEXT_DEMO_VGA14);
        fontV.addEntry("VGA Small",TEXT_DEMO_VGA8);
        fontV.addEntry("Wiggly"   ,TEXT_DEMO_WIGGLY16);

        GlutMenu &fontT = _menu.subMenu();
        fontT.addEntry("Courier"        ,TEXT_DEMO_COURIER);
        fontT.addEntry("Courier Bold"   ,TEXT_DEMO_COURIER_BOLD);
        fontT.addEntry("Helvetica"      ,TEXT_DEMO_HELVETICA);
        fontT.addEntry("Helvetica Bold" ,TEXT_DEMO_HELVETICA_BOLD);
        fontT.addEntry("Palatino"       ,TEXT_DEMO_PALATINO);
        fontT.addEntry("Palatino Italic",TEXT_DEMO_PALATINO_ITALIC);
        fontT.addEntry("Palatino Bold"  ,TEXT_DEMO_PALATINO_BOLD);
        fontT.addEntry("Times Roman"    ,TEXT_DEMO_TIMESROMAN);
        fontT.addEntry("Zapf Chancery"  ,TEXT_DEMO_ZAPFCHANCERY);

        font.addEntry("VGA"    ,fontV);
        font.addEntry("Texture",fontT);

    GlutMenu &alignH = _menu.subMenu();
    alignH.addEntry("Left"  ,TEXT_DEMO_ALIGN_LEFT);
    alignH.addEntry("Center",TEXT_DEMO_ALIGN_HCENTER);
    alignH.addEntry("Right" ,TEXT_DEMO_ALIGN_RIGHT);

    GlutMenu &alignV = _menu.subMenu();
    alignV.addEntry("Top"    ,TEXT_DEMO_ALIGN_TOP);
    alignV.addEntry("Center" ,TEXT_DEMO_ALIGN_VCENTER);
    alignV.addEntry("Bottom" ,TEXT_DEMO_ALIGN_BOTTOM);

    GlutMenu &fade = _menu.subMenu();
    fade.addEntry("  0%",TEXT_DEMO_FADE0);
    fade.addEntry(" 10%",TEXT_DEMO_FADE10);
    fade.addEntry(" 20%",TEXT_DEMO_FADE20);
    fade.addEntry(" 30%",TEXT_DEMO_FADE30);
    fade.addEntry(" 40%",TEXT_DEMO_FADE40);
    fade.addEntry(" 50%",TEXT_DEMO_FADE50);
    fade.addEntry(" 75%",TEXT_DEMO_FADE75);
    fade.addEntry("100%",TEXT_DEMO_FADE100);

    GlutMenu &back = _menu.subMenu();
    back.addEntry("Army",   TEXT_DEMO_ARMY);
    back.addEntry("Carving",TEXT_DEMO_CARVING);
    back.addEntry("Ice",    TEXT_DEMO_ICE);
    back.addEntry("Stone",  TEXT_DEMO_STONE);

    GlutMenu &scheme = _menu.subMenu();
    scheme.addEntry("Grey"  ,TEXT_DEMO_SCHEME_GREY);
    scheme.addEntry("Grey2" ,TEXT_DEMO_SCHEME_GREY2);
    scheme.addEntry("Red"   ,TEXT_DEMO_SCHEME_RED);
    scheme.addEntry("Green" ,TEXT_DEMO_SCHEME_GREEN);
    scheme.addEntry("Blue"  ,TEXT_DEMO_SCHEME_BLUE);
    scheme.addEntry("Yellow",TEXT_DEMO_SCHEME_YELLOW);

    _menu.addEntry("Font",font);
    _menu.addEntry("Horizontal",alignH);
    _menu.addEntry("Vertical"  ,alignV);
    _menu.addEntry("Fade"      ,fade);
    _menu.addEntry("Shadow"    ,TEXT_DEMO_SHADOW);
    _menu.addEntry("Border"    ,TEXT_DEMO_BORDER);
    _menu.addEntry("Background",back);
    _menu.addEntry("Scheme"    ,scheme);
    _menu.addEntry("Quit"      ,MENU_CLOSE);

    _menu.attach();
}

void
GlutWindowTextDemo::OnClose()
{
    _fontT.clear();
    _font.init(NULL);
    _texture.init(NULL);
    _menu.reset();
}

void
GlutWindowTextDemo::OnDisplay()
{
    GLERROR

    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    GLERROR

    _background.draw();

    if (_asciiFont)
        _info.draw();
    else
        _infoT.draw();
}

void
GlutWindowTextDemo::OnMenu(int value)
{
    GlutWindow::OnMenu(value);

    GltTextOverlay &info = _asciiFont ? _info : _infoT;

    switch (value)
    {
    case TEXT_DEMO_ANTIQUE14:   _font.init(antique14Font);  _asciiFont = true; break;
    case TEXT_DEMO_ART16:       _font.init(art16Font);      _asciiFont = true; break;
    case TEXT_DEMO_BROADWAY14:  _font.init(broadway14Font); _asciiFont = true; break;
    case TEXT_DEMO_COURIER14:   _font.init(courier14Font);  _asciiFont = true; break;
    case TEXT_DEMO_ISO14:       _font.init(iso14Font);      _asciiFont = true; break;
    case TEXT_DEMO_LCD14:       _font.init(lcd14Font);      _asciiFont = true; break;
    case TEXT_DEMO_MAC16:       _font.init(mac16Font);      _asciiFont = true; break;
    case TEXT_DEMO_MAC8:        _font.init(mac8Font);       _asciiFont = true; break;
    case TEXT_DEMO_POLICE16:    _font.init(police16Font);   _asciiFont = true; break;
    case TEXT_DEMO_ROMAN14:     _font.init(roman14Font);    _asciiFont = true; break;
    case TEXT_DEMO_SANSERIF14:  _font.init(sanserif14Font); _asciiFont = true; break;
    case TEXT_DEMO_SPRANTO14:   _font.init(spranto14Font);  _asciiFont = true; break;
    case TEXT_DEMO_THINDEMO14:  _font.init(thindemo14Font); _asciiFont = true; break;
    case TEXT_DEMO_VGA14:       _font.init(vga14Font);      _asciiFont = true; break;
    case TEXT_DEMO_VGA8:        _font.init(vga8Font);       _asciiFont = true; break;
    case TEXT_DEMO_WIGGLY16:    _font.init(wiggly16Font);   _asciiFont = true; break;

    case TEXT_DEMO_COURIER:         _fontT.init(CourierFont);                  _asciiFont = false; break;
    case TEXT_DEMO_COURIER_BOLD:    _fontT.init(CourierBoldFont);              _asciiFont = false; break;
    case TEXT_DEMO_HELVETICA:       _fontT.init(HelveticaFont);                _asciiFont = false; break;
    case TEXT_DEMO_HELVETICA_BOLD:  _fontT.init(HelveticaBoldFont);            _asciiFont = false; break;
    case TEXT_DEMO_PALATINO:        _fontT.init(PalatinoRomanFont);            _asciiFont = false; break;
    case TEXT_DEMO_PALATINO_ITALIC: _fontT.init(PalatinoItalicFont);           _asciiFont = false; break;
    case TEXT_DEMO_PALATINO_BOLD:   _fontT.init(PalatinoBoldFont);             _asciiFont = false; break;
    case TEXT_DEMO_TIMESROMAN:      _fontT.init(TimesRomanFont);               _asciiFont = false; break;
    case TEXT_DEMO_ZAPFCHANCERY:    _fontT.init(ZapfChanceryMediumItalicFont); _asciiFont = false; break;

    case TEXT_DEMO_SHADOW:      info.shadow() = !info.shadow(); break;
    case TEXT_DEMO_BORDER:      info.border() = !info.border(); break;

    case TEXT_DEMO_FADE0:   info.fadeColor().alpha() = 0.00; break;
    case TEXT_DEMO_FADE10:  info.fadeColor().alpha() = 0.10; break;
    case TEXT_DEMO_FADE20:  info.fadeColor().alpha() = 0.20; break;
    case TEXT_DEMO_FADE30:  info.fadeColor().alpha() = 0.30; break;
    case TEXT_DEMO_FADE40:  info.fadeColor().alpha() = 0.40; break;
    case TEXT_DEMO_FADE50:  info.fadeColor().alpha() = 0.50; break;
    case TEXT_DEMO_FADE75:  info.fadeColor().alpha() = 0.75; break;
    case TEXT_DEMO_FADE100: info.fadeColor().alpha() = 1.00; break;

    case TEXT_DEMO_ALIGN_LEFT:      info.alignHorizontal() = GLT_ALIGN_LEFT;    break;
    case TEXT_DEMO_ALIGN_HCENTER:   info.alignHorizontal() = GLT_ALIGN_HCENTER; break;
    case TEXT_DEMO_ALIGN_RIGHT:     info.alignHorizontal() = GLT_ALIGN_RIGHT;   break;

    case TEXT_DEMO_ALIGN_TOP:       info.alignVertical() = GLT_ALIGN_TOP;     break;
    case TEXT_DEMO_ALIGN_VCENTER:   info.alignVertical() = GLT_ALIGN_VCENTER; break;
    case TEXT_DEMO_ALIGN_BOTTOM:    info.alignVertical() = GLT_ALIGN_BOTTOM;  break;


    case TEXT_DEMO_ARMY:        _texture.init(armyTexture);    break;
    case TEXT_DEMO_CARVING:     _texture.init(carvingTexture); break;
    case TEXT_DEMO_ICE:         _texture.init(iceTexture);     break;
    case TEXT_DEMO_STONE:       _texture.init(stoneTexture);   break;

    case TEXT_DEMO_SCHEME_GREY:
        {
            info.color()       = white;
            info.shadowColor() = black;
            info.borderColor() = black;
            info.fadeColor()   = black;
            info.fadeColor().alpha() = 0.3;
        }
        break;

    case TEXT_DEMO_SCHEME_GREY2:
        {
            info.color()       = grey;
            info.shadowColor() = black;
            info.borderColor() = black;
            info.fadeColor()   = grey;
            info.fadeColor().alpha() = 0.1;
        }
        break;

    case TEXT_DEMO_SCHEME_RED:
        {
            info.color()       = orangeRed;
            info.shadowColor() = black;
            info.borderColor() = black;
            info.fadeColor()   = darkRed;
            info.fadeColor().alpha() = 0.2;
        }
        break;

    case TEXT_DEMO_SCHEME_GREEN:
        {
            info.color()       = lightGreen;
            info.shadowColor() = black;
            info.borderColor() = darkGreen;
            info.fadeColor()   = darkGreen;
            info.fadeColor().alpha() = 0.3;
        }
        break;

    case TEXT_DEMO_SCHEME_BLUE:
        {
            info.color()       = lightSteelBlue;
            info.shadowColor() = black;
            info.borderColor() = black;
            info.fadeColor()   = darkGrey;
            info.fadeColor().alpha() = 0.3;
        }
        break;

    case TEXT_DEMO_SCHEME_YELLOW:
        {
            info.color()       = yellow;
            info.shadowColor() = black;
            info.borderColor() = black;
            info.fadeColor()   = blue;
            info.fadeColor().alpha() = 0.3;
        }
        break;
    }

    postRedisplay();
}

bool GlutMain(const std::vector<std::string> &arg)
{
    GlutWindow *main = new GlutWindowTextDemo();
    main->open();

    return true;
}
