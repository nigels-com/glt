#ifndef SIERPINK_H
#define SIERPINK_H

/*

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2001 Nigel Stewart
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

class GltShapes;
class GltColor;
class Vector3;

void sierpinskiSponge(GltShapes &shapes, const int n, const Vector3 &min, const Vector3 &max, const GltColor &color);
void sierpinskiCross (GltShapes &shapes, const int n, const Vector3 &min, const Vector3 &max, const GltColor &color);
void sierpinskiFlake (GltShapes &shapes, const int n, const Vector3 &min, const Vector3 &max, const GltColor &color);

#endif
