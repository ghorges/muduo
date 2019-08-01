#include "acceptor.h"

acceptor::acceptor(EventLoop* loop,int port):loop_(loop),acceptSocket(Socket::socket_fd()),
    cha(loop_,acceptSocket.get_fd())
{
    acceptSocket.setReuseAddr(true);
    acceptSocket.setReusePort(true);
    acceptSocket.setTcpNoDelay(true);

    acceptSocket.bind_fd(port);
    acceptSocket.listen_fd();

    typedef std::shared_ptr<channel> Cha;
    Cha listen_cha(new channel(loop_,acceptSocket.get_fd()));
    loop_->get_poller()->insert(std::make_pair(listen_cha->getfd(),listen_cha));
    loop_->get_poller()->add(listen_cha->getfd(),EPOLLIN | EPOLLERR);

    listen_cha->set_readcb(std::bind(&acceptor::handleread,this));
    listen_cha->set_writecb(std::bind(&channel::error_fd,listen_cha.get()));
    listen_cha->set_errcb(std::bind(&channel::error_fd,listen_cha.get()));
}

void acceptor::listen()
{
    acceptSocket.listen_fd();
}

void acceptor::handleread()
{
    int fd = acceptSocket.accept_fd();
    conncb(fd);
}
