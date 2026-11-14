.PHONY: all clean
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
SRC_ARRAY = array.c main_array.c
SRC_LIST = list.c main_list.c
MKDIR = mkdir -p

all: dist/array.exe dist/list.exe

clean:
	rm -f dist/array.exe dist/list.exe

dist/array.exe: $(SRC_ARRAY) array.h Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $(SRC_ARRAY) -o $@

dist/list.exe: $(SRC_LIST) list.h Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $(SRC_LIST) -o $@