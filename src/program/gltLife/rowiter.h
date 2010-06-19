#ifndef GLT_LIFE_ROWITER
#define GLT_LIFE_ROWITER

/*

  GltLife
  C++ OpenGL Implementation of Conways Game of Life
  http://www.nigels.com/glt/gltlife/

  Based on CAEL 1.5 by Abraham Egnor
  http://www.ugcs.caltech.edu/~abe/cael.html

  Glt OpenGL C++ Toolkit (Glt)
  Copyright (C) 2000 Nigel Stewart
  Email: nigels.com@gmail.com   WWW: http://www.nigels.com/glt/

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

#include <cassert>
#include <glt/config.h>

class RowIterator
{
public:
    RowIterator(const unsigned short *begin,const unsigned short *end)
    : _begin(begin), _end(end), _pos(end-1), _mask(0)
    {
        assert(end-begin>=3);

        if (*_pos>0)       _mask |= 4;
        if (*_begin>0)     _mask |= 2;
        if (*(_begin+1)>0) _mask |= 1;

        _pos = _begin+1;
    }

    ~RowIterator()
    {
    }

    byte mask() { return _mask; }

    RowIterator &operator++()
    {
        _pos++;
        if (_pos>=_end)
            _pos = _begin;
        shiftCell();

        return *this;
    }

    RowIterator &operator=(const RowIterator &i)
    {
        _begin = i._begin;
        _end   = i._end;
        _pos   = i._pos;
        _mask  = i._mask;
        return *this;
    }

    static const int rowCount[8];

private:
    const unsigned short *_begin;
    const unsigned short *_end;
    const unsigned short *_pos;
    byte            _mask;

    inline void shiftCell() { _mask = (_mask<<1) | ((*_pos)>0 ? 1 : 0); };
};

#endif
