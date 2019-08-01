#include "channel.h"

typedef std::function<void(const channel& conn, buffer* buf)> cli_callback;

cli_callback client_readcb;
cli_callback client_writecb;


channel::channel(EventLoop* loop,int fd,int event) :loop_(loop),fd_(fd),event_(0),start_event_(event),write_ok(false),sendmess_(),getmess_()
{

}

void channel::handle_event()
{
    if(event_ == EPOLLIN)
    {
        std::cout << "EPOLLIN handle_event fd = " << fd_ << std::endl;
        readcallback();
    }
    if(event_ == EPOLLOUT)
    {
        std::cout << "EPOLLout"  << std::endl;
        writecallback();
    }
    if(event_ == EPOLLERR)
    {
        std::cout << "EPOLLerr"  << std::endl;
        errcallback();
    }
}


void channel::listen_fd()
{
    //int accept(int s, struct sockaddr *addr, socklen_t *addrlen);
    struct sockaddr_in addr;
    socklen_t t = sizeof(addr);
    int fd = accept(fd_,(struct sockaddr*)&addr,&t);

    typedef std::shared_ptr<channel> Cha;
    Cha listen_cha(new channel(loop_,fd,EPOLLIN | EPOLLERR));
    listen_cha->set_nblock();
    loop_->get_poller()->insert(std::make_pair(listen_cha->getfd(),listen_cha));
    loop_->get_poller()->add(listen_cha->getfd(),listen_cha->get_start_event());

    listen_cha->set_readcb(std::bind(&channel::getmessage_,listen_cha.get()));
    listen_cha->set_writecb(std::bind(&channel::getmessage_,std::ref(listen_cha)));

    std::cout << "listen_fd ok fd = " << fd << std::endl;
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
            loop_->get_poller()->mod(fd_,event_ | EPOLLOUT);
        }
    }
    else if(write_ok == true)
    {
        sendmess_.append(message.c_str(),length);

        int t = sendmess_.readbytes();
        int n = send(fd_,sendmess_.c_str(),t,0);
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
        if(n == t)
        {
            write_ok = false;
            loop_->get_poller()->mod(fd_,event_ &~ EPOLLOUT);
            sendmess_.set_readindex(0);
            sendmess_.set_writeindex(0);
            return 0;
        }
        if(n < t)
        {
            sendmess_.set_readindex(sendmess_.prependbytes() + n);
        }
    }
}

int channel::getmessage_()
{
    int t = getmess_.readbuffer(fd_);
    if(t < 0)
    {
        perror("err:");
        return loop_->get_poller()->delete_channel(fd_);
    }
    else if(t == 0){
        std::cout << "close fd = " << fd_ << std::endl;
        return loop_->get_poller()->delete_channel(fd_);
    }
    std::cout << getmess_.c_str() << std::endl;
    sendmessage_("1234567890123456",11);
}
