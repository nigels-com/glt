#include "client.h"

#include <iostream>
using namespace std;

//////////////////

GltClient::GltClient()
: _host("localhost")
{
    setTick(1000/200);  // 200Hz
}

GltClient::~GltClient()
{
}

void GltClient::OnTick()
{
    connect();

    if (connected())
        receive();
}


bool GltClient::connected() const
{
    return _enable && _socket.connected();
}

bool GltClient::connect()
{
    if (_enable)
    {
        if (!_socket.connected())
        {
            _socket.create();

            cout << "Client connecting to server at " << _host << ":" << _port << endl;

            if (_socket.connect(_host,_port))
            {
                    cout << "Client connection established to ";
                    cout << _socket.remoteIP() << "..." << endl;
                    _socket.setBlocking(false);
                    return true;
            }
        }
        else
            return true;
    }

    return false;
}

void GltClient::receive()
{
    recv(&_socket);
}

void GltClient::OnReceive(const int32 val,const void *data,const int32 size)
{
}

GltFieldPtr GltClient::settings()
{
    GltFields *root = new GltFields("client");
    root->add(_enable,"enable");
    root->add(_host,  "host");
    root->add(_port,  "port");
    return root;
}

      std::string &GltClient::host()       { return _host; }
const std::string &GltClient::host() const { return _host; }
