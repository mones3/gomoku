/**
    @file renju.c
    @author Symone Lundy (slundy)
    This is a component containing a main function. With the help from 
    the other components, it interacts with the user and plays the game 
    of Renju.
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
#define MAX_ARGUMENTS 5

int main( int argc, char *argv[] )
{ 
    
    size_t size = DEAFULT_BOARD_SIZE;

    if( argc > MAX_ARGUMENTS ){
    printf("usage: %s", *argv);
        for(int i = 1; i < argc - 1; i = i + 2){
            printf(" [%s %s ", argv[i], argv[i + 1]);
            printf("]");
        }
        printf("\n -r an -b conflicts with each other\n");
        exit(ARGUMENT_ERR);
    }
    
    if( strcmp( argv[1], "-o") == 0 ){
        //add case for -r
        //then add OR statement for 
        //add case for -b
        board* b = board_create(size);
            board_print(b, false); 
            game* newGame = game_create(size, GAME_RENJU);
            game_update(newGame);
            while((*newGame).state == GAME_STATE_PLAYING){
                  game_loop(newGame);
            }

            game_export(newGame, false, argv[2]);
            game_delete(newGame);    
            
    } 

    else if( strcmp( argv[1], "-r") == 0 ) {
        game* g = game_create(DEAFULT_BOARD_SIZE, GAME_RENJU);
        g = game_import(argv[2]);
        while((*g).state == GAME_STATE_PLAYING){
            game_loop(g);
        }
         game_delete(g); 

        //add case for -o
        

    } else if( strcmp( argv[1], "-b") == 0){
         if (strcmp( argv[2], "-a") == 0) {
            printf("usage: ./gomoku [-r <unfinished-match.gmk>] [-o <saved-match.gmk>] [-b <15|17|19>]\n");
            printf("       -r an -b conflicts with each other\n");
            exit(ARGUMENT_ERR);
        }
       
            size = atoi(argv[2]);
            board* b = board_create(size);
            board_print(b, false); 
            game* newGame = game_create(size, GAME_RENJU);
            game_update(newGame);
            while((*newGame).state == GAME_STATE_PLAYING){
                  game_loop(newGame);
              } 
          
                //if (strcmp( argv[3], "-o") == 0){
                    //game_export( newGame, false, argv[4] );
                //}
            //add case for -o
           game_delete(newGame);  
       
    }   
    exit(0);  
}

