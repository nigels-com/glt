#ifndef GLT_LIFE_WORLD
#define GLT_LIFE_WORLD

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

#include <iosfwd>
#include <cassert>
#include <string>
#include <vector>

#include <misc/cbuffer.h>

class GltLifeWorld
{

    friend class GltLifeDraw;

public:

    GltLifeWorld();
    ~GltLifeWorld();

    void init(const unsigned short width,const unsigned short height);

    void clear();
    void read(std::istream &is);    // Uncompressed text
    void read(const char *buffer);  // Uncompressed text
    void read(const void *buffer);  // Compressed

    void update();
    void mutate();

    unsigned short width() const;
    unsigned short height() const;

    unsigned long generation() const;
    unsigned long population() const;

    const bool &survivalRule(const int n) const;
    const bool &birthRule(const int n) const;

    std::string rules() const;

    const std::string &description() const;

    unsigned short &lifeTime();

    bool &survivalRule(const int n);
    bool &birthRule(const int n);

    void setCell(int x,int y,const bool alive);
    bool getCell(int x,int y);

    unsigned short *getCells() const;

protected:

    inline unsigned short &cell(/*const unsigned short p,*/ const unsigned short &x,const unsigned short &y)
    {
//      assert(p<2);
        assert(x<_width && y<_height);
//      assert(_cell[p]);
        return _cell.front().begin()[x+y*_width];
    }

    inline const unsigned short &cell(/*const unsigned short p,*/const unsigned short &x,const unsigned short &y) const
    {
//      assert(p<2);
        assert(x<_width && y<_height);
//      assert(_cell[p]);
        return _cell.front().begin()[x+y*_width];
    }

    unsigned short       _width;
    unsigned short       _height;
    unsigned short       _size;
//  unsigned short       _plane;

    cbuffer< std::vector<unsigned short> > _cell;

    unsigned long        _generation;
    unsigned long        _population;

    bool                 _survival[9];
    bool                 _birth[9];
    unsigned short       _lifeTime;         // Optional cell death, 0 for immortality

    std::string          _description;
};

#endif
