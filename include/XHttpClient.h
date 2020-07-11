#ifndef XHTTPCLIENT_H
#define XHTTPCLIENT_H
#include"XTcp.h"
#include"XHttpResponse.h"
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
    XHttpResponse res;
private:
    void Close();
};
#endif