#ifndef socket_H
#define socket_H

#include "noncopyable.h"
#include <memory>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <assert.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class Socket : public noncopyable /*public std::enable_shared_from_this*/
{
public:
    static Socket* get_Socket(short port);
    static Socket* sock;
    int get_fd(){return Socket::listenfd;}
    int get_port(){return Socket::port_;}
    ~Socket();
    void start();

private:
    Socket(short port);
    int listenfd;
    short port_;
};

#endif // Socket_H
