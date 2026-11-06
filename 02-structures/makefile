.PHONY: all clean
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
MKDIR = mkdir -p

all: dist/tableau.exe

clean: 
	rm -f dist/tableau.exe

dist/tableau.exe: tableau.c Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $< -o $@