#include "Socket.h"
#include "eventloop.h"
#include "channel.h"
#include "buffer.h"
#include "tcpserver.h"
#include <math.h>

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <functional>

using namespace std;


class echoserver
{
public:
    echoserver(EventLoop* p,int port):loop_(p),server(p,port)
    {
        using namespace std::placeholders;
        server.set_connetction(std::bind(&echoserver::onconnection,this,_1));
        server.set_messagecb(std::bind(&echoserver::onmessage,this,_1,_2));
    }

    void onconnection(channel& bar)
    {
        bar.sendmessage_("12331",10);
    }

    void onmessage(channel& bar,buffer& foo)
    {
        cout << foo.c_str() << endl;
        string t = "GET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCGET / HTTP/1.1Host: 127.0.0.1:8888Connection: keep-aliveCache-Control: max-age=0Upgrade-Insecure-Requests: 1User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77 Safari/537.36Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8Accept-Encoding: gzip, deflate, br";
//        bar.sendmessage_(t,t.size());
//        bar.sendmessage_(t,t.size());
//        bar.sendmessage_(t,t.size());
//        bar.sendmessage_(t,t.size());
//        bar.sendmessage_(t,t.size());
//        bar.sendmessage_(t,t.size());
//        bar.sendmessage_(t,t.size());
//        bar.sendmessage_(t,t.size());
    }

private:
    EventLoop* loop_;
    tcpserver server;
};

int main(int argc,char* argv[])
{
    EventLoop p;
    echoserver servers(&p,8888);
    p.loop();
    cout << "Hello everone\ni'm mayicheng" << endl;
    return 0;
}
