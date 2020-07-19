#ifndef __THREADPOOL_H
#define __THREADPOOL_H
#include<thread>
#include"XTask.h"
#include<vector>
#include"XEpoll.h"
/*
            这个线程池是我网上找的板子，
            中间几个重要的函数用的是static变量
            面向对象结构不是很好
            只能用一次
            感觉这个很蛋疼
            不过目前这个就够用了，以后迭代可以对这个进行改进
*/
struct XThread                              //线程结构体
{
    pthread_t pthread_id;           //线程id
    int isStat;                                     //线程状态：1表示正在有任务，0表示等待任务
    XThread();
    ~XThread();
    bool operator==(const XThread &obj) const;
};

//线程池实现
class XThreadPool{
public:
    XThreadPool(int threadNum=10);
    ~XThreadPool();
    int addTask(XTask *task);
    int getTaskSize();
    int stopAll();
    bool isAnyThreadBusy();
    int getTaskNum();
    void setEpoll(XEpoll *);
private:
    XEpoll *epoll;
    int createThread();
    static int moveToldle(XThread *pthread);           //线程执行任务结束，状态置为1
    static int moveToBusy(XThread *pthread);       //线程开始执行状态置位1
    static void* threadFunc(void * threadData);        // 线程回调函数
 
    static std::vector<XTask *>vecTask;                //线程列表  
    static std::vector<XThread>vecThread; 
    static bool shutdown;                                               //线程退出标志
    int threadNum;                                                //线程池中启动的线程数
    static pthread_mutex_t pthreadMutex;               //线程同步锁
    static pthread_cond_t pthreadCond;                 //线程同步条件变量
};

#endif