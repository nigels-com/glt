#include "font.h"

/*! \file
    \ingroup GLT

    $Id: font.cpp,v 2.2 2006/07/01 13:40:18 nigels Exp $
*/

#include <math/real.h>

#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

GltFont::GltFont()
: _hStep(0), _vStep(0), _init(false)
{
}

GltFont::GltFont(const GltFont &)
{
    // Can't copy fonts
    assert(0);
}

GltFont &
GltFont::operator=(const GltFont &)
{
    // Can't copy fonts
    assert(0);
    return *this;
}

GltFont::~GltFont()
{
    _init = false;
}

void
GltFont::size(int &w,int &h,const GltString &str) const
{
    h = 0;
    w = 0;

    // Get the first line of text

    string::size_type i = 0;
    string::size_type j = str.find('\n',i);

    // Process each line of text

    while (i<str.size())
    {
        h++;

        int lWidth = 0;
        for (string::size_type k=i; k<j && k<str.size(); k++)
            lWidth += width(str[k]);

        //

        w = std::max(w,lWidth);

        //

        if (j==GltString::npos)
            break;

        i = j+1;
        j = str.find('\n',i);
    }

    //

    h *= _vStep;
}

int
GltFont::width(const GltChar ch) const
{
    GLT_UNUSED(ch);
    return _hStep;
}

const int GltFont::hStep()  const { return _hStep; }
const int GltFont::vStep()  const { return _vStep; }
