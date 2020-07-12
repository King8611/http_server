#ifndef XEPOLL_H
#define XEPOLL_H
#include<vector>
#include <sys/epoll.h>
typedef int EventType;
class XEpoll{
public:
    XEpoll();
    ~XEpoll();
    //调用epoll_wait方法，监听就绪fd
    int wait(int timeout=-1);

    //添加一个fd,默认是ET模式（边缘触发，收到数据才会触发）
    bool addfd(int fd,uint32_t events = EPOLLIN, bool ETorNot = true);

    //删除一个fd
    bool delfd(int fd);

    //关闭fd
    void close();

    //判断fd是否有效
    bool isValid();

    //返回第eventIndex个就绪fd
    int getEventOccurfd(int eventIndex) const;
    uint32_t getEvents(int eventIndex) const;
private:
    int fdNumber;
    int epollfd;
    int nReady;
    std::vector<epoll_event>events;
    epoll_event event;
};
#endif