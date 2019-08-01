#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H


class noncopyable
{
public:
    noncopyable(){}
    ~noncopyable(){}
private:
    noncopyable(noncopyable& p){}

    noncopyable& operator=(noncopyable& p){}
};

#endif // NONCOPYABLE_H
