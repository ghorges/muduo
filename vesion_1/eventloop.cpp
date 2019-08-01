#include "eventloop.h"

EventLoop::EventLoop() : activelist(0),quit(false)
{
    poller_ = new epoller;

}


void EventLoop::loop()
{
    while(!quit)
    {
        int r = poller_->poll(-1,activelist);
        if(r == 0)
        {

        }
        if(r > 0)
        {
            while(!activelist.empty())
            {
                activelist.front()->handle_event();
                activelist.pop_front();
            }
        }
    }
}
