#ifndef XHTTPSERVER_H
#define XHTTPSERBER_H
#include"XTcp.h"
#include"XEpoll.h"
class XHttpServer{
public:
        XHttpServer();
        ~XHttpServer();
        bool start(unsigned short port);
        void stop();
        void main();
        XTcp server;
private:
        bool isexit=false;
        XEpoll epoll;
};
#endif