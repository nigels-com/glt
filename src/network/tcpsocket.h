#ifndef MISC_SOCKET_H
#define MISC_SOCKET_H

// Vaguely based on libsocketcpp by Garrett Grice

#include <glt/config.h>

#include <string>
#include <cassert>

#ifdef GLT_WIN32

#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif

#  ifndef NOMINMAX
#    define NOMINMAX
#  endif

#  include <winsock.h>

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

class GltSocketServer;

class GltSocket
{
    friend class GltSocketServer;

protected:
    ///
    GltSocket(int socket);
    /// Copying is not allowed
    GltSocket(const GltSocket &socket);

public:

    GltSocket();
    ~GltSocket();

    typedef enum
    {
        TCP = 0,
        UDP
    }
    Type;

    /// Create socket
    bool create(const GltSocket::Type type = TCP);

    /// Establish connection to remote socket
    bool connect(const std::string &hostname,const int port);
    /// Terminate socket connection
    bool close();

    //
    // Send/Receive
    //

    /// Send raw bytes
    int send(const void *message, const size_t size);
    /// Send contents of c string
    int send(const char *str);
    /// Send contents of std::string
    int send(const std::string &str);

    /// Receive raw bytes
    int recv(void *message, const size_t size);

    int recv(std::string &str);

    //
    // Config
    //

    /// Block-on-input is optional
    bool setBlocking(const bool blocking);

    //
    // Status info
    //

    /// Is the socket currently connected?
    const bool        connected() const;

    /// What message size should be used?
    const int         messageSize() const;

    /// What is the remote IP address?
    const std::string remoteIP()  const;

private:

    int    _socket;
    bool   _connected;
    bool   _blocking;
    size_t _messageSize;

    struct sockaddr_in _local;
    struct sockaddr_in _remote;

    static bool _init;
           bool init();
};

template<class T>
bool
send(GltSocket &socket,const T &val)
{
//  assert(sizeof(T)<256);
    return socket.send(&val,sizeof(T))==sizeof(T);
}

template<class T>
bool
recv(GltSocket &socket,T &val)
{
//  assert(sizeof(T)<256);
    return socket.recv(&val,sizeof(T))==sizeof(T);
}

////////////////

class GltSocketServer
{
protected:
    /// Copying is not allowed
    GltSocketServer(const GltSocketServer &server);

public:

    GltSocketServer();

    ~GltSocketServer();

    /// Bind a socket to a port
    bool bind(const int port, const GltSocket::Type type = GltSocket::TCP);

    /// Listen for connections on a socket
    bool listen() const;

    /// Accept a connection on a socket
    GltSocket *accept() const;

    ///
    bool close();

private:
    GltSocket _socket;
};

/////////////////////////

// TODO - Optional ACK?

class GltSocketProtocol
{
public:

          bool &enable();
    const bool &enable() const;

          int  &port();
    const int  &port() const;

protected:

    GltSocketProtocol();
    virtual ~GltSocketProtocol();

    bool send(GltSocket *socket,const int32 val,const bool ack,const void *data = NULL,const int32 size = 0);
    bool send(GltSocket *socket,const int32 val,const bool ack,const std::string &str);
    bool recv(GltSocket *socket);

    virtual void OnReceive(const int32 val,const void *data,const int32 size);

    bool            _enable;
    int             _port;
};

#endif
