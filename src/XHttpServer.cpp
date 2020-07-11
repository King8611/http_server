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
    std::thread sth(&XHttpServer::main,this);
    sth.detach();
    return true;
}
void XHttpServer::stop(){
    isexit=true;
}
void XHttpServer::main(){
    while(!isexit){
        XTcp client=server.accept();
        if(server.sockfd<=0)continue;
		XHttpClient *th = new XHttpClient();
		th->start(client);
    }
}