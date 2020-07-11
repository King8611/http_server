#ifndef XHTTPRESPONSE_H
#define XHTTPRESPONSE_H
#include<string>
class XHttpResponse{
public:
    XHttpResponse();
    ~XHttpResponse();
	bool SetRequest(std::string request);
	std::string GetHead();
	int Read(char *buf, int bufsize);
private:
    FILE *fp;
    int filesize=0;
};
#endif