#ifndef MISC_TIMER_H
#define MISC_TIMER_H

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

/*!
    \file
    \brief   Elapsed Time Object
    \ingroup Misc
*/

#include <glt/config.h>

#include <ctime>
#include <iosfwd>

#ifdef GLT_UNIX
#include <sys/time.h>
#endif

/*!
    \class   Timer
    \brief   Elapsed Time Object
    \ingroup Misc
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
    \note    The precision of this object is limited to the ANSI C macro CLOCKS_PER_SEC

    The timer object can be used for measuring elapsed time
    between events.  The timer starts from the time the object
    is created, and is reset to zero when Timer::start() is
    called.

    When an output stream is passed to the constructor, the
    elapsed time will be output when the timer is destroyed.

*/

class Timer
{
public:
    /*
        Interface for individual timers.
    */


    Timer();                                    ///< Constructor
    Timer(std::ostream &);                      ///< Constructor: Report elapsed time to output stream
    ~Timer();                                   ///< Destructor

    void start();                               ///< Reset the timer

    double  elapsed() const;                    ///< Get the elapsed time (sec)
    clock_t clock()   const;                    ///< Get the elapsed number of clock ticks

    static clock_t clockPerSec();               ///< Get the number of clock ticks per second

    /*
        Interface for controlling
        time globally.
    */

    static void freeze();                       ///< Freeze all timers
    static void unFreeze();                     ///< Un-freeze all timers
    static void advance(const uint32 msec);     ///< Advance all (frozen) timers

private:

    #ifdef GLT_WIN32
           clock_t _start;
           clock_t _end;
    static clock_t _frozen;
    #endif

    #ifdef GLT_UNIX
           timeval _start;
           timeval _end;
    static timeval _frozen;
    #endif

    static uint32 _frozenCount;

    std::ostream *_os;
};

#endif
