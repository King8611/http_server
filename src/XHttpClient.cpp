#include"../include/XHttpClient.h"
#include<thread>
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
    buff[len]='\0';
    printf("%s\n",buff);
    client.close();
    delete this;
}