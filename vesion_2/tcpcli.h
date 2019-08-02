#ifndef TCPCLI_H
#define TCPCLI_H

#include "channel.h"
#include "buffer.h"
#include "noncopyable.h"
#include "eventloop.h"
#include <functional>
#include "Socket.h"
#include <iostream>
#include <string>
#include <assert.h>

class tcpcli : public noncopyable
{
public:
    tcpcli(EventLoop* loop,int port,std::string address);
public:
    typedef std::function<void(channel& conn, buffer& buf)> messagecallback;
    typedef std::function<void(channel& conn)> connectioncallback;

    void set_messagecb(messagecallback cb)
    {
        onmessage = cb;
    }

    void set_connetction(connectioncallback cb)
    {
        onconnection = cb;
    }

    void connection();
    void newconnection(int fd);
private:
    EventLoop* loop_;
    Socket clisocket;
    int port;
    std::string address;
    messagecallback onmessage;
    connectioncallback onconnection;
};

#endif // TCPCLI_H
