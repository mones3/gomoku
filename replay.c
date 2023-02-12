/**
    @file replay.c
    @author Symone Lundy (slundy)
    An executable component containing a main function. With the help from the other components, 
    it reads and replays a saved game from a file.
    @param argc number of command-line arguments
    @param argv list of command-line arguments
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error-codes.h"
#include "board.h"
#include "game.h"
#include "io.h"

#define DEAFULT_BOARD_SIZE 15
#define STRING_LIMIT 5

int main( int argc, char *argv[] )
{ 
    size_t boardSize;
    int gameType;
    char str[STRING_LIMIT];
    char formal_Coord[STRING_LIMIT];
    move m1;

    if( argc > 2 ){
        printf("usage: ./replay <saved-match.gmk>\n");
        exit(ARGUMENT_ERR);
    }
    FILE *dest = fopen(argv[1], "r" );
    if(! dest ){
        exit(FILE_INPUT_ERR); 
    }
        fscanf(dest, "%*[^\n]\n");
       
        fscanf(dest, "%s", str);
        boardSize = atoi(str);
        
        fscanf(dest, "%s", str);
        gameType = atoi(str);
        
        fscanf(dest, "%*[^\n]\n");
        fgetc(dest);
        fscanf(dest, "%*[^\n]\n");
        fgetc(dest);

        game* g = game_create(boardSize, gameType);

    while ((*g).state == GAME_STATE_PLAYING) {
        fscanf(dest, "%s", formal_Coord);
        char c;

        fscanf(dest, "%*[^\n]\n");
        fgetc(dest);
        if ((c = fgetc(dest)) != EOF) {
            ungetc(c, dest);
            (*g).state = GAME_STATE_PLAYING;
          
        } else if ((c = fgetc(dest)) == EOF ) {
            (*g).state = GAME_STATE_STOPPED;
        }  
        
            if ((*g).moves_count % 2 == 0 ) {
                (*g).stone = BLACK_STONE;
            } else if ((*g).moves_count % 2 == 1){
                (*g).stone = WHITE_STONE;
            }
            
        board_coord((*g).board, formal_Coord, &(m1.x), &(m1.y) );
        game_place_stone(g, m1.x, m1.y);
        
        
        board_print((*g).board, true);
        game_replay(g); 

    }        
        
    printf("\n");
    fclose( dest );


    game_delete(g);
    
    
    exit(0);
}