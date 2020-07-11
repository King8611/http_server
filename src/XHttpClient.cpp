#include"../include/XHttpClient.h"
#include"../include/XHttpResponse.h"
#include<thread>
#include<iostream>
using namespace std;

XHttpClient::XHttpClient()
{
}
XHttpClient::~XHttpClient()
{
}
bool XHttpClient::start(XTcp client){
    this->client=client;
    std::thread sth(&XHttpClient::main,this);
    sth.detach();
    return true;
}
void XHttpClient::main(){
    char buff[10240];
    int len=client.recv(buff,sizeof(buff));
    if(len<=0){
        Close();
        return ;
    }
    buff[len]=0;
    if(!res.SetRequest(buff)){
        Close();
        return;
    }
    std::string  head=res.GetHead();
    if(client.send(head.c_str(),head.size())<=0){
        Close();
        return;
    }

    int size=sizeof(buff);
    for(;;){
        int len=res.Read(buff,size);
        if(len<0){
            Close();
            return;
        }
        if(len==0)break;
        
        if(client.send(buff,len)<=0){
            Close();
            return ;
        }
    }
    Close();
    return;
}
void XHttpClient::Close(){
    client.close();
    delete this;
}