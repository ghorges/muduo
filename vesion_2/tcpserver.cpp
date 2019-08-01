#include "tcpserver.h"

tcpserver::tcpserver(EventLoop* loop,int port) : loop_(loop),acceptor_(loop,port)
{
    using namespace std::placeholders;
    acceptor_.set_conncb(std::bind(&tcpserver::newconnection,this,_1));
}

void tcpserver::newconnection(int fd)
{
    typedef std::shared_ptr<channel> Cha;
    Cha listen_cha(new channel(loop_,fd));
    listen_cha->set_nblock();
    loop_->get_poller()->insert(std::make_pair(listen_cha->getfd(),listen_cha));
    loop_->get_poller()->add(listen_cha->getfd(),EPOLLIN | EPOLLERR);

    listen_cha->set_readcb(std::bind(&channel::read_fd,listen_cha.get()));
    listen_cha->set_writecb(std::bind(&channel::send_data,listen_cha.get()));
    listen_cha->set_errcb(std::bind(&channel::error_fd,listen_cha.get()));

    listen_cha->set_connection(this->onconnection);
    listen_cha->set_onmessage(this->onmessage);

    //shared_ptr *is to do what???
    onconnection(*(listen_cha.get()));
}


//每一个你不满意的现在，都有一个你没有努力的曾经
