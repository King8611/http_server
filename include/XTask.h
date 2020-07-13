#include<string.h>
class XTask{
protected:
    void *data;
public:
    virtual int run()=0;
    virtual void SetData(const char *data)=0;
    virtual ~XTask();
}