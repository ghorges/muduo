#ifndef socket_H
#define socket_H

#include "noncopyable.h"
#include <memory>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <assert.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <netinet/tcp.h>
#include <string.h>

class Socket : public noncopyable /*public std::enable_shared_from_this*/
{
public:
    Socket(int fd) : fd_(fd){}

    static int socket_fd();

    int get_fd(){ return fd_; }
    void bind_fd(int port);
    void listen_fd();
    int accept_fd();

    int connect_fd(int port,std::string address);

    //setsockopt
    void setTcpNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);
private:
    int fd_;
};

#endif // Socket_H
