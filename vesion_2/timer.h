#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <queue>


struct cmp1
{
    bool operator()(int x, int y)
    {
        return x > y;//小的优先级高
    }
};

class timer
{
public:
    timer();

private:
    std::priority_queue<int,std::vector<int>,cmp1> t;
};

#endif // TIMER_H
