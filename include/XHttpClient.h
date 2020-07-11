#ifndef XHTTPCLIENT_H
#define XHTTPCLIENT_H
#include"XTcp.h"
class XHttpClient
{
private:
    /* data */
public:
    XHttpClient();
    ~XHttpClient();
    bool start(XTcp client);
    void main();
    XTcp client;
};
#endif