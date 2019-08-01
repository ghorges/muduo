#ifndef POLLER_H
#define POLLER_H

#include "noncopyable.h"

class poller : public noncopyable
{
public:
    poller();
    virtual int add(int fd,int event) = 0;
    virtual int del(int fd) = 0;
    virtual int mod(int fd,int event) = 0;

    //析构函数不能写=0，写了会报错。
    //因为在这里也得析构吧
    virtual ~poller(){};
};

#endif // POLLER_H
