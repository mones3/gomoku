CC = gcc
CFLAGS = -Wall -std=c99 -g

all: gomoku renju	replay

gomoku:	board.o game.o io.o
gomoku.o: gomoku.c	board.h	game.h	io.h
board.o:	board.h
game.o:	game.c	game.h	io.h
io.o:	io.c	io.h

renju:	board.o game.o io.o
renju.o: renju.c	board.h	game.h	io.h
board.o:	board.h
game.o:	game.c	game.h	io.h
io.o:	io.c	io.h

replay:	board.o game.o io.o
replay.o: replay.c	board.h	game.h	io.h
board.o:	board.h
game.o:	game.c	game.h	io.h
io.o:	io.c	io.h

clean:	
	rm -f	board.o	game.o	io.o	gomoku.o	renju.o	replay.o
	rm -f	gomoku	renju	replay
	rm -f	output.txt	savegame.gmk