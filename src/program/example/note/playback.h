#ifndef GLT_PLAYBACK
#define GLT_PLAYBACK

#include <misc/timer.h>
#include <glutm/input.h>
#include <glutm/timer.h>

#include <vector>

class GltNoteTerminal;

class GltPlayback : public GlutInput, GlutTimer
{
public:
    GltPlayback(GltNoteTerminal &terminal,unsigned char *buffer = NULL,int size = 0);
    ~GltPlayback();

    void record();
    void clear();
    void play();
    void flush();

    void OnTimer(int i);

    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);

    //
    void copy(void *,uint32 size);

private:
    int  update();

    GltNoteTerminal            &_terminal;

    std::vector<unsigned char>  _buffer;

    bool                        _record;
    bool                        _play;

    Timer                       _timer;
    double                      _speed;

    uint32                      _pos;
};

#endif
