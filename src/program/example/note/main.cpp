
#include <glutm/master.h>
#include <glutm/window.h>

#include <glt/fontasci.h>
#include <glt/color.h>
#include <glt/rgb.h>

#include <misc/timer.h>
#include <misc/string.h>

#include <fonts/fonts.h>

#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#include "terminal.h"
#include "playback.h"
#include "rasterb.h"

string outfile;

const int magicSize = 8;
const int messageSize = 1024*16;    // 16K Message Size maximum
const int messageTail = 6;          // 6 bytes at the end

unsigned char message[magicSize+messageSize+messageTail] =
{
    0x25, 0x10, 0x19, 0x74, 0x19, 0x89, 0x20, 0x01,  // Magic
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   // Empty recording
};

class GltNoteWindow : public GlutWindow
{
public:
    GltNoteWindow
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );

    ~GltNoteWindow();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnTick();
    void OnReshape(int w, int h);
//    void OnTimer(unsigned char val);
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);
    void OnMenu(int value);

protected:
    GltFontAscii    _font;
    GltNoteTerminal _terminal;
    GltPlayback     _play;
    float           _playSpeed;

    GltViewport     _textBox;
    GltRasterBar    _bar1;
    GltRasterBar    _bar2;
    GltRasterBar    _bar3;
    Timer           _time;

    typedef enum
    {
        NOTE_PLAY,
        NOTE_CLEAR,
        NOTE_RECORD,
        NOTE_SAVE
    } MenuCallbacks;

    const static int _timer;
};

const int GltNoteWindow::_timer = 1;

GltNoteWindow::GltNoteWindow(int width,int height,int x,int y)
: GlutWindow("GLT Note",width,height,x,y,GLUT_DOUBLE|GLUT_RGBA),
  _terminal(_font),
  _play(_terminal,message+magicSize,messageSize),
  _playSpeed(3.0),      // 3x realtime typing speed
  _bar1(red*0.4,red),
  _bar2(green*0.4,green),
  _bar3(blue*0.4,blue)
{
}

GltNoteWindow::~GltNoteWindow()
{
}

void
GltNoteWindow::OnOpen()
{
    _font.init(iso14Font);

    // Go into play mode and start timer
    _play.play();
    setTick(10);    // 100 FPS max

    _bar1.height() = _bar2.height() = _bar3.height() = .03;

    _leftButtonMenu.addEntry("Play"   ,NOTE_PLAY);
    _leftButtonMenu.addEntry("Clear"  ,NOTE_CLEAR);
    _leftButtonMenu.addEntry("Record" ,NOTE_RECORD);
    _leftButtonMenu.addEntry("Save"   ,NOTE_SAVE);
    _leftButtonMenu.addEntry("Exit"   ,MENU_CLOSE);
    _leftButtonMenu.attach();

    glShadeModel(GL_SMOOTH);
    glDisable(GL_LIGHTING);
}

void
GltNoteWindow::OnClose()
{
    _font.init(NULL);
}

void
GltNoteWindow::OnReshape(int w, int h)
{
    GlutWindow::OnReshape(w,h);

    _textBox.x() = 5;
    _textBox.y() = 5;
    _textBox.width() = _viewport.width()-10;
    _textBox.height() = _viewport.height()-10;
}

void
GltNoteWindow::OnDisplay()
{
//    GlutWindow::OnDisplay();

    black.glClearColor();
    glClear(GL_COLOR_BUFFER_BIT);

    double t = _time.elapsed()*0.5;

    _bar1.pos() = sin(t)*0.9;
    _bar2.pos() = sin(t-0.4)*0.9;
    _bar3.pos() = sin(t-0.8)*0.9;

    _bar3.draw();
    _bar2.draw();
    _bar1.draw();

    _terminal.draw(_textBox);
}

void
GltNoteWindow::OnTick()
{
    postRedisplay();
}

void
GltNoteWindow::OnKeyboard(unsigned char key, int x, int y)
{
    _play.OnKeyboard(key,x,y);

    // Let some keys through to base class

    switch (key)
    {
        case 27:
            GlutWindow::OnKeyboard(key,x,y);
            break;
    }

    postRedisplay();
}

void
GltNoteWindow::OnSpecial(int key, int x, int y)
{
    _play.OnSpecial(key,x,y);
    postRedisplay();
}

void
GltNoteWindow::OnMenu(int value)
{
    switch (value)
    {
    case NOTE_PLAY:     _play.play();   break;
    case NOTE_CLEAR:    _play.clear();  break;
    case NOTE_RECORD:   _play.record(); break;

    case NOTE_SAVE:
        {
            if (outfile.size())
            {
                // Read the EXE into memory

                string exe;
                ifstream is(outfile.c_str(),ios::in|ios::binary);
                readStream(is,exe);

                // Replace message

                string::size_type i = exe.find(string((char *) message,magicSize));

                if (i!=string::npos)
                    _play.copy(&exe[i]+magicSize,messageSize+messageTail);

                // Write EXE

                string file(outfile);
#ifdef WIN32
                file = file.substr(file.rfind('\\')+1);
#else
                file = file.substr(file.rfind('/')+1);
#endif
                file = string("_") + file;

                ofstream os(file.c_str(),ios::out|ios::binary);
                writeStream(os,exe);
            }
        }
        break;

    default:
        GlutWindow::OnMenu(value);
    }
}

#include <glutm/main.h>

bool GlutMain(const std::vector<std::string> &arg)
{
    if (arg.size())
        outfile = arg.front();

    cout << endl;
    cout << "note" << endl;
    cout << endl;
    cout << "(C) 2001 Nigel Stewart (nigels@nigels.com)" << endl;
    cout << "Source code available under terms of LGPL." << endl;
    cout << "For updates, source code and information:" << endl;
    cout << "http://www.nigels.com/glt/" << endl;
    cout << endl;
    cout << "Usage: note" << endl;
    cout << endl;

    static GlutWindow *main = new GltNoteWindow(400,300,10,10);
    main->open();

    return true;
}

