#include "Socket.h"
#include "eventloop.h"
#include "channel.h"
#include <math.h>
#include <iostream>

int main_01(int argc,char** argv)
{
    using namespace std;
    int port;
    if(argc == 1)
    {
        port = 8888;
    }
    else
    {
        port = atoi(argv[1]);
    }

    EventLoop p;
    Socket* Lsock;
    Lsock = Socket::get_Socket(8888);

    typedef shared_ptr<channel> Cha;
    //explicit
    Cha listen_cha(new channel(&p,Lsock->get_fd(),EPOLLIN | EPOLLOUT | EPOLLERR));

    //这里拒绝隐式类型转换
    //Cha listen_cha = new channel(Lsock->get_fd(),EPOLLIN | EPOLLOUT | EPOLLERR);
    listen_cha->set_nblock();
    listen_cha->set_readcb(std::bind(&channel::listen_fd,listen_cha.get()));
    listen_cha->set_writecb(std::bind(&channel::error_fd,listen_cha.get()));
    p.get_poller()->insert(std::make_pair(listen_cha->getfd(),listen_cha));
    p.get_poller()->add(listen_cha->getfd(),listen_cha->get_start_event());
    Lsock->start();

    p.loop();

    return 0;
}
