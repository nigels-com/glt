#include "timer.h"

/*! \file
    \ingroup GlutMaster
*/

#include <glutm/master.h>

#include <cassert>
using namespace std;

///////////////////////// GlutTimer ///////////////////////////////////////

GlutTimer::GlutTimer()
: _idle(false),
  _tick(0),
  _tickPending(false)
{
}

GlutTimer::~GlutTimer()
{
    Slot::remove(this);
    _idleList.remove(this);
}

void GlutTimer::OnIdle()         {}
void GlutTimer::OnTick()         {}
void GlutTimer::OnTimer(int val) {}
void GlutTimer::OnPreIdle()      {}
void GlutTimer::OnPreTimer()     {}

void GlutTimer::setIdle(bool idle)
{
    GlutMaster::setIdle(this,idle);
}

void GlutTimer::setTick(unsigned int msec)
{
    GlutMaster::setTick(this,msec);
}

void GlutTimer::setTimer(unsigned int msecs,int val)
{
    GlutMaster::setTimer(this,msecs,val);
}

bool         GlutTimer::getIdle() const { return _idle; }
unsigned int GlutTimer::getTick() const { return _tick; }

/////////////////////////////////////////////////////////////

uint32                         GlutTimer::Slot::_slot;
std::vector<GlutTimer::Slot>   GlutTimer::Slot::_slots;

list<GlutTimer *>              GlutTimer::_idleList;

void
GlutTimer::idleCallback()
{
    if (_idleList.size())
    {
        // All active windows with idle processing enabled
        // receive the OnIdle callback

        list<GlutTimer *>::iterator i=_idleList.begin();
        for (; i!=_idleList.end(); i++)
        {
            (*i)->OnPreIdle();  // Set GLUT window, OpenGL context, etc.
            (*i)->OnIdle();
        }
    }
}

void
GlutTimer::timerCallback(int val)
{
    Slot *slot = GlutTimer::Slot::get(val);

    assert(slot);
    if (slot)
    {
        if (slot->_target)
        {
            if (slot->_tick)
            {
                slot->_target->OnPreTimer();
                slot->_target->OnTick();
                slot->_target->_tickPending = false;

                if (slot->_target->_tick)
                {
                    GlutMaster::setTick(slot->_target,slot->_target->_tick);
                    slot->_target->_tickPending = true;
                }
            }
            else
            {
                slot->_target->OnPreTimer();
                slot->_target->OnTimer(slot->_val);
            }
        }
    }
}


/////////////////////////////////////////////////////////////

GlutTimer::Slot::Slot()
: _inUse(false),
  _target(NULL),
  _val(0),
  _tick(false)
{
}

GlutTimer::Slot::~Slot()
{
}

int GlutTimer::Slot::add(GlutTimer *target,int val,bool tick)
{
    if (!_slots.size())         // Allocate one slot if empty
    {
        _slots.resize(1);
        _slot = 0;
    }

    uint32 i = _slot;               // Start looking from current position

    while (_slots[i]._inUse)        // Search until empty slot found
    {
        i = (i+1)%_slots.size();    // Advance to next slot

        if (i==_slot)               // If all slots taken, allocate a new one
        {
            i = _slots.size();
            _slots.push_back(Slot());
            break;
        }
    }
                                        // Store information
    _slots[i]._inUse  = true;
    _slots[i]._target = target;
    _slots[i]._val    = val;
    _slots[i]._tick   = tick;

    _slot = (i+1)%_slots.size();

    return i;
}

GlutTimer::Slot *
GlutTimer::Slot::get(const uint32 index)
{
    if (index>=0 && index<_slots.size())    // Check that index is in range
    {
        _slots[index]._inUse = false;       // Mark slot as available
        _slot = index;                      // Recycle this slot ASAP
        return &(_slots[index]);            // Return target and val
    }
    else
        return NULL;
}

void GlutTimer::Slot::remove(GlutTimer *target)
{
    for (uint32 i=0; i<_slots.size(); i++)
        if (_slots[i]._target==target)
            _slots[i]._target = NULL;
}
