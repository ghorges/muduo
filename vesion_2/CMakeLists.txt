cmake_minimum_required(VERSION 2.8)

project(muo)
add_executable(${PROJECT_NAME} "main.cpp"  "eventloop.h" "eventloop.cpp" "noncopyable.h" "noncopyable.cpp" "channel.h" "channel.cpp" "buffer.h" "buffer.cpp" "epoller.h" "epoller.cpp" "poller.h" "poller.cpp" "timer.h" "timer.cpp" "Socket.h" "Socket.cpp" "acceptor.h" "acceptor.cpp" "tcpserver.h" "tcpserver.cpp")

set(CMAKE_CXX_FLAGS "-g -std=c++11 -lpthread")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -lpthread -DNDEBUG -DEIGEN_MPL2_ONLY")
#set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -lpthread -DEIGEN_MPL2_ONLY")
#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O -lpthread -I/usr/include/freetype2 -DNDEBUG -DEIGEN_MPL2_ONLY")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -lpthread -I/usr/include/freetype2 -DEIGEN_MPL2_ONLY")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -ldl -DNDEBUG -DEIGEN_MPL2_ONLY")
#set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -ldl -DEIGEN_MPL2_ONLY")
#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O -ldl -I/usr/include/freetype2 -DNDEBUG -DEIGEN_MPL2_ONLY")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -ldl -I/usr/include/freetype2 -DEIGEN_MPL2_ONLY")
