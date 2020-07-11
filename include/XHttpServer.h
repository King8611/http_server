#ifndef XHTTPSERVER_H
#define XHTTPSERBER_H
#include"XTcp.h"
class XHttpServer{
public:
        XHttpServer();
        ~XHttpServer();
        bool start(unsigned short port);
        void stop();
        void main();
        XTcp server;
        bool isexit=false;
};
#endif