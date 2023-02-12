/**
    @file io.c
    @author Symone Lundy (slundy)
    This component will provide functions to import and export a game save file
*/
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "game.h"
#include "io.h"
#include "error-codes.h"

#define STRING_LIMIT 20
#define DEAFULT_BOARD_SIZE 19

/**
    This function imports a saved game from the file at path, and returns the reconstructed game struct.
    If the file doesn't exist, can't be read, or it's not following the format specified, 
    the program will exit with the code FILE_INPUT_ERR.
    @param path the path of the file containing the game to be imported
    @return returns the game struct from the file saved.
*/
game* game_import(const char* path)
{
 
    game* g = game_create(DEAFULT_BOARD_SIZE, GAME_FREESTYLE);
  
    //remove magic number
    char formal_Coord[STRING_LIMIT];
    unsigned char resultCode;
    size_t x;
    size_t y;

    FILE *dest = fopen(path, "r" );
        if( !dest ){
            exit(FILE_INPUT_ERR);
        } else { 
            //game* g = game_create(, GAME_FREESTYLE); 
            int ch;
            while ((ch = fgetc( dest ) ) != EOF){
               
                ungetc(ch, dest );
                fscanf( dest, "%s", formal_Coord);
                resultCode = board_coord((*g).board, formal_Coord, &x, &y );
                if (resultCode != FORMAL_COORDINATE_ERR) {
                    //printf("%d", resultCode);
                    game_place_stone(g, x, y);
                    board_print((*g).board, true);
                    } else {
                        exit(FILE_INPUT_ERR);
                    }   
            }
        }
    fclose( dest );
    return g;
}

/**
    This function exports a game to the file at path.
    If the file can't be written, the program will exit with the code  FILE_OUTPUT_ERR.
    @param g game to be exported
    @param path the path of the file to be exported
*/
void game_export(game* g, bool binary, const char* path)
{
if (binary == false) {
    FILE *dest;
    dest = fopen(path, "w" );
    if( dest ){
        fprintf(dest, "GA\n");
        fprintf(dest, "%zd\n", g -> board -> size);
        fprintf(dest, "%d\n", (*g).type);
        fprintf(dest, "%d\n", (*g).state);
        fprintf(dest, "%d\n", (*g).winner);

        for (int i = 0; i < (*g).moves_count; i++){
            char x = (*g).moves[i].x;
            fprintf(dest, "%c", x);
            fprintf(dest, "%zd", (*g).moves[i].y);
            fprintf(dest, "\n");
        }
           
    } else {

        exit(FILE_INPUT_ERR);
    }
        fclose( dest );

        exit(0);
    }
}