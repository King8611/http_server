#include"../include/XHttpServer.h"
#include"../include/XHttpClient.h"
#include"../include/XTask.h"
#include<thread>
XHttpServer::XHttpServer(){}
XHttpServer::~XHttpServer(){}
bool XHttpServer::start(unsigned short port){
    server.createSocket();
    if(!server.bind(port)){
        return false;
    }
    threadPool.setEpoll(&epoll);
    std::thread sth(&XHttpServer::main,this);
    sth.detach();
    return true;
}
void XHttpServer::stop(){
    isexit=true;
}
void XHttpServer::main(){
    epoll.addXTcp(server);
    while(!isexit){    
        run();
    }
}
void XHttpServer::run(){
    int count=epoll.wait(500);
    for(int i=0;i<count;i++){
        XTcp xtcp=epoll.getEventOccurXTcp(i);
        handle(xtcp);
    }
}
void XHttpServer::handle(XTcp xtcp){
    if(xtcp.sockfd==server.sockfd){
        XTcp client=xtcp.accept();
        epoll.addXTcp(client);
    }else{
        XHttpClient *client=new XHttpClient(xtcp);
        threadPool.addTask(client);
    }
}