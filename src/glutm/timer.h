#ifndef GLUTM_TIMER_H
#define GLUTM_TIMER_H

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
    \brief   GLUT Timer Receiver Class
    \ingroup GlutMaster
*/

#include <glutm/config.h>
#include <glutm/glut.h>

#include <vector>
#include <list>

/////////////////////////// GlutTimer ////////////////////////////////////

/*! \class   GlutTimer
    \brief   Base class for GLUT objects that receive real-time events
    \ingroup GlutMaster
    \author  Nigel Stewart (nigels@nigels.com)

    The GlutTimer interface should be inherited by all
    classes that require idle, timer and tick events
    from the GLUT main loop.  Primarily for GlutWindow
    objects, but also available to other C++ objects.

*/

class GlutTimer
{
    friend class GlutMaster;

public:

    GlutTimer();                ///< Constructor
    virtual ~GlutTimer();       ///< Destructor

    // Callback handlers

    /*!
        \brief      Handler for idle events, if enabled
        \note       Use of idle tends to be a CPU hog
    */
    virtual void OnIdle();
    /*!
        \brief      Handler for tick events, if enabled
        \note       This is gentler on CPU load than the idle callback
    */
    virtual void OnTick();
    /*!
        \brief      Handler for timer events
        \note       Queue timer events via GlutWindow::setTimer()
    */
    virtual void OnTimer(int val);

    // Get/Set


            bool getIdle() const;   ///< Is the object receiving idle events?
    unsigned int getTick() const;   ///< Get the object tick interval

    /*!
        \brief      Object will receive OnIdle() events, continuously
        \warning    This tends to hog the CPU
        \note       Object will receive OnIdle() events
    */
    void setIdle(bool idle);

    /*!
        \brief      Configure draw events to occur at a given frequency
        \param      msec  Time between tick events in milli seconds, zero to disable
        \note       Object will receive OnTick() events
    */
    void setTick(unsigned int msec);

    /*!
        \brief      Configure a timer event to occur after an elapsed time period
        \param      msec  Time until timer event
        \param      val   Integer value to be received by OnTimer()
        \note       Object will receive OnTimer() event
    */
    void setTimer(unsigned int msec,int val = 0);

protected:

    // Protected callback handlers

    virtual void OnPreIdle();           ///< Handler for pre-idle event
    virtual void OnPreTimer();          ///< Handler for pre-timer event

private:


    bool         _idle;         ///< Idle flag, must be manipulated via getIdle/setIdle
    unsigned int _tick;         ///< Delay between update "ticks"
    bool         _tickPending;  ///< Currently waiting for tick

    //

    class Slot
    {
    public:
        Slot();
        ~Slot();

        static int   add(GlutTimer *target,int val,bool tick = false);
        static Slot *get(const uint32 index);
        static void  remove(GlutTimer *target);

        bool       _inUse;
        GlutTimer *_target;
        int        _val;
        bool       _tick;

    private:
        static uint32                   _slot;
        static std::vector<Slot>        _slots;
    };

    static std::list<GlutTimer *> _idleList;

    static void idleCallback();
    static void timerCallback(int val);
};

#endif
