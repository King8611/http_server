#ifndef XHTTPSERVER_H
#define XHTTPSERBER_H
#include"XTcp.h"
#include"XEpoll.h"
#include"XThreadPool.h"
class XHttpServer{
public:
        XHttpServer();
        ~XHttpServer();
        bool start(unsigned short port);
        void stop();
        void main();
        XTcp server;
private:
        void run();
        bool isexit=false;
        XEpoll epoll;
        XThreadPool threadPool;
        void handle(XTcp xtcp);
        
};
#endif