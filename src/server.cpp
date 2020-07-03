#include<sys/socket.h>
#include"../include/XTcp.h"
#include<string.h>
#include<stdio.h>
#include<thread>
#include<sys/epoll.h>
class TCPThread{
	XTcp client;
public:
	TCPThread(XTcp _client):client(_client){}
	void main(){
		for(;;){
			char buff[1024];
			int recvlen=client.recv(buff,sizeof(buff)-1);
			if(recvlen<=0)break;
			if(buff[0]=='q'&&buff[1]=='u'&&buff[2]=='i'&&buff[3]=='t'){
				char *re="quit success.\n";
				client.send(re,sizeof(re));
				break;
			}
			buff[recvlen]=0;
			printf("%s",buff);
			client.send("ok\n",4);
		}
		client.close();
		delete this;
	}
};
int main(int argc,char **argv){
	unsigned short port=8080;
	if(argc>1){
		port=atoi(argv[1]);
	}
	XTcp server;
	if(!server.bind(port)){
		exit(-1);
	}

	int epfd=epoll_create(256);

	epoll_event ev;
	ev.data.fd=server.sockfd;
	ev.events=EPOLLIN|EPOLLET;
	epoll_ctl(epfd,EPOLL_CTL_ADD,server.sockfd,&ev);

	epoll_event events[20];
	char buf[1024]={0};
	const char* msg="HTTP/1.1 200 OK\r\nContent-Length: 10\r\n\r\nhelloworld";
	server.setBlock(false);
	for(;;){
		int count=epoll_wait(epfd,events,20,500);
		if(count<=0)continue;
		for(int i=0;i<count;i++){
			if(events[i].data.fd==server.sockfd){
				for(;;){
					XTcp client=server.accept();
					if(client.sockfd<=0)break;
					ev.data.fd=client.sockfd;
					ev.events=EPOLLIN|EPOLLET;
					epoll_ctl(epfd,EPOLL_CTL_ADD,client.sockfd,&ev);
				}
			}else{
				XTcp client;
				client.sockfd=events[i].data.fd;
				client.recv(buf,1024);
				client.send(msg,strlen(msg));
				epoll_ctl(epfd,EPOLL_CTL_DEL,client.sockfd,&ev);
				client.close();
			}
		}
		/*XTcp client=sever.accept();
		TCPThread *th=new TCPThread(client);
		std::thread sth(&TCPThread::main,th);
		sth.detach();*/
	}
	server.close();
}