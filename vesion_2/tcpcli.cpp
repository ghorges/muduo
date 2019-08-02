#include "tcpcli.h"

tcpcli::tcpcli(EventLoop* loop,int port,std::string address) : loop_(loop),port(port),
    address(address),clisocket(Socket::socket_fd())
{

}


void tcpcli::connection()
{
    clisocket.connect_fd(port,address);

    typedef std::shared_ptr<channel> Cha;
    Cha listen_cha(new channel(loop_,clisocket.get_fd()));
    listen_cha->set_nblock();
    loop_->get_poller()->insert(std::make_pair(listen_cha->getfd(),listen_cha));
    loop_->get_poller()->add(listen_cha->getfd(),EPOLLIN | EPOLLERR);
    listen_cha->set_readcb(std::bind(&channel::read_fd,listen_cha.get()));
    listen_cha->set_writecb(std::bind(&channel::send_data,listen_cha.get()));
    listen_cha->set_errcb(std::bind(&channel::error_fd,listen_cha.get()));


    listen_cha->set_connection(this->onconnection);
    listen_cha->set_onmessage(this->onmessage);

    onconnection(*(listen_cha.get()));
}
