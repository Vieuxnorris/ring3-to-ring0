.PHONY: all clean
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
SRC_ARRAY = array.c main_array.c
SRC_LIST = list.c main_list.c
SRC_HASH = hash.c main_hash.c
MKDIR = mkdir -p

all: dist/array.exe dist/list.exe dist/hash.exe

clean:
	rm -f dist/array.exe dist/list.exe dist/hash.exe

dist/array.exe: $(SRC_ARRAY) array.h Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $(SRC_ARRAY) -o $@

dist/list.exe: $(SRC_LIST) list.h Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $(SRC_LIST) -o $@

dist/hash.exe: $(SRC_HASH) hash.h Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $(SRC_HASH) -o $@