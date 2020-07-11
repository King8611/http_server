#ifndef XTCP_H
#define XTCP_H
#include<string>
class XTcp{
public:
    XTcp();
    virtual ~XTcp();
    unsigned short port;
    bool bind(unsigned short port);
    XTcp accept();
    void close();
    int recv(char *buf,int bufsize);
    int send(const char *buf,int sendsize);
    std::string ip;
    int sockfd=0;
    int createSocket();
    bool connect(char *ip,unsigned short port,int timeoutms=1000);
    bool setBlock(bool);
};
#endif