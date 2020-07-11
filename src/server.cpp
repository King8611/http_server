#include<sys/socket.h>
#include"../include/XTcp.h"
#include<string.h>
#include<stdio.h>
#include<thread>
#include<sys/epoll.h>
#include<regex>
#include"../include/XHttpServer.h"
#include"../include/XHttpClient.h"
#define FILE_PATH "www"
using std::string;
class TCPThread{
	XTcp client;
public:
	TCPThread(XTcp _client):client(_client){}
	void close(){
		client.close();
		delete this;
	}
	void main(){
		char buff[2048];
		int buff_size=client.recv(buff,strlen(buff)-1);
		if(buff_size<=0){
			close();
		}
		printf("==============:recv:================\n");
		printf("%s\n",buff);
		printf("==============:end:================\n");
	
// GET / HTTP/1.1
// Host: 127.0.0.1:8080
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Sec-Fetch-Site: none
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Accept-Encoding: gzip, deflate, br
// Accept-Language: zh-CN,zh;q=0.9
		std::string str=buff;
		std::string pattern="^([A-Z]+) (.+) HTTP/1";
		std::smatch mas;
		std::regex r(pattern);
		std::regex_search(str,mas,r);
		if(mas.size()==0){
			printf("%s failed!\n",pattern.c_str());
			close();
			return ;
		}
		string type=mas[1];
		string path=mas[2];
		if(type!="GET"){
			close();
			return ;
		}
		if(path=="/"){
			path="/index.html";
		}
		path=FILE_PATH+path;
		FILE *fp=fopen(path.c_str(),"rb");
		if(fp==NULL){
			close();
			return;
		}
		//获取文件大小
		fseek(fp,0,SEEK_END);
		int filesize = ftell(fp);
		fseek(fp,0,0);
		printf("file size is %d\n",filesize);

		//回应get头
		string rmsg="HTTP/1.1 200OK\r\n";
		rmsg+="Server:XHttp\r\n";
		rmsg+="Content-Type:text/html\r\n";
		rmsg+="Content-Length: ";
		rmsg+=std::to_string(filesize);
		rmsg+="\r\n\r\n";
		int sendSize=client.send(rmsg.c_str(),rmsg.size());
		printf("sendsize=%d\n",sendSize);
		for(;;){
			int len=fread(buff,1,sizeof(buff),fp);
			if(len<=0)break;
			int re=client.send(buff,len);
			if(re<=0)break;
		}
		close();
	}
};
int main(int argc,char **argv){
	unsigned short port=8080;
	if(argc>1){
		port=atoi(argv[1]);
	}
	XHttpServer server;
	server.start(port);
	getchar();
	return 0;
}
