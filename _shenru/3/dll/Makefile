TAR=mydll.dll
WORKSPACE_DIR=.
CC:=g++

.PHONY: build clear all

build:
	$(CC) -std=c++11 $(WORKSPACE_DIR)/mydll.h $(WORKSPACE_DIR)/mydll.cpp  -shared -o $(TAR)

all: clear build

clear:
	rm -rf $(TAR)
