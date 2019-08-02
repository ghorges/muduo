#include "Socket.h"


int Socket::socket_fd()
{
    int fd = ::socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,IPPROTO_TCP);
    if(fd < 0)
    {
        std::cout << "fd err" << "\n";
    }
    return fd;
}

void Socket::bind_fd(int port)
{
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ::bind(fd_,(struct sockaddr*)&my_addr,sizeof(my_addr));
}

int Socket::connect_fd(int port,std::string address)
{
    struct sockaddr_in con_addr;
    memset(&con_addr,0,sizeof(con_addr));
    con_addr.sin_family = AF_INET;
    con_addr.sin_port = htons(port);
    con_addr.sin_addr.s_addr = inet_addr(address.c_str());

    while(1)
    {
        int ret = connect(fd_,(struct sockaddr *)&con_addr,sizeof(con_addr));
        if(ret != -1)
            break;
        //err 114　is Operation already in progress
        //err 115 is Operation now in progress
        if(errno == 114 || errno == 115)
        {
            continue;
        }
        else
        {
            //err 106 is Transport endpoint is already connected
            if(errno == 106)
                break;
            else
            {
                perror("err:");
                std::cout << errno << std::endl;
                return -1;
            }
        }
    }
    return 0;
}

void Socket::listen_fd()
{
    listen(fd_,5);
}

int Socket::accept_fd()
{
    struct sockaddr_in addr;
    socklen_t t = sizeof(addr);
    int fd = accept(fd_,(struct sockaddr*)&addr,&t);
    return fd;
}

void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY,
                 &optval, static_cast<socklen_t>(sizeof optval));
    // FIXME CHECK
}

void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR,
                 &optval, static_cast<socklen_t>(sizeof optval));
    // FIXME CHECK
}

void Socket::setReusePort(bool on)
{
#ifdef SO_REUSEPORT
    int optval = on ? 1 : 0;
    int ret = ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT,
                           &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0 && on)
    {
        std::cout << "setReusePort err:" << "\n";
    }
#endif
}
