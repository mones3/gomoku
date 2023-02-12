#ifndef _IO_H_
#define _IO_H_
#include "game.h"

game* game_import(const char* path);
void game_export(game* g, bool binary, const char* path);
#endif