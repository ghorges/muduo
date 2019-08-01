#include "Socket.h"
#include "eventloop.h"
#include "channel.h"
#include "main_01.hpp"
#include "buffer.h"
#include <math.h>

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

class messages
{
public:
    void onMessage(const channel& conn, buffer* buf)
    {

    }

};

int main(int argc,char* argv[])
{
    main_01(argc,argv);
    return 0;
}
