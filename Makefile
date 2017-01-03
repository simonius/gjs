CC = cc
CFLAGS = -Ofast

all: gjs matcat

gjs: gjs.c gjs.h
	$(CC) $(CFLAGS) -o gjs gjs.c

matcat: gjs.h binprinter.c
	$(CC) $(CFLAGS) -o matcat binprinter.c
