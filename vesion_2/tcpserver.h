#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "acceptor.h"
#include "channel.h"
#include "buffer.h"
#include "noncopyable.h"
#include "eventloop.h"
#include <functional>
#include <iostream>

class tcpserver : public noncopyable
{
public:
    typedef std::function<void(channel& conn, buffer& buf)> messagecallback;
    typedef std::function<void(channel& conn)> connectioncallback;
    tcpserver(EventLoop* loop,int port);

    void set_messagecb(messagecallback cb)
    {
        onmessage = cb;
    }

    void set_connetction(connectioncallback cb)
    {
        onconnection = cb;
    }

    void newconnection(int fd);
private:
    EventLoop* loop_;
    acceptor acceptor_;
    messagecallback onmessage;
    connectioncallback onconnection;
};

#endif // TCPSERVER_H
