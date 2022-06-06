TAR=main
WORKSPACE_DIR=.
CC:=g++
OPTS=-Wall -std=c++11

.PHONY: build clear all

build:
	$(CC) $(OPTS)  $(WORKSPACE_DIR)/main.cpp -g -o $(TAR)

all: clear build

clear:
	rm -rf $(TAR)
