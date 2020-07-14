CFLAGS=-lpthread -g

all:server main

main:./bin/XEpoll.o ./bin/XTcp.o ./src/main.cpp 
	g++ $^ -o $@ -g

server:./bin/XTcp.o ./bin/XHttpServer.o ./bin/XHttpClient.o  ./bin/XEpoll.o ./bin/XThreadPool.o ./bin/XHttpResponse.o ./src/server.cpp
	g++ $^ -o $@ $(CFLAGS)

./bin/XHttpServer.o:./bin/XTcp.o ./bin/XHttpClient.o  ./bin/XEpoll.o  ./bin/XThreadPool.o ./src/XHttpServer.cpp
	g++ $^ -c $(CFLAGS)
	mv XHttpServer.o ./bin

./bin/XHttpClient.o:./bin/XTcp.o ./bin/XHttpResponse.o ./src/XHttpClient.cpp
	@echo "hello"
	g++ $^ -c $(CFLAGS)
	mv XHttpClient.o ./bin

./bin/XTcp.o: ./src/XTcp.cpp
	g++   $^  -c 
	mv XTcp.o ./bin

./bin/XHttpResponse.o:./src/XHttpResponse.cpp
	g++ $^ -c 
	mv XHttpResponse.o ./bin

./bin/XEpoll.o:./src/XEpoll.cpp
	g++ $^ -c
	mv XEpoll.o ./bin

./bin/XThreadPool.o:./src/XThreadPool.cpp
	g++ $^ -c 
	mv XThreadPool.o ./bin
clean:
	rm ./bin/* server main