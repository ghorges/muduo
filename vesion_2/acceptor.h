#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "Socket.h"
#include "channel.h"
#include "eventloop.h"
#include <functional>
#include <iostream>

class Socket;
class EventLoop;

class acceptor
{
public:
    typedef std::function<void(int fd)>connectioncallback;

    acceptor(EventLoop* loop,int port);

    void listen();

    void set_conncb(connectioncallback cb)
    {
        conncb = cb;
    }

    void handleread();
private:
    EventLoop* loop_;
    Socket acceptSocket;
    channel cha;
    connectioncallback conncb;

};

#endif // ACCEPTOR_H
