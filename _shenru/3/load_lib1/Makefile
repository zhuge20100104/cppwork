TAR=main
WORKSPACE_DIR=.
CC:=g++
LIB_PATH =-L.

.PHONY: build clear all

build:
	$(CC) -std=c++11 $(WORKSPACE_DIR)/mydll.h $(WORKSPACE_DIR)/main.cpp -g -o $(TAR) $(LIB_PATH)

all: clear build

clear:
	rm -rf $(TAR)
