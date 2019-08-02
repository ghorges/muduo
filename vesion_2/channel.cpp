#include "channel.h"

channel::channel(EventLoop* loop,int fd) :loop_(loop),fd_(fd),event_(0),write_ok(true)
{

}

void channel::handle_event()
{
    if((event_ & EPOLLHUP) && !(event_ & EPOLLIN))
    {
        loop_->get_poller()->delete_channel(fd_);
        return;
    }

    if(event_ & (EPOLLERR | POLLNVAL))
    {
        loop_->get_poller()->delete_channel(fd_);
        return;
    }

    if(event_ & (EPOLLIN | EPOLLRDHUP))
    {
        std::cout << "EPOLLIN fd = " << fd_ << std::endl;
        readcallback();
        return;
    }

    if(event_ & EPOLLOUT)
    {
        std::cout << "EPOLLOUT fd = "  << fd_ << std::endl;
        writecallback();
        return;
    }
}
///////////////////////////////////
/// channel::listen_fd　don/t use
///////////////////////////////////

void channel::listen_fd()
{
    //int accept(int s, struct sockaddr *addr, socklen_t *addrlen);
    struct sockaddr_in addr;
    socklen_t t = sizeof(addr);
    int fd = accept(fd_,(struct sockaddr*)&addr,&t);

    typedef std::shared_ptr<channel> Cha;
    Cha listen_cha(new channel(loop_,fd));
    listen_cha->set_nblock();
    loop_->get_poller()->insert(std::make_pair(listen_cha->getfd(),listen_cha));
    loop_->get_poller()->add(listen_cha->getfd(),EPOLLIN | EPOLLERR);

    listen_cha->set_readcb(std::bind(&channel::read_fd,listen_cha.get()));
    listen_cha->set_writecb(std::bind(&channel::write_fd,listen_cha.get()));
    listen_cha->set_errcb(std::bind(&channel::error_fd,listen_cha.get()));

    listen_cha->set_connection(this->onconnection);
    listen_cha->set_onmessage(this->onmessage);
}

void channel::read_fd()
{
    int t = getmessage_();
    if(t > 0)
        onmessage(*this,sendmess_);
}

//////////
/// \brief channel::write_fd no use
///
void channel::write_fd()
{
    send_data();
}

void channel::error_fd()
{
    perror("err:");
    loop_->get_poller()->delete_channel(fd_);
}


int channel::sendmessage_(std::string message,int length)
{
    if(write_ok == false)
    {
        int n = send(fd_,message.c_str(),length,0);
        if(n < 0)
        {
            perror("err:");
            return loop_->get_poller()->delete_channel(fd_);
        }
        if(n == 0)
        {
            std::cout << "close fd = " << fd_ << std::endl;
            return loop_->get_poller()->delete_channel(fd_);
        }
        if(n == length)
        {
            return 0;
        }
        if(n < length)
        {
            write_ok = 1;
            sendmess_.append(message.c_str() + length,n - length);
            loop_->get_poller()->mod(fd_,EPOLLIN | EPOLLOUT);
        }
    }
    else if(write_ok == true)
    {
        loop_->get_poller()->mod(fd_,EPOLLIN | EPOLLOUT);
        sendmess_.append(message.c_str(),length);
        //send_data();
    }
}
void channel::send_data()
{
    std::cout << "send data" << std::endl;
    int t = sendmess_.readbytes();
    int n = send(fd_,sendmess_.c_str(),t,0);
    if(n < 0)
    {
        perror("124_err:");
        loop_->get_poller()->delete_channel(fd_);
        return;
    }
    if(n == 0)
    {
        std::cout << "close fd = " << fd_ << std::endl;
        loop_->get_poller()->delete_channel(fd_);
        return;
    }
    if(n == t)
    {
        //write_ok = false;
        loop_->get_poller()->mod(fd_,EPOLLIN);
        sendmess_.set_readindex(0);
        sendmess_.set_writeindex(0);
        return;
    }
    if(n < t)
    {
        sendmess_.set_readindex(sendmess_.prependbytes() + n);
    }
}

int channel::getmessage_()
{
    int t = getmess_.readbuffer(fd_);
    if(t < 0)
    {
        perror("err143_:");
        loop_->get_poller()->delete_channel(fd_);
    }
    else if(t == 0){
        std::cout << "close fd = " << fd_ << std::endl;
        loop_->get_poller()->delete_channel(fd_);
    }
    return t;
}
