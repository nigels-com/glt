#include "fontpoly.h"

#if 0

/*! \file
    \ingroup GLT

	Based on Polyfont Copyright (C) 2003 Bob Pendleton

	Polyfonts is a polygon font drawing library for use with SDL. Any
	TTF font can be converted for use with this library. Contact the
	author for details.

    $Id: fontpoly.cpp,v 2.1 2004/02/12 13:48:56 nigels Exp $

    $Log: fontpoly.cpp,v $
    Revision 2.1  2004/02/12 13:48:56  nigels
    no message

    Revision 1.1  2003/12/11 23:46:48  nigels
    Added PolyFont library


*/

#include <math/real.h>

#include <algorithm>
#include <cstdio>
#include <cassert>
using namespace std;

#define unfix(value) ((float)(value)) / ((float)pfFixScale)

typedef struct
{
  float x, y;
} vertex;

vertex weightOffset[] = {
  {0.0, 0.0},
  {0.0, 1.0},
  {1.0, 1.0},
  {1.0, 0.0},
  /*-------*/
  {0.0, 2.0},
  {1.0, 2.0},
  {2.0, 2.0},
  {1.0, 2.0},
  {0.0, 2.0},
};

GltFontPolygon::GltFontPolygon(void *data)
: _font(NULL),
  _center(false),
  _weight(1),
  _skew(0.0)
{
    if (data)
        init(data);

	_hStep = 40;
	_vStep = 40;
}

GltFontPolygon::~GltFontPolygon()
{
    init(NULL);
}

void
GltFontPolygon::init(void *data)
{
    clear();

    if (data)
    {
		_font = static_cast<pffont *>(data);
    }
}

void
GltFontPolygon::clear()
{
}

bool 
GltFontPolygon::print(const GltChar ch) const
{
	const pfglyph *g = getGlyph(ch);
	if (!g)
		return false;

	for (int k=0; k<_weight; k++)
	{
		int      segs = g->numsegments;
		pfint16 *d    = g->segments;

		for (int i=0; i<segs; i++)
		{
			int prim   = *d++;
			int points = *d++;

			glBegin(prim);
			for (int j=0; j<points; j++)
			{
				float gx = unfix(*d++);
				float gy = unfix(*d++);

				gx += weightOffset[k].x;
				gy += weightOffset[k].y;

				gx = skew(gx, gy);

				glVertex2f(gx*_hStep, 0.75*_vStep - gy*_vStep);
			}
			glEnd();
		}
	}

	glTranslatef(g->advance*_hStep,0.0f,0.0f);

	return true;
}

bool
GltFontPolygon::print(const GltString &str) const
{
    if (_font)
    {
		// Push modelview matrix so that we can skip
		// back to the start of the line before moving
		// downwards for the next string.

		glPushMatrix();
        glPushAttrib(GL_LIST_BIT|GL_CURRENT_BIT);
            for (uint32 i=0; i<str.length(); i++)
                print(str[i]);
        glPopAttrib();
		glPopMatrix();

		// Adjust modelview matrix for outputting to the
		// next line.

		glTranslatef(0.0f,_vStep,0.0f);

        return true;
    }
    else
        return false;
}

int
GltFontPolygon::width(const GltChar ch) const
{
	const pfglyph *g = getGlyph(ch);
	if (!g)
		return 0;

	return ceil(g->advance*_hStep);
}

int 
GltFontPolygon::comp(const void *key, const void *target)
{
  pfglyph *k = (pfglyph *)key;
  pfglyph *t = (pfglyph *)target;

  return (k->glyph) - (t->glyph);
}

const pfglyph *
GltFontPolygon::getGlyph(const wchar_t c) const
{
	if (!_font)
		return NULL;

	pfglyph key;
	key.glyph = c;

	return (pfglyph *) bsearch(
		(void *) (&key),
		(void *) (_font->glyphs),
		_font->numglyphs,
		sizeof(pfglyph),
		comp);
}

float 
GltFontPolygon::skew(float x, float y) const
{
  return x + (_skew * y);
}

#endif
