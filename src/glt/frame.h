#ifndef GLT_FRAME_H
#define GLT_FRAME_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2004 Nigel Stewart


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
    \brief OpenGL Frame Rate Information
    \ingroup GLT

    $Id: frame.h,v 2.1 2004/08/11 05:20:18 nigels Exp $

    $Log: frame.h,v $
    Revision 2.1  2004/08/11 05:20:18  nigels
    Updated copyright and removed email address from headers

    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.13  2003/03/06 12:18:59  nigels
    *** empty log message ***

    Revision 1.12  2002/11/27 00:57:28  nigels
    expand

    Revision 1.11  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.10  2002/10/07 16:27:46  nigels
    Added CVS version control info


*/

#include <iosfwd>
#include <vector>
#include <string>

#include <misc/timer.h>
#include <misc/cbuffer.h>

/*! \class GltFrameRate
    \brief OpenGL Frame Rate Information Class
    \ingroup GLT
*/

class GltFrameRate
{
public:
    /// Constructor
    GltFrameRate(const int sampleSize = 11);
    /// Destructor
    ~GltFrameRate();

    /// Call this once for each redraw
    GltFrameRate &operator++();

    /// Get the total elapsed time since construction
    double elapsedTime() const;
    /// Get the total number of frames
    int   totalFrames() const;

    /// Get the (averaged) frame rate
    double frameRate() const;
    /// Get the (averaged) time per frame
    double frameTime() const;

    /// Summary frame rate information
    std::string summary() const;

    /// Detailed fram rate information
    std::string detailed() const;

private:

    Timer           _timer;             // Timer used for frame rate calculation
    int             _frames;            // Total number of frames
    double          _step;              // Minimum time step between recalculation

    double          _lastCalc;          // Time of last recalculation
    double          _lastFrameRate;     // Previously calculated frame rate (frame/sec)
    double          _lastFrameTime;     // Previously calculated frame time (sec/frame)

    cbuffer<double> _buffer;            // Circular buffer storage
};

#endif
