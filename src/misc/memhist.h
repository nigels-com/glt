#ifndef MISC_MEMHIST_H
#define MISC_MEMHIST_H

#error OBSOLETE

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2002 Nigel Stewart

  Email: nigels@nigels.com
  WWW:   http://www.nigels.com/glt/

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

#ifndef DOXYGEN

/*! \file
    \brief   Classes for memory use analysis
    \ingroup Misc

    These classes are for analysing run-time heap memory
    utilisation, and are still quite experimental.  At
    this stage, they are totally unsupported - use at your
    own risk.  Ultimately, I'd like to visualise memory
    use, in real-time, using OpenGL or perhaps direct
    image output to disk.

*/

#ifdef WIN32
#pragma warning(disable : 4786)     // Lengthy STL symbols
#endif

#include <cstdlib>
#include <list>
#include <map>
#include <iosfwd>

/*! \class   MemoryEvent
    \brief   Memory allocation event
    \ingroup Misc
    \warning Unsupported, Experimental & Subject to change!
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
*/

class MemoryEvent
{
    friend class MemoryModel;       // Memory model needs to see private members

public:
    MemoryEvent(void *ptr,size_t size);             // new
    MemoryEvent(void *ptr);                         // delete

private:
    void   *_ptr;
    size_t  _size;
    bool    _new;
};

/*! \class   MemoryEventHistory
    \brief   Sequenced list of memory allocation events
    \ingroup Misc
    \warning Unsupported, Experimental & Subject to change!
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
*/

class MemoryEventHistory : public std::list<MemoryEvent>
{
public:
    MemoryEventHistory();
    MemoryEventHistory(std::istream &is);

    void summary(std::ostream &os) const;
};

/*! \class   MemoryModel
    \brief   Virtual machine for memory allocation analysis
    \ingroup Misc
    \warning Unsupported, Experimental & Subject to change!
    \author  Nigel Stewart, RMIT (nigels@nigels.com)
*/

class MemoryModel
{
public:
    MemoryModel();

    void apply(const MemoryEvent &event);

    size_t minAddress() const;
    size_t maxAddress() const;
    size_t addressSpace() const;
    size_t blocks() const;
    size_t memoryUsed() const;
    size_t maxBlocks() const;
    size_t maxMemory() const;

    size_t numAllocations() const;
    size_t numFree() const;
    size_t numFreeNull() const;
    size_t numFreeInvalid() const;

private:
    std::map<size_t, size_t, std::less<size_t> >            _allocated;
    size_t                                                  _minAddress,_maxAddress;
    size_t                                                  _memoryUsed;
    size_t                                                  _maxBlocks;
    size_t                                                  _maxMemory;

    size_t                                                  _numAllocations;
    size_t                                                  _numFree;
    size_t                                                  _numFreeNull;
    size_t                                                  _numFreeInvalid;
};

#endif
#endif
