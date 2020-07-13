#include"../include/XThreadPool.h"
#include<iostream>
#include <algorithm>
using namespace std;
bool XThreadPool::shutdown=false;
pthread_mutex_t XThreadPool::pthreadMutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t XThreadPool::pthreadCond=PTHREAD_COND_INITIALIZER;
XThreadPool::XThreadPool(int _threadNum):
threadNum(_threadNum)
{
    cout << "threadNum:" << threadNum << " threads will be created." << endl;
    createThread(); //创建线程
}
XThreadPool::~XThreadPool(){}
int XThreadPool::createThread(){
    vecThread.resize(threadNum);
    for(size_t i=0;i<threadNum;i++){
        pthread_create(&vecThread[i].pthread_id,NULL,threadFunc,&vecThread[i]);
    }
}
void* XThreadPool::threadFunc(void * threadData){
    XThread *pThread=(XThread*)threadData;
    while(1){
        //pthread_mutex_t和pthread_cond_t一起使用（锁和条件变量
        pthread_mutex_lock(&pthreadMutex);
        while(vecTask.size()==0&&!shutdown){
            pthread_cond_wait(&pthreadCond,&pthreadMutex);
        }
        if(shutdown){                                   //shutdown表示这个线程池不用了
            pthread_mutex_unlock(&pthreadMutex);
            pthread_exit(NULL);
        }
        moveToBusy(pThread);
        XTask* task=NULL;
        auto iter=vecTask.begin();
        if(iter!=vecTask.end()){
            task=*iter;
            vecTask.erase(iter);
        }
        pthread_mutex_unlock(&pthreadMutex);
        if(task){
            task->run();
        }
        moveToldle(pThread);
    }
    return (void*)0;
}
int XThreadPool::moveToldle(XThread *pthread){
   auto  iter=find(vecThread.begin(),vecThread.end(),*pthread);
    if(iter!=vecThread.end()){
        iter->isStat=0;
    }
    return 0;
}           //线程执行任务结束，状态置为1
int XThreadPool::moveToBusy(XThread *pthread){
    auto  iter=find(vecThread.begin(),vecThread.end(),*pthread);
    if(iter!=vecThread.end()){
        iter->isStat=1;
    }
    return 0;
}      //线程开始执行状态置位1

bool XThreadPool::isAnyThreadBusy(){
    for(int i=0;i<threadNum;i++){
        if(vecThread[i].isStat==1){                                         //目前这个isStat只有1和0两个状态
            return true;
        }
    }
    return false;
}

int XThreadPool::addTask(XTask *task){
    pthread_mutex_lock(&pthreadMutex);
    this->vecTask.push_back(task);
    pthread_cond_signal(&pthreadCond);
    pthread_mutex_unlock(&pthreadMutex);
}
int XThreadPool::getTaskSize(){
    return vecTask.size();
}
int XThreadPool::stopAll(){
    if(shutdown)return -1;

    //唤醒所有线程，然后让他们自动终止。
    shutdown=true;
    pthread_cond_broadcast(&pthreadCond);
    for(size_t i=0;i<vecThread.size();i++){
        pthread_join(vecThread[i].pthread_id,NULL);
    }
    vecThread.clear();
    vecTask.clear();
    
    /*
        销毁锁
    */
    pthread_mutex_destroy(&pthreadMutex);
    pthread_cond_destroy(&pthreadCond);
}
int XThreadPool::getTaskNum(){}