#include "timer.h"

/*! \file
    \brief   Elapsed Time Object
    \ingroup Misc

    $Id: timer.cpp,v 2.0 2004/02/08 19:44:13 nigels Exp $

    $Log: timer.cpp,v $
    Revision 2.0  2004/02/08 19:44:13  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:22  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.15  2003/03/06 12:34:47  nigels
    *** empty log message ***

*/

#include <iostream>
using namespace std;

#define THOUSAND 1000
#define MILLION  1000000

Timer::Timer()
: _os(NULL)
{
    start();
}

Timer::Timer(ostream &os)
: _os(&os)
{
    start();
}

Timer::~Timer()
{
    if (_os)
        (*_os) << elapsed() << " sec." << endl;
}

double
Timer::elapsed() const
{
    #ifdef GLT_WIN32
    return (double) (::clock()-_start)/CLOCKS_PER_SEC;
    #endif

    #ifdef GLT_UNIX
    return double(clock())/MILLION;
    #endif
}

clock_t
Timer::clock() const
{
    #ifdef GLT_WIN32
    if (_frozenCount)
        return _frozen-_start;
    else
        return ::clock()-_start;
    #endif

    #ifdef GLT_UNIX

    /* TODO: after one hour or so, we get overflow.
             Perhaps we should migrate to milli-seconds for UNIX
             That extends our timeout to 1000 hours (or 41 days)  */

    if (_frozenCount)
        return (_frozen.tv_sec-_start.tv_sec)*MILLION+(_frozen.tv_usec-_start.tv_usec);
    else
    {
        timeval tmp;
        gettimeofday(&tmp,NULL);
        return (tmp.tv_sec-_start.tv_sec)*MILLION+(tmp.tv_usec-_start.tv_usec);
    }
    #endif
}

void
Timer::start()
{
    #ifdef GLT_WIN32
        if (_frozenCount)
        _start = _end = _frozen;
    else
        _start = _end = ::clock();
    #endif

    #ifdef GLT_UNIX
    if (_frozenCount)
        _start = _end = _frozen;
    else
    {
        gettimeofday(&_start,NULL);
        _end = _start;
    }
    #endif
}

///

#ifdef GLT_WIN32
clock_t Timer::_frozen = 0;
#endif

#ifdef GLT_UNIX
timeval Timer::_frozen;
#endif

uint32  Timer::_frozenCount = 0;

void
Timer::freeze()
{
    #ifdef GLT_WIN32
    if (_frozenCount==0)
        _frozen = ::clock();
    #endif

    #ifdef GLT_UNIX
    if (_frozenCount==0)
        gettimeofday(&_frozen,NULL);
    #endif

    _frozenCount++;
}

void
Timer::unFreeze()
{
    _frozenCount--;
}

void
Timer::advance(const uint32 msec)
{
    #ifdef GLT_WIN32
    _frozen += (msec*CLOCKS_PER_SEC)/1000;
    #endif

    #ifdef GLT_UNIX
    _frozen.tv_sec  += (_frozen.tv_usec+(msec*THOUSAND))/MILLION;
    _frozen.tv_usec  = (_frozen.tv_usec+(msec*THOUSAND))%MILLION;
    #endif
}

