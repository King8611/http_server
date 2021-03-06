#include"../include/XTcp.h"
#include"../include/XEpoll.h"
#include<string.h>
#include<bits/stdc++.h>
using namespace std;
struct X{
    int a,b;
};
int main(int argc,char **argv){

    XEpoll epoll;
    XTcp server;
    server.createSocket();
    unsigned short port=8080;
    if(argc!=1)port=atoi(argv[1]);
    if(!server.bind(port))return 0;

    epoll.addXTcp(server);
    server.setBlock(false);
    char buf[1024];
    const char* msg="HTTP/1.1 200 OK\r\nContent-Length: 10\r\n\r\nhelloworld";
    int k=0;
    for(;;){
        int count=epoll.wait(500);      
        if(count<=0)continue;
        printf("%d,\n",count);
        for(int i=0;i<count;i++){
            if(epoll.getEventOccurXTcp(i).sockfd==server.sockfd){
                XTcp client=server.accept();
                if(client.sockfd<=0)continue;
                epoll.addXTcp(client);
            }else{
                XTcp client=epoll.getEventOccurXTcp(i);
                int len=client.recv(buf,1023);
                buf[len]=0;
                printf("%s.\n",buf);
                client.send(msg,strlen(msg));
                epoll.delXTcp(client);
                client.close();
            }
        }
    }
}