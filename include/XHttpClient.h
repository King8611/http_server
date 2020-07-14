#ifndef XHTTPCLIENT_H
#define XHTTPCLIENT_H
#include"XTcp.h"
#include"XHttpResponse.h"
#include"XTask.h"
class XHttpClient:public XTask{

private:
    /* data */
public:
    XHttpClient();
    virtual ~XHttpClient();
    bool start(XTcp client);
    void main();
    XTcp client;
    XHttpResponse res;

    
    virtual int run();
    virtual void SetData(void*data);
private:
    void Close();
};
#endif