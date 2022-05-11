TAR=worker
WORKSPACE_DIR=.
CC:=g++

.PHONY: build clear all

build:
	$(CC)  $(WORKSPACE_DIR)/utils/* $(WORKSPACE_DIR)/main.cpp -g -o $(TAR)

all: clear build

clear:
	rm -rf $(TAR)
