#ifndef MESH_YYPARSE_H
#define MESH_YYPARSE_H

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
    \brief   VRML Parser
    \ingroup Mesh

    $Id: vrmlpars.h,v 1.2 2004/02/08 14:13:21 jgasseli Exp $

    $Log: vrmlpars.h,v $
    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.9  2003/05/31 11:38:11  nigels
    *** empty log message ***

    Revision 1.8  2003/03/06 12:31:15  nigels
    *** empty log message ***

*/

#include <iostream>
#include <cstdio>
using namespace std;

#include <mesh/vrml.h>

class Mesh;

extern Mesh   *yyVrmlMesh;
extern FILE   *Vrmlin;

int Vrmlparse(void);

extern void (*VrmlParseMaterial)      (MaterialPtr       &material);
extern void (*VrmlParseIndexedFaceSet)(IndexedFaceSetPtr &faceSet);
extern void (*VrmlParseShape)         (GltShapePtr       &shape);

#endif

