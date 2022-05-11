TAR=main
WORKSPACE_DIR=.
CC:=g++

.PHONY: build clear all

build:
	$(CC) $(WORKSPACE_DIR)/*.*pp -g -o $(TAR)

all: clear build

clear:
	rm -rf $(TAR)
