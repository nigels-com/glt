#ifndef NODE_HISTOGRM_H
#define NODE_HISTOGRM_H

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
    \brief   Histogram Node
    \ingroup Node
*/

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <node/shape.h>
#include <node/field.h>

#include <vector>

///////////////////////////// GltHistogram ///////////////////////////////////////

/*! \class   GltHistogram
    \brief   Histogram Node
    \ingroup Node
*/

class GltHistogram : public GltShape
{
public:

             GltHistogram();        ///< Constructor
    virtual ~GltHistogram();        ///< Destructor

    virtual void draw() const;

    void reset();                   ///< Reset histogram to all zeros
    void add(const double x);       ///< Add sample
    void add(const int    n);       ///< Add sample

    double &min();                  ///< Minimum of sample domain
    double &max();                  ///< Maximum of sample domain
    int    &size();                 ///< Number of buckets
    bool   &cumulative();           ///< Cumulative mode

    bool   &drawLine();             ///< Draw as lines or bars

    unsigned int samples()  const;  ///< Number of samples
    unsigned int outlyers() const;  ///< Number of outlyer samples
    unsigned int minCount() const;  ///< Minimum bucket count
    unsigned int maxCount() const;  ///< Maximum bucket count

    GltFieldPtr settings();         ///< Field settings

private:

    double  _min;
    double  _max;
    int     _size;
    bool    _cumulative;

    bool    _drawLine;

    unsigned int    _samples;
    unsigned int    _outlyers;

    std::vector<unsigned int> _count;
};

#endif
