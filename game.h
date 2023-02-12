#ifndef _GAME_H
#define _GAME_H
#include "board.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define GAME_FREESTYLE 0
#define GAME_RENJU 1
#define GAME_STATE_PLAYING 0
#define GAME_STATE_FORBIDDEN 1
#define GAME_STATE_STOPPED 2
#define GAME_STATE_FINISHED 3

typedef struct {
    size_t x;
    size_t y;
    unsigned char stone;
} move;

typedef struct {
    board* board;
    unsigned char type;
    unsigned char stone;
    unsigned char state;
    unsigned char winner;
    move* moves;
    size_t moves_count;
    size_t moves_capacity;
} game;

game* game_create(size_t board_size, unsigned char game_type);
void game_delete(game* g);
bool game_update(game* g);
void game_loop(game* g);
void game_resume(game* g);
void game_replay(game* g);
bool game_place_stone(game* g, size_t x, size_t y);
#endif
