#include "epoller.h"
#include "channel.h"

epoller::epoller() : channel_list(),event(10)
{
    epfd_ = epoll_create(10);
    assert(epfd_ != -1);
    std::cout << "epoller create" << "\n";
}

epoller::~epoller()
{

}

int epoller::add(int fd,int event)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    assert(epoll_ctl(epfd_,EPOLL_CTL_ADD,fd,&ev) != -1);
    //std::pair<all_channel,int>(p,p->getfd());
    //channel_list.insert();
}

int epoller::del(int fd)
{
    assert(epoll_ctl(epfd_,EPOLL_CTL_DEL,fd,0) != -1);
}

int epoller::mod(int fd,int event)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    assert(epoll_ctl(epfd_,EPOLL_CTL_MOD,fd,&ev) != -1);
}


int epoller::poll(int time,std::list<all_channel>& active_channel)
{
    int r = epoll_wait(epfd_,&event[0],event.size(),time);
    std::cout << "r = " << r << "\n";
    if(r > 0)
    {
        for(int i = 0;i < r;i++)
        {
            std::map<int,all_channel>::iterator it = channel_list.find(event[i].data.fd);
            assert(it != channel_list.end());
            it->second->set_event(event[i].events);
            active_channel.push_back(it->second);
        }
    }
    else if(r == 0)
    {

    }
    else
    {
        if(errno == EINTR)
        {
            return 0;
        }
        else
        {
            perror("epoll_wait err:");
        }
    }

    return r;
}
