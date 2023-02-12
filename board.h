#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdlib.h>
#include <stdbool.h>
#define EMPTY_INTERSECTION 0
#define BLACK_STONE 1
#define WHITE_STONE 2
#define clear() printf("\033[H\033[J")

typedef struct {
    size_t size;
    unsigned char* grid;
} board;

board* board_create(size_t size);
void board_delete(board* b);
void board_print(board* b, bool in_place);
unsigned char board_formal_coord(board* b, size_t x, size_t y, char* formal_coord);
unsigned char board_coord(board* b, const char* formal_coord, size_t* x, size_t* y);
unsigned char board_get(board* b, size_t x, size_t y);
void board_set(board* b, size_t x, size_t y, unsigned char stone);
bool board_is_full(board* b);
#endif


