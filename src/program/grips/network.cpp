#include "network.h"

#include "document.h"
#include "window.h"

#include <misc/string.h>

#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;

GripsServer::GripsServer(Grips &window)
: _window(window)
{
    // Server doesn't need to respond quickly,
    // so we schedule slow updates (calls to OnTick)

    setTick(1000/10);   // 10 ticks per second
}

GripsServer::~GripsServer()
{
}

void
GripsServer::OnTick()
{
    const int slaves = _window.tileX*_window.tileY-1;

    if (connected()<slaves)
        if (connect())
        {
            sendState(_window);
            sendTile();
        }
}

void
GripsServer::sendSync()
{
    for (SocketListIterator i=_channel.begin(); i!=_channel.end(); i++)
        if ((*i)->connected())
        {
            if (!send(*i,MESSAGE_STEP,false))
            {
//              delete _channel;
//              _channel = NULL;
            }
        }
}

void
GripsServer::sendState(Grips &window,const std::string &prefix)
{
    for (SocketListIterator i=_channel.begin(); i!=_channel.end(); i++)
        if ((*i)->connected())
        {

            // Convert state to string

            ostringstream os;
            window.write(os,prefix);
            string str = os.str();

            if (!send(*i,MESSAGE_SET,true,str))
            {
//              delete _channel;
//              _channel = NULL;
            }

            cout << "Sent " << prefix << " state..." << endl;
        }
}

void
GripsServer::sendTile()
{
    int tile=1;

    for (SocketListIterator i=_channel.begin(); i!=_channel.end(); i++)
        if ((*i)->connected())
        {
            string str;
            sprintf(str,"grips.display.tile.index: %d\n",tile);

            if (!send(*i,MESSAGE_SET,true,str))
            {
//              delete _channel;
//              _channel = NULL;
            }

            cout << "Sent tile... " << tile << endl;

            tile++;
        }
}

////////////////////////

GripsClient::GripsClient(Grips &window)
: _window(window)
{
    // Slaves need to synchronised with events from the server,
    // so we schedule frequent updates (100Hz)

    setTick(1000/100);  // 100Hz
    setTick(1000/50);   // 50Hz
}

GripsClient::~GripsClient()
{
}

void
GripsClient::OnReceive(const int32 val,const void *data,const int32 size)
{
    switch (val)
    {
    case MESSAGE_STEP:
        {
            _window._document->iterate(_window._display.steps);
            _window.postRedisplay();
            break;
        }

    case MESSAGE_SET:
        {
            string str(static_cast<const char *>(data));
            _window.read(str);

            // The received settings from the server
            // should not interfere with current setup

            _window._server.enable() = false;
            _enable = true;

            // Trigger a redraw

            _window.postRedisplay();
            break;
        }

    default:
        assert(0);
        break;
    }
}

/////////////////////////////////////////

GripsHttpClient::GripsHttpClient(Grips &window)
: _window(window)
{
}

GripsHttpClient::~GripsHttpClient()
{
}

void
GripsHttpClient::OnReceive(const std::string &data)
{
    if (_enable)
    {
        _window.read(data);
        _window.postRedisplay();
    }
}

