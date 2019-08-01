#ifndef CHANNEL_H
#define CHANNEL_H

#include "noncopyable.h"
#include "eventloop.h"
#include "buffer.h"
#include <functional>
#include <iostream>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <memory>
#include <string>
#include <poll.h>

class EventLoop;

class channel : public noncopyable,public std::enable_shared_from_this<channel>
{
public:
    typedef std::function<void(void)> callback;

    channel(EventLoop* loop,int fd);

    int getfd(){return fd_;}
    int set_event(int t){event_ = t;}
    int get_event(){return event_;}
    int set_nblock(){int oflag = fcntl(fd_,F_GETFL,0);
                     fcntl(fd_,F_SETFL,oflag | O_NONBLOCK);}
    void handle_event();
    void set_readcb(callback t){readcallback = t;}
    void set_writecb(callback t){writecallback = t;}
    //emmmm MGD
    void set_errcb(callback t){errcallback = t;}
    callback get_readcb(){return readcallback;}
    callback get_writecd(){return writecallback;}
    void listen_fd();
    void error_fd();
    void read_fd();
    void write_fd();


    int sendmessage_(std::string message,int length);
    int getmessage_();
    void send_data();

    void set_onmessage(const std::function<void(channel& conn, buffer& buf)> foo)
    {
        onmessage = foo;
    }

    void set_connection(const std::function<void(channel& conn)> foo)
    {
        onconnection = foo;
    }

private:
    EventLoop *loop_;

    int fd_;
    //look
    int event_;
    //epoll return
    int revent_;
    bool write_ok;

    callback readcallback;
    callback writecallback;
    callback errcallback;

    std::function<void(channel& conn, buffer& buf)> onmessage;
    std::function<void(channel& conn)> onconnection;

    buffer sendmess_;
    buffer getmess_;
};

#endif // CHANNEL_H
