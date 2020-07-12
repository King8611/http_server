#include"../include/XEpoll.h"
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

XEpoll::XEpoll():fdNumber(0),nReady(0){
    epollfd=::epoll_create(2048);       //epoll_create里面的参数理论无效
    if(epollfd<0){
        printf("epoll create error.\n");
    }
}
XEpoll::~XEpoll(){
    this->close();
}
int XEpoll::wait(int timeout){
    events.resize(fdNumber);
    while(true){
        nReady=epoll_wait(epollfd,&*events.begin(),fdNumber,timeout);

        if(nReady==0){
            printf("epoll_wait timeout.\n");
            return 0;
        }else if(nReady==-1){
            if(errno==EINTR){
                continue;
            }else{
                printf("epoll_wait error.\n");
                return 0;
            }
        }else{
            return nReady;
        }
    }
    return -1;
}
bool XEpoll::addfd(int fd,uint32_t events, bool ETorNot){
    bzero(&event, sizeof(event));
    event.events=events;
    if(ETorNot){
        events|=EPOLLET;
    }
    event.data.fd=fd;
    if(::epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event)<0){
        printf("epoll_add error,fd=%d..\n",fd);
        return false;
    }
    ++fdNumber;
    return true;
}
bool XEpoll::delfd(int fd){
    bzero(&event,sizeof(event));
    event.data.fd=fd;
    if(epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&event)==-1){
        printf("epoll_del error,fd=%d\n",fd);
        return false;
    }
    --fdNumber;
    return true;
}
void XEpoll::close(){
    if(isValid()){
        ::close(epollfd);
    }
}
bool XEpoll::isValid(){
    if(epollfd==-1)return false;
    return true;
}
int XEpoll::getEventOccurfd(int eventIndex) const{
    if (eventIndex > nReady){
        printf("parameter(s) error");
    }
    return events[eventIndex].data.fd;
}
uint32_t XEpoll::getEvents(int eventIndex) const{
    if (eventIndex > nReady){
        printf("parameter(s) error");
    }
    return events[eventIndex].events;
}