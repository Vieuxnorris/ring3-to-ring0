.PHONY: all clean
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
SRC = tableau.c main.c
MKDIR = mkdir -p

all: dist/tableau.exe

clean: 
	rm -f dist/tableau.exe

dist/tableau.exe: $(SRC) tableau.h Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $(SRC) -o $@