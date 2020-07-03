#include"../include/XTcp.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv){
    XTcp client;
    client.createSocket();
    if(argc!=3){
        printf("usage:<ip><port>\n");
        exit(-1);
    }
    char *ip=argv[1];
    unsigned short port=atoi(argv[2]);

    client.setBlock(false);

    client.connect(ip,port,3000);
    client.send("helloworld!\n",12);
    char buf[1024];
    int len=client.recv(buf,1024);
    buf[len]='\0';
    printf("%s",buf);
    client.close();
}