#include "server.h"

#include <iostream>
using namespace std;

//////////////////

GltServer::GltServer(const int maxConnections)
: _listening(false),
  _maxConnections(maxConnections)
{
}

GltServer::~GltServer()
{
}

void GltServer::OnTick()
{
    connect();
}

int GltServer::connected() const
{
    return _channel.size();
}

bool GltServer::connect()
{
    if (_enable)
    {
        if (!_listening)
        {
            cout << "Server is accepting connections on port " << _port << "..." << endl;

            _server.close();
            _server.bind(_port);
            _listening = _server.listen();
        }

        GltSocket *channel = _server.accept();

        if (channel)
        {
                cout << "Connection accepted from ";
                cout << channel->remoteIP() << "..." << endl;

                _channel.push_back(channel);

                cout << _channel.size() << " connections in total..." << endl;

                return true;
        }
    }

    return false;
}

GltFieldPtr GltServer::settings()
{
    GltFields *root = new GltFields("server");
    root->add(_enable,"enable");
    root->add(_port,"port");
    return root;
}

