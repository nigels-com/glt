#include "window.h"

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

#include "lif2src.h"

#include <glt/fontasci.h>
#include <glt/rgb.h>
#include <math/plane.h>
#include <glutm/shape.h>
#include <fonts/fonts.h>

#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

#include "example.h"

GltLifeWindow::GltLifeWindow(int width,int height,int x,int y)
:
  GlutWindowExaminer("gltLife 0.5 - F1 for help",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA),
  _run(false),
  _step(false),
  _mutate(false),
  _fullscreen(false),
  _demoMode(true),
  _demoLifeform(0),
  _graphics(_arena,_viewport),
  _info(_font,_viewport),
  _infoPage(1)
{
}

GltLifeWindow::~GltLifeWindow()
{
}

void
GltLifeWindow::OnOpen()
{
    _font.init(vga8Font);

    _info.color() = white;
    _info.shadow() = true;
    _info.shadowColor() = black;
    _info.fadeColor().alpha() = 0.1;
    _info.border() = true;

    _ortho.zNear()  = 1000.0;
    _ortho.zFar()  = -1000.0;

    setGrid(200,200);

    GlutMenu &info = _leftButtonMenu.subMenu();
    info.addEntry("Credits" ,CELL_TITLE_PAGE);
    info.addEntry("Help"    ,CELL_HELP_PAGE);
    info.addEntry("Status"  ,CELL_STATUS_PAGE);
    info.addEntry("Hide"    ,CELL_EMPTY_PAGE);

    GlutMenu &draw = _leftButtonMenu.subMenu();
    draw.addEntry("Squares" ,CELL_MODE_PIXELS);
    draw.addEntry("CAEL"    ,CELL_MODE_CAEL);
    draw.addEntry("Blend"   ,CELL_MODE_BLEND);

    GlutMenu &grid = _leftButtonMenu.subMenu();
    grid.addEntry("10x10"   ,CELL_GRID_10);
    grid.addEntry("50x50"   ,CELL_GRID_50);
    grid.addEntry("100x100" ,CELL_GRID_100);
    grid.addEntry("200x200" ,CELL_GRID_200);
    grid.addEntry("500x500" ,CELL_GRID_500);

    GlutMenu &rules = _leftButtonMenu.subMenu();
    rules.addEntry("Classic"  ,CELL_RULES_CLASSIC);
    rules.addEntry("3/4"      ,CELL_RULES_3_4);
    rules.addEntry("Crystals" ,CELL_RULES_CRYSTALS);

    GlutMenu &death = _leftButtonMenu.subMenu();
    death.addEntry("None"            ,CELL_DEATH_NONE);
    death.addEntry("5 Generations"   ,CELL_DEATH_5);
    death.addEntry("10 Generations"  ,CELL_DEATH_10);
    death.addEntry("20 Generations"  ,CELL_DEATH_20);
    death.addEntry("50 Generations"  ,CELL_DEATH_50);
    death.addEntry("100 Generations" ,CELL_DEATH_100);

    GlutMenu &example = _leftButtonMenu.subMenu();

    for (int i=0; lifeExamples[i]!=NULL;)
    {
        GlutMenu &subMenu = example.subMenu();
        const char *menuName = (const char *) lifeExamples[i];
        for (int j=0; j<16 && lifeExamples[i]!=NULL; j++,i+=2)
            subMenu.addEntry((const char *) lifeExamples[i],CELL_EXAMPLE+i+1);
        example.addEntry(menuName,subMenu);
    }

    _leftButtonMenu.addEntry("Fullscreen",CELL_TOGGLEFULL);
    _leftButtonMenu.addEntry("Demo"      ,CELL_DEMO);
    _leftButtonMenu.addEntry("Info"      ,info);
    _leftButtonMenu.addEntry("Example"   ,example);
    _leftButtonMenu.addEntry("Draw"      ,draw);
    _leftButtonMenu.addEntry("Run"       ,CELL_RUN);
    _leftButtonMenu.addEntry("Step"      ,CELL_STEP);
    _leftButtonMenu.addEntry("Mutate"    ,CELL_MUTATE);
    _leftButtonMenu.addEntry("Reset"     ,CELL_RESET);
    _leftButtonMenu.addEntry("Grid"      ,grid);
    _leftButtonMenu.addEntry("Rules"     ,rules);
    _leftButtonMenu.addEntry("Cell Death",death);
    _leftButtonMenu.addEntry("Close"     ,MENU_CLOSE);
    _leftButtonMenu.attach();

    glShadeModel(GL_SMOOTH);
    glDisable(GL_LIGHTING);

    #if defined(GLUTM_SAVER)
    setDemo(true);
    #else
    setDemo(false);
    setRun(true);
    #endif
}

void
GltLifeWindow::OnClose()
{
    _leftButtonMenu.reset();
}

void
GltLifeWindow::OnReshape(int w, int h)
{
    GlutWindowExaminer::OnReshape(w,h);

    _ortho.left()   = 0;
    _ortho.right()  = _arena.width();

    _ortho.top()    = 0;
    _ortho.bottom() = _arena.height();

    _ortho.set();

    if (_graphics.mode()==GltLifeDraw::DRAW_LIFE_BLEND)
    {
        clear(GL_FRONT);
    }
    else
    {
        OnDisplay();
        OnPostDisplay();
    }
}

void
GltLifeWindow::OnDisplay()
{
    if (_run || _step)
    {
        _arena.update();
        if (_mutate)
            _arena.mutate();
        _step = false;
    }

    if (_demoMode)
    {
        if (_arena.population()==0 && _arena.generation()==100)
        {
            const int demoLifes = 15;
            const unsigned char *demoLife[demoLifes] =
            {
                ACORN,
                AK47,
                BHEPTPUF,
                BREEDER,
                BTRACK,
                JAWS,
                IRRAT2,
                MAX,
                PULLER,
                RELAY2,
                SBMEM,
                SPIRAL,
                SPARK2PI,
                WING,
                ZIPS
            };

            _demoLifeform = (_demoLifeform+1)%demoLifes;
            _arena.read((void *) demoLife[_demoLifeform]);
        }
        else
            if (_arena.generation()==1000)
                _arena.clear();
    }

    if (_graphics.mode()==GltLifeDraw::DRAW_LIFE_BLEND)
    {
        glDrawBuffer(GL_FRONT);
        _swapBuffers = false;
    }
    else
    {
        clear(GL_BACK);
        glDrawBuffer(GL_BACK);
        _swapBuffers = true;
    }

    _graphics.draw();

    //
    // Text overlay only works in double-buffered mode
    //

    if (_graphics.mode()!=GltLifeDraw::DRAW_LIFE_BLEND)
    {
        makePage();
        _info.draw();
    }
}

void
GltLifeWindow::OnKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':   setRun(!_run);   break;
        case '.':   _step = true;    break;
        case '/':   _arena.clear();  break;
        case 'm':   if (_run) _mutate = !_mutate; else { _arena.mutate(); _mutate = false; } break;
        case 'M':   _arena.mutate(); break;

        case '1':   OnMenu(CELL_MODE_PIXELS); break;
        case '2':   OnMenu(CELL_MODE_CAEL);   break;
        case '3':   OnMenu(CELL_MODE_BLEND);  break;

        case '!':   OnMenu(CELL_TITLE_PAGE);  break;
        case '@':   OnMenu(CELL_HELP_PAGE);   break;
        case '#':   OnMenu(CELL_STATUS_PAGE); break;
        case '$':   OnMenu(CELL_EMPTY_PAGE);  break;

        default:
            GlutWindowExaminer::OnKeyboard(key,x,y);
    }

    postRedisplay();
}

void
GltLifeWindow::OnSpecial(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_F1: _infoPage = (_infoPage+1)%4; break;
        default:
            GlutWindowExaminer::OnSpecial(key,x,y);
    }

    postRedisplay();
}

void
GltLifeWindow::OnMenu(int value)
{
    switch (value)
    {
    case CELL_TITLE_PAGE:   _infoPage = 1; break;
    case CELL_HELP_PAGE:    _infoPage = 2; break;
    case CELL_STATUS_PAGE:  _infoPage = 3; break;
    case CELL_EMPTY_PAGE:   _infoPage = 0; break;

    case CELL_MODE_PIXELS:
        _graphics.setMode(GltLifeDraw::DRAW_LIFE_PIXELS);
        _swapBuffers = true;
        mouseZoom() = true;
        mousePan() = true;
        mouseRotate() = false;
        break;

    case CELL_MODE_CAEL:
        _graphics.setMode(GltLifeDraw::DRAW_LIFE_CAEL);
        _swapBuffers = true;
        mouseZoom() = true;
        mousePan() = true;
        mouseRotate() = false;
        break;

    case CELL_MODE_BLEND:
        _graphics.setMode(GltLifeDraw::DRAW_LIFE_BLEND);
        _swapBuffers = false;
        clear(GL_FRONT);
        mouseZoom() = false;
        mousePan() = false;
        mouseRotate() = false;
        break;

    case CELL_FULLSCREEN: setFullscreen(true);         break;
    case CELL_WINDOW:     setFullscreen(false);        break;
    case CELL_TOGGLEFULL: setFullscreen(!_fullscreen); break;
    case CELL_DEMO:       setDemo(!_demoMode);         break;

    case CELL_RESET:        _arena.clear();  break;
    case CELL_RUN:          setRun(!_run);   break;
    case CELL_STEP:         _step = !_step;  break;
    case CELL_DEATH_NONE:   _arena.lifeTime() =   0; break;
    case CELL_DEATH_5:      _arena.lifeTime() =   5; break;
    case CELL_DEATH_10:     _arena.lifeTime() =  10; break;
    case CELL_DEATH_20:     _arena.lifeTime() =  20; break;
    case CELL_DEATH_50:     _arena.lifeTime() =  50; break;
    case CELL_DEATH_100:    _arena.lifeTime() = 100; break;
    case CELL_GRID_10:      setGrid(10,10);      break;
    case CELL_GRID_50:      setGrid(50,50);      break;
    case CELL_GRID_100:     setGrid(100,100);    break;
    case CELL_GRID_200:     setGrid(200,200);    break;
    case CELL_GRID_500:     setGrid(500,500);    break;

    case CELL_MUTATE:
        if (_run)
            _mutate = !_mutate;
        else
        {
            _arena.mutate();
            _mutate = false;
        }
        break;

    case CELL_RULES_CLASSIC:
        _arena.survivalRule(0) = false;
        _arena.survivalRule(1) = false;
        _arena.survivalRule(2) = true;
        _arena.survivalRule(3) = true;
        _arena.survivalRule(4) = false;
        _arena.survivalRule(5) = false;
        _arena.survivalRule(6) = false;
        _arena.survivalRule(7) = false;
        _arena.survivalRule(8) = false;

        _arena.birthRule(0) = false;
        _arena.birthRule(1) = false;
        _arena.birthRule(2) = false;
        _arena.birthRule(3) = true;
        _arena.birthRule(4) = false;
        _arena.birthRule(5) = false;
        _arena.birthRule(6) = false;
        _arena.birthRule(7) = false;
        _arena.birthRule(8) = false;
        break;

    case CELL_RULES_3_4:
        _arena.survivalRule(0) = false;
        _arena.survivalRule(1) = false;
        _arena.survivalRule(2) = false;
        _arena.survivalRule(3) = true;
        _arena.survivalRule(4) = true;
        _arena.survivalRule(5) = false;
        _arena.survivalRule(6) = false;
        _arena.survivalRule(7) = false;
        _arena.survivalRule(8) = false;

        _arena.birthRule(0) = false;
        _arena.birthRule(1) = false;
        _arena.birthRule(2) = false;
        _arena.birthRule(3) = true;
        _arena.birthRule(4) = true;
        _arena.birthRule(5) = false;
        _arena.birthRule(6) = false;
        _arena.birthRule(7) = false;
        _arena.birthRule(8) = false;
        break;

    case CELL_RULES_CRYSTALS:
        _arena.survivalRule(0) = false;
        _arena.survivalRule(1) = true;
        _arena.survivalRule(2) = true;
        _arena.survivalRule(3) = true;
        _arena.survivalRule(4) = false;
        _arena.survivalRule(5) = false;
        _arena.survivalRule(6) = false;
        _arena.survivalRule(7) = false;
        _arena.survivalRule(8) = false;

        _arena.birthRule(0) = false;
        _arena.birthRule(1) = false;
        _arena.birthRule(2) = true;
        _arena.birthRule(3) = false;
        _arena.birthRule(4) = false;
        _arena.birthRule(5) = false;
        _arena.birthRule(6) = false;
        _arena.birthRule(7) = false;
        _arena.birthRule(8) = false;
        break;

    default:
        if (value>=CELL_EXAMPLE && value<=CELL_EXAMPLE+500)
        {
            _arena.clear();
            _arena.read((void *) lifeExamples[value-CELL_EXAMPLE]);
            _infoPage = 3;
            break;
        }
        else
        {
            GlutWindowExaminer::OnMenu(value);
            return;
        }
    }

    postRedisplay();
}

void
GltLifeWindow::setGrid(unsigned short width,unsigned short height)
{
    _arena.init(width,height);

    _ortho.left()   = 0;
    _ortho.right()  = width;

    _ortho.top()    = 0;
    _ortho.bottom() = height;

    _ortho.set();

    postRedisplay();
}

void
GltLifeWindow::setRun(const bool run)
{
    _run = run;
    setTick(_run ? 10 : 0);
}

void
GltLifeWindow::OnVisibility(int visible)
{
    setTick(visible==GLUT_VISIBLE ? 10 : 0);
}

void
GltLifeWindow::setDemo(const bool demo)
{
    _demoMode = demo;

    if (_demoMode)
    {
        OnMenu(CELL_MODE_BLEND);
        OnMenu(CELL_FULLSCREEN);
        OnMenu(CELL_EXAMPLE+1);
        setRun(true);
    }
    else
    {
        OnMenu(CELL_MODE_PIXELS);
        OnMenu(CELL_WINDOW);
        OnMenu(CELL_EXAMPLE+1);
        setRun(false);
    }
}

void
GltLifeWindow::setFullscreen(const bool fullscreen)
{
    _fullscreen = fullscreen;
    if (_fullscreen)
        enterGameMode();
    else
        leaveGameMode();
}

void
GltLifeWindow::clear(GLenum buffer)
{
    _graphics.background().glClearColor();
    if (buffer!=GL_NONE)
        glDrawBuffer(buffer);
    glClear(GL_COLOR_BUFFER_BIT);
}

const string GltLifeWindow::_messageText =

    "gltLife 0.5                               \n" \
    "(C) 2001-2002 Nigel Stewart                \n" \
    "http://www.nigels.com/glt/gltlife/        \n" \
    "\n" \
    "Based on CAEL 1.5 by Abraham Egnor        \n" \
    "http://www.ugcs.caltech.edu/~abe/cael.html\n" \
    "\n" \
    "Example lifeforms collection by Alan Hensel\n" \
    "http://hensel.lifepatterns.net/\n" \
    "\n" \
    "F1 for help, left mouse button for menu.";

const string GltLifeWindow::_helpText =

    "Mouse:                          \n" \
    "  Left Button      Menu         \n" \
    "  Middle Button    Zooming      \n" \
    "  Right Button     Panning      \n" \
    "\n" \
    "Keyboard:                       \n" \
    "  space            Toggle Update\n" \
    "  .                Step         \n" \
    "  /                Clear Arena  \n" \
    "  1-3              Draw Mode    \n" \
    "  F1               Info         \n" \
    "  q                Quit";


void
GltLifeWindow::makePage()
{
    switch (_infoPage)
    {
    case 0: _info.text() = "";           break;
    case 1: _info.text() = _messageText; break;
    case 2: _info.text() = _helpText;    break;

    case 3:
        {
            char grid[20];
            char generation[20];
            char population[20];

            sprintf(grid,      "%ux%u\n",(unsigned int) _arena.width(),(unsigned int) _arena.height());
            sprintf(generation,"%lu\n",_arena.generation());
            sprintf(population,"%lu\n",_arena.population());

            string info;
            info =  "Status:     ";
            info += (_run ? "Running\n" : "Stopped\n");
            info += "Rules:      ";
            info += _arena.rules();
            info += '\n';

            info +=  "Mutation:   ";
            info += (_mutate ? "On\n" : "Off\n");
            info += "Grid:       ";
            info += grid;
            info += "Generation: ";
            info += generation;
            info += "Population: ";
            info += population;

            info += "\n";
            info += _arena.description();

            _info.text() = info;
        }
        break;
    }
}

Vector
GltLifeWindow::getReferencePoint(int x,int y,const Vector &pos,const Matrix &modelView,const Matrix &modelViewInverse) const
{
    Plane plane(Vector0,VectorZ);
    const Vector p0 = modelViewInverse*pos;
    const Vector p1 = modelViewInverse*Vector(pos.x(),pos.y(),0.0);
    return plane.intersectPosition(p0,p1);
}

