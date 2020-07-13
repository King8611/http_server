#include"../include/XHttpServer.h"
#include"../include/XHttpClient.h"
#include<thread>
XHttpServer::XHttpServer(){}
XHttpServer::~XHttpServer(){}
bool XHttpServer::start(unsigned short port){
    server.createSocket();
    if(!server.bind(port)){
        return false;
    }
    epoll.addfd(server.sockfd);
    std::thread sth(&XHttpServer::main,this);
    sth.detach();
    return true;
}
void XHttpServer::stop(){
    isexit=true;
}
void XHttpServer::main(){
    while(!isexit){
        int count=epoll.wait(500);
        if(count<=0)continue;
        for(int i=0;i<count;i++){
            
        }
    }
}