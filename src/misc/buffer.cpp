#include "buffer.h"

#include <cassert>
#include <cstring>
#include <cstdlib>
using namespace std;

buffer_iterator::buffer_iterator()
: _begin(NULL),
  _end(NULL),
  _pos(NULL)
{
}

buffer_iterator::buffer_iterator(void *begin, void *end)
: _begin(reinterpret_cast<byte *>(begin)),
  _end(reinterpret_cast<byte *>(end)),
  _pos(reinterpret_cast<byte *>(begin))
{
}

buffer_iterator::buffer_iterator(void *begin, const uint32 size)
: _begin(reinterpret_cast<byte *>(begin)),
  _end(reinterpret_cast<byte *>(begin)+size),
  _pos(reinterpret_cast<byte *>(begin))
{
}

buffer_iterator::~buffer_iterator()
{
    _begin = _end = NULL;
}

const bool   buffer_iterator::empty() const { return _begin==_end;              }
const uint32 buffer_iterator::size()  const { return _end-_begin;               }

const bool   buffer_iterator::valid()                 const { return valid(_pos);             }
const bool   buffer_iterator::valid(const byte  *pos) const { return pos>=_begin && pos<_end; }
const bool   buffer_iterator::valid(const uint32 pos) const { return valid(_pos+pos);         }

      byte &buffer_iterator::operator *()       { assert(valid()); return *_pos; }
const byte &buffer_iterator::operator *() const { assert(valid()); return *_pos; }

      byte *buffer_iterator::pos()       { return _pos;   }
      byte *buffer_iterator::begin()     { return _begin; }
      byte *buffer_iterator::end()       { return _end;   }

const byte *buffer_iterator::pos()   const { return _pos;   }
const byte *buffer_iterator::begin() const { return _begin; }
const byte *buffer_iterator::end()   const { return _end;   }

byte &
buffer_iterator::operator[](const uint32 i)
{
    assert(valid(i));
    return _pos[i];
}
const byte &
buffer_iterator::operator[](const uint32 i) const
{
    assert(valid(i));
    return _pos[i];
}

void
buffer_iterator::clear(const byte val)
{
    memset(_begin,_end-_begin,val);
}

///////////////////////////////////////////////////////////////////////////

const_buffer_iterator::const_buffer_iterator()
: _begin(NULL),
  _end(NULL),
  _pos(NULL)
{
}

const_buffer_iterator::const_buffer_iterator(const void *begin, const void *end)
: _begin(reinterpret_cast<const byte *>(begin)),
  _end(reinterpret_cast<const byte *>(end)),
  _pos(reinterpret_cast<const byte *>(begin))
{
}

const_buffer_iterator::const_buffer_iterator(const void *begin, const uint32 size)
: _begin(reinterpret_cast<const byte *>(begin)),
  _end(reinterpret_cast<const byte *>(begin)+size),
  _pos(reinterpret_cast<const byte *>(begin))
{
}

const_buffer_iterator::~const_buffer_iterator()
{
    _begin = _end = _pos = NULL;
}

const bool   const_buffer_iterator::empty() const { return _begin==_end;              }
const uint32 const_buffer_iterator::size()  const { return _end-_begin;               }

const bool  const_buffer_iterator::valid()                 const { return valid(_pos);             }
const bool  const_buffer_iterator::valid(const byte  *pos) const { return pos>=_begin && pos<_end; }
const bool  const_buffer_iterator::valid(const uint32 pos) const { return valid(_pos+pos);         }

const byte &const_buffer_iterator::operator *() const { assert(valid()); return *_pos; }

const byte *const_buffer_iterator::pos()   const { return _pos;   }
const byte *const_buffer_iterator::begin() const { return _begin; }
const byte *const_buffer_iterator::end()   const { return _end;   }

const byte &
const_buffer_iterator::operator[](const uint32 i) const
{
    assert(valid(i));
    return _pos[i];
}
