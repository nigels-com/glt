#include "world.h"

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

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
using namespace std;

#include <misc/compress.h>

#include "rowiter.h"

unsigned short &GltLifeWorld::lifeTime()     { return _lifeTime; }

unsigned short  GltLifeWorld::width()  const { return _width; }
unsigned short  GltLifeWorld::height() const { return _height; }

unsigned long GltLifeWorld::generation() const { return _generation; }
unsigned long GltLifeWorld::population() const { return _population; }

bool &GltLifeWorld::survivalRule(const int n) { assert(n>=0 && n<=8); return _survival[n]; }
bool &GltLifeWorld::birthRule(const int n)    { assert(n>=0 && n<=8); return _birth[n]; }

const bool &GltLifeWorld::survivalRule(const int n) const { assert(n>=0 && n<=8); return _survival[n]; }
const bool &GltLifeWorld::birthRule(const int n)    const { assert(n>=0 && n<=8); return _birth[n]; }

const string &GltLifeWorld::description() const { return _description; }

GltLifeWorld::GltLifeWorld()
: _width(0), _height(0), _size(0), _generation(0), _population(0)
{
    _lifeTime = 0;

    //
    // Setup default rules for Conway Game Of Life
    //

    _survival[0] = false;
    _survival[1] = false;
    _survival[2] = true;
    _survival[3] = true;
    _survival[4] = false;
    _survival[5] = false;
    _survival[6] = false;
    _survival[7] = false;
    _survival[8] = false;

    _birth[0] = false;
    _birth[1] = false;
    _birth[2] = false;
    _birth[3] = true;
    _birth[4] = false;
    _birth[5] = false;
    _birth[6] = false;
    _birth[7] = false;
    _birth[8] = false;

}

GltLifeWorld::~GltLifeWorld()
{
}

void
GltLifeWorld::init(const unsigned short width,const unsigned short height)
{
    _width  = (width <3 ? 3 : width);
    _height = (height<3 ? 3 : height);
    _size   = _width*_height;

    cbuffer< std::vector<unsigned short> > cell(2);
    cell.push_back(vector<unsigned short>(_size,0));
    cell.push_back(vector<unsigned short>(_size,0));

    _cell.swap(cell);
}

void
GltLifeWorld::clear()
{
    assert(_cell.front().size()>=_size);
    memset(&_cell.front()[0],0,sizeof(unsigned short)*_cell.front().size());

    _generation = 0;
    _population = 0;
}

void
GltLifeWorld::update()
{
    if (_width==0 || _height==0 || _cell.size()<2)
        return;

    assert(_cell.front().size()>=_size);
    const unsigned short *get = &_cell.front()[0];

    _cell.leftShift();
    assert(_cell.front().size()>=_size);
          unsigned short *put = &_cell.front()[0];

    memset(put,0,sizeof(unsigned short)*_size);

    const unsigned short *begin = get;
    const unsigned short *end   = get+_size;

    RowIterator a(end-_width,end         );
    RowIterator b(get       ,get+_width  );
    RowIterator c(get+_width,get+_width*2);

    for (int y=0; y<_height; y++)
    {
        for (int x=0; x<_width; x++)
        {
            const int count =
                RowIterator::rowCount[a.mask()&7] +
                RowIterator::rowCount[b.mask()&5] +
                RowIterator::rowCount[c.mask()&7];

            if (b.mask()&2)
            {
                // Cell is alive in current generation

                if (_survival[count] && (_lifeTime==0 || *get<_lifeTime))
                    *put = *get + 1;
                else
                    _population--;
            }
            else
            {
                // Cell is dead in current generation

                if (_birth[count])
                {
                    *put = 1;
                    _population++;
                }
            }

            ++a;
            ++b;
            ++c;
            get++;
            put++;
        }

        a = b;
        b = c;

        if ((y+1)<(_height-1))
            c = RowIterator(get+_width,get+_width*2);
        else
            if ((y+1)==(_height-1))
                c = RowIterator(begin,begin+_width);
    }

    _generation++;
}

void
GltLifeWorld::mutate()
{
    for (int y=0; y<_height; y++)
        for (int x=0; x<_width; x++)
            if (rand()<(RAND_MAX>>7) && cell(x,y)==0)
            {
                cell(x,y) = 1;
                _population++;
            }
}

void
GltLifeWorld::setCell(int x,int y,const bool alive)
{
    while (x<0)
        x += _width;

    while (y<0)
        y += _height;

    x %= _width;
    y %= _height;

    if (cell(x,y)==0 && alive)
        _population++;

    if (cell(x,y)!=0 && !alive)
        _population--;

    cell(x,y) = alive;
}

bool
GltLifeWorld::getCell(int x,int y)
{
    while (x<0)
        x += _width;

    while (y<0)
        y += _height;

    x %= _width;
    y %= _height;

    return cell(x,y)!=0;
}

unsigned short *
GltLifeWorld::getCells() const
{
    return (unsigned short *) &_cell.front()[0];
}


string
GltLifeWorld::rules() const
{
    string tmp;

    int i;
    for (i=0;i<9; i++)
        if (survivalRule(i))
            tmp += '0'+i;

    tmp += '/';

    for (i=0;i<9; i++)
        if (birthRule(i))
            tmp += '0'+i;

    return tmp;
}

void
GltLifeWorld::read(const char *buffer)
{
    istringstream is(buffer);
    read(is);
}

void
GltLifeWorld::read(const void *buffer)
{
    string tmp;
    bool ok = decompress(tmp,buffer);
    assert(ok);

    if (ok)
    {
        tmp += '\0';
        read(tmp.c_str());
    }
}


void
GltLifeWorld::read(istream &is)
{
    const int bufferSize = 1024;
    char buffer[bufferSize];

    // Get the head line

    is.getline(buffer,bufferSize);
    if (strncmp(buffer,"#Life ",6))
        return;

    // Get the description (optional)

    string desc;
    for(;;)
    {
        is.getline(buffer,bufferSize);
        if (!strncmp(buffer,"#D",2) || !strncmp(buffer,"#C",2))
        {
            // Skip any whitespace before the description

            char *pos = buffer+2;
            while (*pos==' ' || *pos=='\t')
                pos++;

            desc += pos;
            desc += "\n";
            continue;
        }
        break;
    }

    _description = desc;

    // Get the rules (optional)

    if (!strcmp(buffer,"#N"))
    {
        _survival[0] = false;
        _survival[1] = false;
        _survival[2] = true;
        _survival[3] = true;
        _survival[4] = false;
        _survival[5] = false;
        _survival[6] = false;
        _survival[7] = false;
        _survival[8] = false;

        _birth[0] = false;
        _birth[1] = false;
        _birth[2] = false;
        _birth[3] = true;
        _birth[4] = false;
        _birth[5] = false;
        _birth[6] = false;
        _birth[7] = false;
        _birth[8] = false;

        is.getline(buffer,bufferSize);
    }
    else
        if (!strncmp(buffer,"#R ",3))
        {
            // Reset all the rules

            for (int i=0; i<9; i++)
                _survival[i] = _birth[i] = false;

            // Read survival rules

            char *pos = buffer+3;
            for (;*pos!='\0' && *pos!='/';pos++)
                if (*pos>='0' && *pos<='8')
                    _survival[*pos-'0'] = true;

            // Read birth rules

            if (*pos=='/')
                for (;*pos!='\0';pos++)
                if (*pos>='0' && *pos<='8')
                    _birth[*pos-'0'] = true;

            is.getline(buffer,bufferSize);
        }

    // Get the cells

    while (!strncmp(buffer,"#P ",3))
    {
        // Position

        int px,py;
        sscanf(buffer+3,"%d %d",&px,&py);

        px += _width>>1;
        py += _height>>1;

        int y = py;

        is.getline(buffer,bufferSize);
        while (*buffer!='#')
        {
            for (uint32 x=0; x<strlen(buffer); x++)
                setCell(x+px,y,buffer[x]=='*');

            if (is.eof())
                break;

            y++;
            is.getline(buffer,bufferSize);
        }
    }

    // Cells can also be in x y tuples, one per line.
    // This is noticed in oscsp4.lif in the collection

    while (!is.eof())
    {
        int px = 0;
        int py = 0;
        if (sscanf(buffer,"%d %d",&px,&py)==2)
        {
            px += _width>>1;
            py += _height>>1;
                setCell(px,py,true);
        }
        is.getline(buffer,bufferSize);
    }
}

