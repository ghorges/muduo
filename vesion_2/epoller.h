#ifndef EPOLLER_H
#define EPOLLER_H

#include "poller.h"
#include <memory>
#include <map>
#include <sys/epoll.h>
#include <assert.h>
#include <vector>
#include <list>
#include <errno.h>
#include <poll.h>
#include <iostream>
class channel;

class epoller : public poller{
public:
    //这个是typedef　shared_ptr
    typedef std::shared_ptr<channel> all_channel;

    epoller();
    ~epoller();

    int add(int fd,int event);
    int del(int fd);
    int mod(int fd,int event);
    void insert(std::pair<int,all_channel>/*&&*/t){channel_list.insert(t);}
    int delete_channel(int fd)
    {
        if(channel_list.find(fd) == channel_list.end())
        {
            return -1;
        }
        channel_list.erase(channel_list.find(fd));
        del(fd);
        return 0;
    }

    int poll(int time,std::list<all_channel>& active_channel);
private:
    //这个是用map将channel和fd关联起来
    std::map<int,all_channel> channel_list;
    std::vector<struct epoll_event> event;
    int epfd_;
};

#endif // EPOLLER_H
