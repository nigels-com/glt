#include "httpclient.h"

#include <misc/string.h>
#include <glt/error.h>

#include <vector>
#include <iostream>
using namespace std;

//////////////////

GltHttpClient::GltHttpClient()
: _enable(false),
  _tickTime(1000),      // 1 Hz
  _url(""),
  _thread(*this),
  _shutdown(false),
  _relaxTime(1000)      // 1 Hz
{
    setTick(_tickTime);
}

GltHttpClient::~GltHttpClient()
{
}

void GltHttpClient::OnTick()
{
    _mutex.lock();
    if (_enable && _buffer.size())
        OnReceive(_buffer);
    _buffer.resize(0);
    _mutex.unlock();

     setTick(_tickTime);
}


bool GltHttpClient::connected() const
{
    return _enable && GltSocket::connected();
}

bool GltHttpClient::connect()
{
    if (_enable)
    {
        if (!connected())
        {
            GltSocket::create();

            // Determine the host name and port number

            string protocol = "http";
            string host = "localhost";
            int port = 80;
            string location = "";
            urlSplit(_url,protocol,host,port,location);

            #ifndef NDEBUG
            cout << "HTTP Client connecting to " << host << ':' << port << endl;
            #endif

            if (GltSocket::connect(host,port))
            {
                assert(connected());

                #ifndef NDEBUG
                cout << "HTTP connection established to ";
                cout << GltSocket::remoteIP() << "..." << endl;
                #endif

                return true;
            }
        }
        else
            return true;
    }

    return false;
}

void GltHttpClient::receive()
{
    if (!_enable)
        return;

    // Determine the host name and port number

    string protocol = "http";
    string host = "localhost";
    int port = 80;
    string location = "";
    urlSplit(_url,protocol,host,port,location);

    // Form a HTTP GET request
    string httpGet;
    sprintf(httpGet,"GET %s HTTP/1.0\n\n",location.c_str());

    GltSocket::setBlocking(true);
    GltSocket::send(httpGet);

    // Receive response from server

    vector<string> v;

    for (;;)
    {
        const int blockSize = 10*1024;

        v.push_back(string());
        v.back().resize(blockSize);
        int bytes = GltSocket::recv(v.back());

        if (bytes!=blockSize)
            v.back().resize(bytes);

        if (!bytes)
            break;
    }

    // Close socket connection to server
    if (!GltSocket::close())
        gltWarning("Failed to close socket in GltHttpClient::receive()");

    // Merge blocks into one string

    string buffer;
    stringMerge(v,buffer,"");

    // Ignore headers
    string::size_type i;

    for (i=3; i<buffer.size(); i++)
        if (buffer[i-3]==13 && buffer[i-2]==10 && buffer[i-1]==13 && buffer[i]==10)
        {
            i++;
            break;
        }

    if (i<buffer.size())
    {
        _mutex.lock();
        _buffer = buffer.substr(i);
        _mutex.unlock();
    }
}

void GltHttpClient::OnReceive(const std::string &data)
{
}

GltFieldPtr GltHttpClient::settings()
{
    GltFields *root = new GltFields("httpClient");
    root->add(_enable,   "enable"   );
    root->add(_tickTime, "tickTime" );
    root->add(_url,      "url"      );
    root->add(_relaxTime,"relaxTime");
    return root;
}

      std::string &GltHttpClient::url()       { return _url; }
const std::string &GltHttpClient::url() const { return _url; }

/////////////////////////////////

GltHttpClient::GltHttpClientThread::GltHttpClientThread(GltHttpClient &client)
: pt::thread(false), _client(client)
{
    start();
}

GltHttpClient::GltHttpClientThread::~GltHttpClientThread()
{
    _client._shutdown = true;
    signal();
    waitfor();
}

void
GltHttpClient::GltHttpClientThread::execute()
{
    while (!_client._shutdown)
    {
        if (_client._enable && _client._url.size())
        {
            _client.connect();

            if (_client.connected())
                _client.receive();
        }

        relax(_client._relaxTime);
    }
}

void
GltHttpClient::GltHttpClientThread::cleanup()
{
}
