#include<sys/socket.h>
#include"../include/XTcp.h"
#include<string.h>
#include<stdio.h>
#include<thread>
#include<sys/epoll.h>
#include<regex>
#include"../include/XHttpServer.h"
#include"../include/XHttpClient.h"
#include <signal.h>
using std::string;
int main(int argc,char **argv){
	signal(SIGPIPE,SIG_IGN);
	unsigned short port=8080;
	if(argc>1){
		port=atoi(argv[1]);
	}
	XHttpServer server;
	server.start(port);
	getchar();
	return 0;
}
