#include "textbuff.h"

#include <math/real.h>

#include <cassert>
using namespace std;

/////////////////// GltTextBuffer //////////////////////

GltTextBuffer::GltTextBuffer()
{
    clear();
}

GltTextBuffer::~GltTextBuffer()
{
}

void
GltTextBuffer::clear()
{
    list<string>::clear();
    push_back(string());
}

/////////////////// GltTextBufferIterator //////////////////////

GltTextBufferIterator::GltTextBufferIterator(GltTextBuffer &buffer)
: _buffer(buffer), _insert(true), _wrap(false), _wrapColumn(80)
{
    reset();
}

GltTextBufferIterator::~GltTextBufferIterator()
{
}

void
GltTextBufferIterator::reset()
{
    _line = _buffer.begin();
    _x = 0;
}

bool
GltTextBufferIterator::nextLine()
{
    GltTextBuffer::iterator tmp = _line;
    tmp++;

    if (tmp!=_buffer.end())
    {
        _line = tmp;
        _x = clamp(_x,0u,(unsigned int)(_line->size()));
        return true;
    }

    return false;
}

bool
GltTextBufferIterator::prevLine()
{
    if (_line!=_buffer.begin())
    {
        _line--;
        _x = clamp(_x,0u,(unsigned int)(_line->size()));
        return true;
    }

    return false;
}

bool
GltTextBufferIterator::nextChar()
{
    // Move right on the current line

    if (_x<_line->length())
    {
        _x++;
        return true;
    }

    // Move to the start of next line

    if (nextLine())
        _x = 0;

    return false;
}

bool
GltTextBufferIterator::prevChar()
{
    // Move left on the current line

    if (_x>0)
    {
        _x--;
        return true;
    }

    // Move to the end of previous line

    if (prevLine())
        _x = _line->length();

    return false;
}

bool GltTextBufferIterator::goUp()    { return prevLine(); }
bool GltTextBufferIterator::goDown()  { return nextLine(); }
bool GltTextBufferIterator::goLeft()  { return prevChar(); }
bool GltTextBufferIterator::goRight() { return nextChar(); }

const bool &GltTextBufferIterator::modeInsert() const { return _insert; }
      bool &GltTextBufferIterator::modeInsert()       { return _insert; }

const bool &GltTextBufferIterator::modeWrap() const { return _wrap; }
      bool &GltTextBufferIterator::modeWrap()       { return _wrap; }

void
GltTextBufferIterator::insert(const char ch)
{
    switch (ch)
    {

    // ENTER

    case 13:

        {
            GltTextBuffer::iterator next = _line;
            next++;

            if (_insert)
            {
                // Split the line, at the horizontal position
                _buffer.insert(next,_line->substr(_x));
            }
            else
            {
                // Split the line, if necessary
                if (_x<_line->length())
                    _buffer.insert(next,_line->substr(_x+1));
                else
                    if (next==_buffer.end())
                        _buffer.push_back(string());
            }

            *_line = _line->substr(0,_x);
            nextLine();
            _x = 0;
        }
        break;

    // BACKSPACE

    case 8:

        // Delete the character to the left of cursor, if possible

        if (_x>0)
        {
            _line->erase(_x-1,1);
            _x--;
        }
        else
        {
            // Merge line with previous line

            if (_line!=_buffer.begin())
            {
                GltTextBuffer::iterator next = _line;
                next--;
                _x = next->length();
                *next += *_line;
                _buffer.erase(_line);
                _line = next;
            }
        }
        break;

    // DELETE

    case 127:

        // Delete the character to the right of cursor, if possible

        if (_x<_line->length())
            _line->erase(_x,1);
        else
        {
            // Merge with next line

            GltTextBuffer::iterator next = _line;
            next++;

            if (next!=_buffer.end())
            {
                *_line += *next;
                _buffer.erase(next);
            }
        }
        break;

    // TAB

    case '\t':

        _line->insert(_x,3,' ');
        _x += 3;
        return;

    ///

    default:

        if (!_insert && _x<_line->length())
            _line->erase(_x,1);

        _line->insert(_x,1,ch);
        _x++;

        // Go to next line, if in wrap mode

        if (_wrap && _x>=_wrapColumn)
        {
            GltTextBuffer::iterator next = _line;
            next++;
            if (_insert)
            {
                _buffer.insert(next,_line->substr(_x));
                *_line = _line->substr(0,_x);
            }
            nextLine();
            _x = 0;
        }

        break;
    }
}

void
GltTextBufferIterator::insert(const std::string &string)
{
    for (uint32 i=0; i<string.size(); i++)
        insert(string[i]);
}

GltTextBuffer::iterator &GltTextBufferIterator::line()       { return _line; }
GltTextBuffer::iterator  GltTextBufferIterator::begin()      { return _buffer.begin(); }
GltTextBuffer::iterator  GltTextBufferIterator::end()        { return _buffer.end();   }

const int GltTextBufferIterator::x() const { return _x; }
