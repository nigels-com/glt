#ifndef VRMLVIEW_H
#define VRMLVIEW_H

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

// TODO
//        ZLib compression
//    Pov-ray export
//    VRML coloring support
//    OpenVRML support

#include <glutm/glut.h>
#include <glutm/master.h>
#include <glutm/winexam.h>
#include <glutm/raypp.h>

#include <glt/light.h>
#include <glt/material.h>
#include <glt/lightm.h>
#include <glt/rgb.h>

//#include <mesh/mesh.h>
#include <node/dlist.h>
#include <node/shapes.h>

#ifdef OPENVRML
class VrmlScene;
class ViewerOpenGL;
#endif

#ifdef GLUTM_RAYPP
extern void initSceneMesh(const Mesh &mesh);
#endif

class GlutVrmlViewer : public GlutWindowExaminer
{
public:
    GlutVrmlViewer
    (
        const std::string &filename,
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault,
        unsigned int displayMode = displayModeDefault
    );

   ~GlutVrmlViewer();

   void OnOpen();
   void OnClose();

   void OnDisplay();
   void OnKeyboard(unsigned char key, int x, int y);

protected:

    #ifdef OPENVRML
    VrmlScene    *_scene;
    ViewerOpenGL *_viewer;
    void loadScene(const std::string &filename);
    void drawScene();
    #else
//  Mesh _mesh;
    GltShapes _shapes;
    #endif

    GltLight        _light0;
    GltLight        _light1;
    GltMaterial     _material;
    GltLightModel   _lightModel;
    GltDisplayList  _list;
};

#endif
