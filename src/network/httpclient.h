#ifndef GLT_HTTPCLIENT_H
#define GLT_HTTPCLIENT_H

#include <node/fields.h>
#include <glutm/timer.h>
#include <network/tcpsocket.h>

#include <ptypes/pasync.h>

////////////////////////////////

class GltHttpClient : public GltSocket, public GlutTimer
{
public:
             GltHttpClient();
    virtual ~GltHttpClient();

    /// Tick callback function
    void OnTick();

    virtual void OnReceive(const std::string &data);

    virtual GltFieldPtr settings();

    bool connected() const;

          std::string &url();
    const std::string &url() const;

protected:

    class GltHttpClientThread : public pt::thread
    {
    public:
        GltHttpClientThread(GltHttpClient &client);
        ~GltHttpClientThread();

        void execute();
        void cleanup();

    private:
        GltHttpClient &_client;
    };

    friend class GltHttpClientThread;

    bool connect();
    void receive();

    bool                 _enable;
    uint32               _tickTime;
    std::string          _url;

    std::string          _buffer;
    pt::mutex            _mutex;
    GltHttpClientThread  _thread;
    bool                 _shutdown;
    uint32               _relaxTime;
};

#endif
