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

class EventLoop;

class channel : public noncopyable
{
public:
    typedef std::function<void(void)> callback;
    typedef std::function<void(const channel& conn, buffer* buf)> cli_callback;

    channel(EventLoop* loop,int fd,int event);

    int getfd(){return fd_;}
    int set_event(int t){event_ = t;}
    int get_event(){return event_;}
    int get_start_event(){return start_event_;}
    int set_nblock(){int oflag = fcntl(fd_,F_GETFL,0);
                     fcntl(fd_,F_SETFL,oflag | O_NONBLOCK);}
    void handle_event();
    void set_readcb(callback t){readcallback = t;}
    void set_writecb(callback t){writecallback = t;}
    callback get_readcb(){return readcallback;}
    callback get_writecd(){return writecallback;}
    void listen_fd();
    void error_fd();

    int sendmessage_(std::string message,int length);
    int getmessage_();

private:
    EventLoop *loop_;

    int fd_;
    int event_;
    const int start_event_;
    bool write_ok;

    callback readcallback;
    callback writecallback;
    callback errcallback;

    static cli_callback client_readcb;
    static cli_callback client_writecb;

    buffer sendmess_;
    buffer getmess_;

};

#endif // CHANNEL_H
