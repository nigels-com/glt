#include "frame.h"

/*! \file
    \ingroup GLT

    $Id: frame.cpp,v 2.1 2004/02/21 23:53:58 nigels Exp $

    $Log: frame.cpp,v $
    Revision 2.1  2004/02/21 23:53:58  nigels
    Decrease frequency of frame rate calculation to 2 fps

    Revision 2.0  2004/02/08 19:44:11  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:21  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.13  2003/09/08 05:18:37  nigels
    Use std::string sprintf

    Revision 1.12  2002/11/27 00:57:28  nigels
    expand

    Revision 1.11  2002/11/07 15:40:45  nigels
    *** empty log message ***

    Revision 1.10  2002/10/09 15:09:38  nigels
    Added RCS Id and Log tags


*/

#include <cstdio>
#include <string>
using namespace std;

#include <misc/string.h>

GltFrameRate::GltFrameRate(const int sampleSize)
: _frames(0),
  _step(0.500),
  _lastFrameRate(0.0),
  _lastFrameTime(0.0),
  _buffer(sampleSize)
{
    _lastCalc = _timer.elapsed();
}

GltFrameRate::~GltFrameRate()
{
}

GltFrameRate &
GltFrameRate::operator++()
{
    _frames++;
    _buffer.push_back(_timer.elapsed());

    // Recalculate frame rate and frame time
    // if we have sufficient samples and
    // enough time has elapsed.

    if (_buffer.size()>=2)
    {
        if ((_buffer.back()-_lastCalc)>=_step)
        {
            _lastCalc      = _buffer.back();
            _lastFrameTime = double(_buffer.back()-_buffer.front())/double(_buffer.size()-1);
            _lastFrameRate = 1.0/_lastFrameTime;
        }
    }

    return *this;
}

double GltFrameRate::elapsedTime() const { return _timer.elapsed(); }
int    GltFrameRate::totalFrames() const { return _frames;          }

double GltFrameRate::frameRate()   const { return _lastFrameRate; }
double GltFrameRate::frameTime()   const { return _lastFrameTime; }

string
GltFrameRate::summary() const
{
    string tmp;
    sprintf
    (
        tmp,
        "%3.0f fps",
        float(frameRate())
    );

    return tmp;
}

std::string
GltFrameRate::detailed() const
{
    string tmp;
    sprintf
    (
        tmp,
        "%5.3f sec %3.0f fps",
        float(frameTime()),
        float(frameRate())
    );
    return tmp;
}

