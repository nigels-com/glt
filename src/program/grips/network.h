#ifndef NBODY_NETWORK_H
#define NBODY_NETWORK_H

#include <network/server.h>
#include <network/client.h>
#include <network/httpclient.h>

class Grips;

typedef enum
{
    MESSAGE_STEP = 1024,
    MESSAGE_SET

} GripsMessage;

class GripsServer : public GltServer
{
    friend class Grips;

public:
    GripsServer(Grips &window);
    virtual ~GripsServer();

    void OnTick();

    void sendSync();
    void sendState(Grips &,const std::string &prefix = "");
    void sendTile();

private:

    Grips           &_window;
};

class GripsClient : public GltClient
{
    friend class Grips;

public:
    GripsClient(Grips &);
    ~GripsClient();

    void OnReceive(const int32 val,const void *data,const int32 size);

private:

    Grips      &_window;
};

class GripsHttpClient : public GltHttpClient
{
    friend class Grips;

public:
    GripsHttpClient(Grips &);
    ~GripsHttpClient();

    void OnReceive(const std::string &data);

private:

    Grips      &_window;
};

#endif
