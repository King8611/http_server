#include"../include/XTcp.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>
XTcp::XTcp(){

}
XTcp::~XTcp(){
}
bool XTcp::connect(char *ip,unsigned short port,int timeoutms){
    if(sockfd<=0)createSocket();
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    setBlock(false);
    int flag=::connect(sockfd,(sockaddr *)&addr,sizeof(addr));
    fd_set set;
    if(flag!=0){
        FD_ZERO(&set);
        FD_SET(sockfd,&set);
        timeval tm;
        tm.tv_sec=0;
        tm.tv_usec=timeoutms*1000;
        if(select(sockfd+1,0,&set,0,&tm)<=0){
            printf("connect timeout or error!\n");
            printf("connect %s:%d failed:%s\n",ip,port,strerror(errno));
            return false;
        }
    }
    setBlock(true);
    printf("connect %s:%d sucess!\n",ip,port);
    return true;
}
XTcp XTcp::accept(){
    XTcp tcp;
    sockaddr_in addr;
    socklen_t len=sizeof(addr);
    int client=::accept(sockfd,(sockaddr*)&addr,&len);
    if(client<=0)return tcp;
    printf("accept client %d.\n",client);
    tcp.ip=inet_ntoa(addr.sin_addr);
    tcp.port=ntohs(addr.sin_port);
    tcp.sockfd=client;
    printf("client ip is %s,port is %d\n",tcp.ip.c_str(),tcp.port);
    return tcp;
}
void XTcp::close(){
    if (sockfd <= 0) return;
    ::close(sockfd);
}

bool XTcp::bind(unsigned short port){
    sockaddr_in addr;
    if(sockfd<=0){
        createSocket();
    }
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    printf("%d\n",port);
    addr.sin_addr.s_addr=htonl(0);
    if(::bind(sockfd,(sockaddr*)&addr,sizeof(addr))!=0){
        printf("bind port failed\n");
        return false;
    }
    printf("bind port %d sucess!\n",port);
    listen(sockfd, 10);
    return true;
}

int XTcp::recv(char *buf,int bufsize){
    return ::recv(sockfd,buf,bufsize,0);
}
int XTcp::send(const char *buf,int sendsize){
    int s=0,len=0;
    while(s!=sendsize){
        len=::send(sockfd,buf+s,sendsize-s,0);
        if(len<=0)break;
        s+=len;
    }
    return s;
}
int XTcp::createSocket(){
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("sock create error.\n");
    }
    return sockfd;
}
bool XTcp::setBlock(bool isblock){
    int flag=fcntl(sockfd,F_GETFL,0);
    if(flag<0)return false;
    if(isblock){
        flag&=~O_NONBLOCK;
    }else{
        flag|=O_NONBLOCK;
    }
    if(fcntl(sockfd,F_SETFL,flag)!=0)return false;
    return true;
}
