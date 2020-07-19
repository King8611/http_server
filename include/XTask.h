#ifndef TASK_H
#define TASK_H
#include<string.h>
#include<iostream>
#include"XTcp.h"
class XTask{
public:
    virtual int run()=0;
    virtual void SetData(void *data)=0;
    virtual ~XTask();
    XTask();
    XTcp client;
};
#endif