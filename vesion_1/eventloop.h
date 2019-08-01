#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "noncopyable.h"
#include "epoller.h"
#include "channel.h"
#include "timer.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include <memory>
#include <list>

class epoller;
class channel;
class timer;

class EventLoop : public noncopyable
{
public:
    EventLoop();
    void loop();
    epoller* get_poller(){return poller_;}
    
private:
    typedef std::shared_ptr<channel> all_channel;
    epoller* poller_;
    std::list<all_channel> activelist;
    bool quit;
    //timer* clock_time;
};

#endif // EVENTLOOP_H
