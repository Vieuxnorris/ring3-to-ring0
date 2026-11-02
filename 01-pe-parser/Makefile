.PHONY: all clean
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
MKDIR = mkdir -p

all: dist/hexdump.exe dist/pe.exe

clean: 
	rm -f dist/hexdump.exe dist/pe.exe

dist/hexdump.exe: hexdump.c Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $< -o $@

dist/pe.exe: pe.c Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $< -o $@