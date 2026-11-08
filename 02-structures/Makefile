.PHONY: all clean
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
SRC_TABLEAU = tableau.c main_tableau.c
SRC_LISTE = liste.c main_liste.c
MKDIR = mkdir -p

all: dist/tableau.exe dist/liste.exe

clean: 
	rm -f dist/tableau.exe dist/liste.exe

dist/tableau.exe: $(SRC_TABLEAU) tableau.h Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $(SRC_TABLEAU) -o $@

dist/liste.exe: $(SRC_LISTE) liste.h Makefile
	$(MKDIR) dist
	$(CC) $(CFLAGS) $(SRC_LISTE) -o $@