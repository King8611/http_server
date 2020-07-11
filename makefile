CFLAGS=-lpthread -g
all:server
client:./bin/XTcp.o ./src/client.cpp
	g++ $^ -o ./bin/client

server:./bin/XTcp.o ./bin/XHttpServer.o ./bin/XHttpClient.o ./bin/XHttpResponse.o ./src/server.cpp
	g++ $^ -o ./bin/server $(CFLAGS)

./bin/XHttpServer.o:./bin/XTcp.o ./bin/XHttpClient.o ./src/XHttpServer.cpp
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

clean:
	rm ./bin/*