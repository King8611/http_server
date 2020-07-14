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
    Close();
}

int XHttpClient::run(){
    main();
    return 1;
}
void XHttpClient::SetData(void *data){
   client=*((XTcp*)data);

   /*
            为啥我用下面这个代码
            调用析构函数的时候就会失败
            但是改成上面的就没事了
            我QAQ嘤嘤嘤呜呜呜
   */
    // memcpy(&client,data,sizeof(XTcp));
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
    printf("%s.\n",buff);
    if(len<=0){
        return ;
    }
    buff[len]=0;
    if(!res.SetRequest(buff)){
        return;
    }
    std::string  head=res.GetHead();
    if(client.send(head.c_str(),head.size())<=0){
        return;
    }

    int size=sizeof(buff);
    for(;;){
        int len=res.Read(buff,size);
        if(len<0){
            return;
        }
        if(len==0)break;
        
        if(client.send(buff,len)<=0){
            return ;
        }
    }
    return;
}
void XHttpClient::Close(){
    client.close();
}