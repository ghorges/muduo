#include "Socket.h"

Socket* Socket::sock = NULL;

Socket::Socket(short port)
{
    port_ = port;
    listenfd = socket(AF_INET,SOCK_STREAM,0);

    int on = 1;
    assert(setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) >= 0);

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ::bind(listenfd,(struct sockaddr*)&my_addr,sizeof(my_addr));
    listen(listenfd,5);
}

Socket* Socket::get_Socket(short port  = 8888)
{
    if(Socket::sock == NULL)
    {
        Socket::sock = new Socket(port);
    }
    return Socket::sock;
}

Socket::~Socket()
{

}

void Socket::start()
{
    //assert(listen(Socket::listenfd,20) != -1);
}
