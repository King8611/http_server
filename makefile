CFLAGS=-lpthread
all:client server
client:./bin/XTcp.o ./src/client.cpp
	g++ $^ -o ./bin/client
server:./bin/XTcp.o ./src/server.cpp
	g++ $^ -o ./bin/server $(CFLAGS)
./bin/XTcp.o: src/XTcp.cpp
	g++   $^  -c 
	mv XTcp.o ./bin
clean:
	rm ./bin/*