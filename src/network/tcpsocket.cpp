// Vaguely based on libsocketcpp by Garrett Grice

#include "tcpsocket.h"

#include <math/real.h>

#include <cstring>
#include <iostream>

#include <sys/types.h>

#ifdef WIN32
#else
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1
#endif

#ifdef GLT_SGI
#define socklen_t int
#endif

#include <cstdio>
#include <cstdlib>
#include <cassert>
using namespace std;

bool GltSocket::_init = false;

GltSocket::GltSocket()
: _socket(-1), _connected(false), _blocking(true), _messageSize(128)
{
    init();
}

GltSocket::GltSocket(int socket)
: _socket(socket), _connected(false), _blocking(true), _messageSize(128)
{
    init();
}

bool GltSocket::init()
{
    memset(&_local,  0, sizeof(_local));
    memset(&_remote, 0, sizeof(_remote));

    if (_init)
        return true;

    #ifdef GLT_WIN32
    WSADATA wsaData;
    if (WSAStartup(0x0101, &wsaData)!=0)
        return false;
    #endif

    _init = true;
    return true;
}

GltSocket::~GltSocket()
{
    close();
}

bool GltSocket::create(const Type type)
{
    int socket = INVALID_SOCKET;

    switch (type)
    {
    case TCP:
        socket = ::socket(AF_INET, SOCK_STREAM, 0);
        break;

    case UDP:
        socket = ::socket(AF_INET, SOCK_DGRAM, 0);
        break;
    }

    if (socket==int(INVALID_SOCKET))
        return false;

    _socket = socket;

    int size = 1024*300;    // 300 KB
/*   int ok = */
        ::setsockopt(_socket,SOL_SOCKET,SO_RCVBUF,(const char *) &size,sizeof(size));

    return true;
}

//

bool GltSocket::connect(const std::string &hostname,const int port)
{
    hostent *Host;
    if((Host = gethostbyname(hostname.c_str())) == NULL)
        return false;

    memset(&_remote, 0x00, sizeof(_remote));
    _remote.sin_family      = AF_INET;
    _remote.sin_addr        = *((struct in_addr *)Host->h_addr);
    _remote.sin_port        = htons(port);

    _connected = ::connect(_socket, (struct sockaddr *)&_remote, sizeof(struct sockaddr)) != SOCKET_ERROR;

    setBlocking(_blocking);

    return _connected;
}

int GltSocket::send(const void *message, const size_t size)
{
    // Keep track of total bytes sent
    size_t total = 0;
    // For pointer arithmetic, convenient to have const char ptr
    const char *buff = static_cast<const char *>(message);

    // Loop until entire message is sent
    while (total<size)
    {
        // Send a message
        size_t bytes = ::send(_socket,buff+total, std::min(_messageSize,size-total), 0);

        // Check for an error
//      assert(!_blocking || bytes!=SOCKET_ERROR);

        // Be graceful about errors
        if (bytes==(size_t) SOCKET_ERROR)
            break;

        // Accumulate total bytes sent
        total += bytes;

        // In non-blocking mode, send only one message
        if (!_blocking)
            break;
    }

    return total;
}

int
GltSocket::send(const char *str)
{
    return send(str,strlen(str));
}

int
GltSocket::send(const std::string &str)
{
    return send(str.c_str(),str.size());
}

int
GltSocket::recv(void *message, const size_t size)
{
    // Keep track of total bytes received
    size_t total = 0;
    // For pointer arithmetic, convenient to have const char ptr
    char *buff = static_cast<char *>(message);

    // Loop until entire message is received
    while (total<size)
    {
        // Receive a message
        int bytes = ::recv(_socket, buff+total, size-total, 0);

        // Check for an error
//      assert(!_blocking || bytes!=SOCKET_ERROR);

//      cout << bytes << endl;

        // Be graceful about errors
        if (bytes==SOCKET_ERROR)
        {
            _connected = false;
            break;
        }

        // Accumulate total bytes received
        total += bytes;

        // In blocking mode, this means disconnect
        if (_blocking && size_t(bytes)<size)
        {
            _connected = false;
            break;
        }

        // In an error has happened, stop
        if (errno!=0 && errno!=EAGAIN)
        {
            _connected = false;
            return total;
        }

        // In non-blocking mode, receive only one message
        if (!_blocking || errno!=EAGAIN)
            break;

//      Sleep(500);
    }

//    cout << errno << endl;

    return total;
}

int
GltSocket::recv(std::string &str)
{
    return GltSocket::recv((void *) str.c_str(),str.size());
}

bool GltSocket::close()
{
    if (_socket==-1)
        return true;

#ifdef GLT_WIN32
    if (::closesocket(_socket)==SOCKET_ERROR)
        return false;
#else
    if (::close(_socket)!=0)
        return false;
#endif

    _socket = -1;
    _connected = false;

    return true;
}

bool GltSocket::setBlocking(const bool blocking)
{
    _blocking = blocking;

    #ifdef GLT_WIN32
    if (_socket!=-1)
    {
        unsigned long b = !_blocking;
        bool ok = ::ioctlsocket(_socket,FIONBIO,&b)==0;
        assert(ok);
        return ok;
    }
    #else
    if (_socket!=-1)
    {
        int flags = fcntl(_socket,F_GETFL);

        if (_blocking)
            flags &= ~O_NONBLOCK;
        else
            flags |= O_NONBLOCK;

        return fcntl(_socket,F_SETFL,flags)==flags;
    }
    #endif

    return false;
}

//

const bool
GltSocket::connected() const
{
    return _connected;
}

const int
GltSocket::messageSize() const
{
    return _messageSize;
}

const std::string
GltSocket::remoteIP() const
{
   return inet_ntoa(_remote.sin_addr);
}

////////////////

GltSocketServer::GltSocketServer()
{
}

GltSocketServer::~GltSocketServer()
{
}

bool
GltSocketServer::bind(const int port, const GltSocket::Type type)
{
    if (!_socket.create(type))
        return false;

    memset(&_socket._local, 0x00, sizeof(_socket._local));
    _socket._local.sin_family      = AF_INET;
    _socket._local.sin_addr.s_addr = INADDR_ANY;
    _socket._local.sin_port        = htons(port);

    if (::bind(_socket._socket,(struct sockaddr*) &_socket._local,sizeof(_socket._local))==SOCKET_ERROR)
        return false;

    _socket.setBlocking(false);

   return true;
}

bool
GltSocketServer::listen() const
{
    if (::listen(_socket._socket,5)==SOCKET_ERROR)
        return false;

   return true;
}

GltSocket *
GltSocketServer::accept() const
{
    #ifdef GLT_WIN32
    int len = sizeof(_socket._remote);
    #else
    socklen_t len = sizeof(_socket._remote);
    #endif

    int socket = ::accept(_socket._socket,(struct sockaddr *) &_socket._remote,&len);

    if (socket==int(INVALID_SOCKET))
        return NULL;

    GltSocket *connect = new GltSocket(socket);
    connect->_local  = _socket._local;
    connect->_remote = _socket._remote;
    connect->_connected = true;

    connect->setBlocking(connect->_blocking);

    return connect;
}

bool
GltSocketServer::close()
{
    return _socket.close();
}

///////////////////////////////////////////////////////////

GltSocketProtocol::GltSocketProtocol()
: _enable(false),
  _port(5001)
{
}

GltSocketProtocol::~GltSocketProtocol()
{
}

bool
GltSocketProtocol::send(GltSocket *socket,const int32 val,const bool ack,const void *data,const int32 size)
{
    if (!socket)
        return false;

    // Header is two integers, id and size of extra data

    int32 header[3] = { val,size,int(ack)};
    bool ok = (socket->send(&header,sizeof(header))==sizeof(header));

    // If there is extra data, send it

    if (size)
        ok &= (socket->send(data,size)==size);

    // Wait for an ACK

    assert(ok);

    if (ack)
    {
        unsigned char ack = 0;
        if (ok)
            ok &= (socket->recv(&ack,1)==1 && ack==255);
        assert(ok);
    }

    return ok;
}

bool
GltSocketProtocol::send(GltSocket *socket,const int32 val,const bool ack,const string &str)
{
    return send(socket,val,ack,str.c_str(),str.size());
}

bool
GltSocketProtocol::recv(GltSocket *socket)
{
    if (!socket)
        return false;

    while (socket->connected())
    {
        // Receive header

        socket->setBlocking(false);
        int32 header[3] = { 0,0,0 };
        bool ok = (socket->recv(&header,sizeof(header))==sizeof(header));

        // If header not available, break out of loop

        if (!ok)
            return true;

        // If there is extra data, get it

        socket->setBlocking(true);

        const int32 &val  = header[0];
        const int32 &size = header[1];
        const bool   ack  = header[2]!=0;

        if (ok)
        {
            // Allocate buffer

            char *buffer = size ? new char[size] : NULL;

            // Receive buffer from network

            ok &= (socket->recv(buffer,size)==size);

            // Send ACK

            if (ack)
            {
                unsigned char ack = 255;
                if (ok)
                    ok &= (socket->send(&ack,1)==1);
            }

            // Call application message handler

            if (ok)
                OnReceive(val,buffer,size);

            // Free buffer

            delete [] buffer;
        }
    }

    // Socket is not connected

    return false;
}

void
GltSocketProtocol::OnReceive(const int32 val,const void *data,const int32 size)
{
    // Do nothing by default
}

      bool &GltSocketProtocol::enable()       { return _enable; }
const bool &GltSocketProtocol::enable() const { return _enable; }

      int  &GltSocketProtocol::port()         { return _port; }
const int  &GltSocketProtocol::port() const   { return _port; }

