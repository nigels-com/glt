#ifndef GLT_SERVER_H
#define GLT_SERVER_H

#include <node/fields.h>
#include <glutm/timer.h>
#include <network/tcpsocket.h>

#include <list>

////////////////////////////////

class GltServer : public GltSocketProtocol, public GlutTimer
{
public:
             GltServer(const int maxConnections = 1);
    virtual ~GltServer();

    /// Tick callback function
    void OnTick();

    virtual GltFieldPtr settings();

    int connected() const;

protected:

    virtual bool connect();

    GltSocketServer  _server;
    bool             _listening;
    int              _maxConnections;

    typedef std::list<GltSocket *> SocketList;
    typedef SocketList::iterator   SocketListIterator;

    SocketList _channel;
};

#endif
