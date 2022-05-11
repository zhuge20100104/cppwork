TAR=main
WORKSPACE_DIR=.
CC:=g++
HEADER_PATH = -ID:/software/boost_1_74_0
LIB_PATH = -LD:/software/boost_1_74_0/stage/lib

.PHONY: build clear all

build:
	$(CC) -std=c++11 $(WORKSPACE_DIR)/lazy.hpp $(WORKSPACE_DIR)/main.cpp -g -o $(TAR) $(HEADER_PATH) $(LIB_PATH)

all: clear build

clear:
	rm -rf $(TAR)
