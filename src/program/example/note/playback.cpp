#include "playback.h"

#include "terminal.h"

GltPlayback::GltPlayback(GltNoteTerminal &terminal,unsigned char *buffer,int size)
: _terminal(terminal),
  _record(false),
  _play(true),
  _speed(4.0),
  _pos(0)
{
    int i=0;

    while (i<size)
    {
        if (buffer[i]==0)
            break;
        else
            i++;

        if (buffer[i]==0)
            i += 5;
        else
            i++;
    }

    _buffer.insert(_buffer.begin(),buffer,buffer+i);
}

GltPlayback::~GltPlayback()
{
}

void
GltPlayback::record()
{
    flush();
    _record = true;
    _play   = false;
    _timer.start();
}

void
GltPlayback::play()
{
    _record = false;
    _play   = true;         // Play mode
    _pos    = 0;            // Begin at the start
    _terminal.clear();      // Clear terminal
    setTimer(1);            // Start playback
}

void
GltPlayback::clear()
{
    _pos    = 0;
    _terminal.clear();
    _buffer.clear();
    record();
}

int
GltPlayback::update()
{
    if (_pos<_buffer.size() && _buffer[_pos]!=0)
    {
        _pos++;

        const unsigned char key = _buffer[_pos++];

        if (key)
            _terminal.OnKeyboard(key,0,0);
        else
        {
            const int a = _buffer[_pos++];
            const int b = _buffer[_pos++];
            const int c = _buffer[_pos++];
            const int d = _buffer[_pos++];
            _terminal.OnSpecial(a<<24 | b<<16 | c<<8 | d ,0,0);
        }

        return _buffer[_pos];
    }

    return -1;
}

void
GltPlayback::flush()
{
    _record = false;
    _play = true;
    while (update()>=0);
}

void
GltPlayback::OnKeyboard(unsigned char key, int x, int y)
{
    if (_record && key!=0)
    {
        // Store time as tenths of a second
        unsigned int time = (unsigned int) floor(_timer.elapsed()*10);

        // Clamp the time to the range of an unsigned char
        time = clamp(time,1u,255u);

        // Store the time interval and keypress
        _buffer.push_back(time);
        _buffer.push_back(key);

        // Restart the timer
        _timer.start();
    }

    if (!_play)
        _terminal.OnKeyboard(key,x,y);
}

void
GltPlayback::OnSpecial(int key, int x, int y)
{
    if (_record)
    {
        // Store time as tenths of a second
        unsigned int time = (unsigned int) floor(_timer.elapsed()*10);

        // Clamp the time to the range of an unsigned char
        time = clamp<int>(time,1,255);

        // Store the time and full integer code
        _buffer.push_back(time);
        _buffer.push_back(0);
        _buffer.push_back((key>>24)&0xff);
        _buffer.push_back((key>>16)&0xff);
        _buffer.push_back((key>>8)&0xff);
        _buffer.push_back(key&0xff);

        // Restart the timer
        _timer.start();
    }

    if (!_play)
        _terminal.OnSpecial(key,x,y);
}

//

void
GltPlayback::OnTimer(int i)
{
    if (_record)
        return;

    int delay = 0;

    while (delay==0)
    {
        delay = update();

        // Finished?
        if (delay<0)
            return;

        if (delay>0)
            setTimer(clamp<int>((int) floor(100*delay/_speed),1,10000));
    }
}

void
GltPlayback::copy(void *buffer,uint32 size)
{
    memset(buffer,0,size);
    memcpy(buffer,&_buffer[0],std::min(_buffer.size(),size-6));
}


