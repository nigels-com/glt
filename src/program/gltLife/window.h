#ifndef GLT_LIFE_WINDOW
#define GLT_LIFE_WINDOW

/*

  GltLife
  C++ OpenGL Implementation of Conways Game of Life
  http://www.nigels.com/glt/gltlife/

  Based on CAEL 1.5 by Abraham Egnor
  http://www.ugcs.caltech.edu/~abe/cael.html

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

#include <glutm/winexam.h>
#include <glt/fontasci.h>
#include <node/text.h>

#include "world.h"
#include "draw.h"

class GltLifeWindow : public GlutWindowExaminer
{
public:
    GltLifeWindow
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );

    virtual ~GltLifeWindow();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnReshape(int w, int h);
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);
    void OnMenu(int value);
    void OnVisibility(int visible);

    Vector getReferencePoint(int x,int y,const Vector &pos,const Matrix &modelView,const Matrix &modelViewInverse) const;

protected:

    void setGrid(unsigned short width,unsigned short height);
    void setRun(const bool run);
    void setDemo(const bool demo);
    void setFullscreen(const bool fullscreen);

    void clear(GLenum buffer = GL_NONE);

    bool         _run;
    bool         _step;
    bool         _mutate;
    bool         _fullscreen;
    bool         _demoMode;
    int          _demoLifeform;

    GltLifeWorld               _arena;
    GltLifeDraw                _graphics;
    GltFontAscii               _font;
    GltTextOverlay             _info;

    static const std::string _messageText;
    static const std::string _helpText;

    typedef enum
    {
        CELL_TITLE_PAGE,
        CELL_HELP_PAGE,
        CELL_STATUS_PAGE,
        CELL_EMPTY_PAGE,
        CELL_MODE_PIXELS,
        CELL_MODE_CAEL,
        CELL_MODE_BLEND,
        CELL_FULLSCREEN,
        CELL_WINDOW,
        CELL_TOGGLEFULL,
        CELL_DEMO,
        CELL_RESET,
        CELL_MUTATE,
        CELL_RUN,
        CELL_STEP,
        CELL_DEATH_NONE,
        CELL_DEATH_5,
        CELL_DEATH_10,
        CELL_DEATH_20,
        CELL_DEATH_50,
        CELL_DEATH_100,
        CELL_GRID_10,
        CELL_GRID_50,
        CELL_GRID_100,
        CELL_GRID_200,
        CELL_GRID_500,
        CELL_RULES_CLASSIC,
        CELL_RULES_3_4,
        CELL_RULES_CRYSTALS,
        CELL_EXAMPLE            // Must be last becase we use a range of values
    } MenuCallbacks;

    int _infoPage;

    void makePage();
};

#endif
