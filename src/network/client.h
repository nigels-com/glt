#ifndef GLT_CLIENT_H
#define GLT_CLIENT_H

#include <node/fields.h>
#include <glutm/timer.h>
#include <network/tcpsocket.h>

////////////////////////////////

class GltClient: public GltSocketProtocol, public GlutTimer
{
public:
             GltClient();
    virtual ~GltClient();

    /// Tick callback function
    void OnTick();

    virtual void OnReceive(const int32 val,const void *data,const int32 size);

    virtual GltFieldPtr settings();

    bool connected() const;

          std::string &host();
    const std::string &host() const;

protected:

    bool connect();
    void receive();

    std::string _host;
    GltSocket   _socket;
};

#endif
