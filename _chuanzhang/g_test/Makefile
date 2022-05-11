TAR=main
WORKSPACE_DIR=.
CC:=g++ -std=c++11
HEADER = -I./include
LIB = -L./lib -lgtest -lpthread

.PHONY: build clear all

build:
	$(CC) $(WORKSPACE_DIR)/main.cpp $(HEADER) $(LIB)  -g -o $(TAR) 

all: clear build

clear:
	rm -rf $(TAR)
