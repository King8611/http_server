SH=bash
CONF_FILE=configure.sh
CC=g++
CCFLAGS=-I include -g
AR=ar
AR_FLAG=-crv
SRC_FILE=$(wildcard src/*.cpp)
OBJ_FILE:=$(subst .cpp,.o,$(SRC_FILE))
LIB_DIR=lib
LIB_FILE:=$(LIB_DIR)/libXHTTP.a
LIB_FLAG=-L lib -lXHTTP -lpthread
# EXAMPLE_FILE=client.bin server.bin
EXAMPLE_FILE=example/server.bin
.PHONY:configure example 

#
# run make configure before firstly build
# run make to generate lib file
# run make example to generate client and server binary file
# run make clean to remove all generated file
#

XHTTP:$(LIB_FILE)

$(LIB_FILE):$(OBJ_FILE)
	$(AR) $(AR_FLAG) $(LIB_FILE) $^

.cpp.o:
	$(CC) $(CC_FLAG) -c -o $@ $<

configure:$(CONF_FILE)
	$(SH) $^

example:$(EXAMPLE_FILE)

%.bin:%.cpp $(LIB_FILE)
	$(CC) $(CCFLAGS) -o $@ $< $(LIB_FLAG)
	
clean:
	rm -r $(LIB_DIR)
	rm $(OBJ_FILE)
	rm $(EXAMPLE_FILE)


