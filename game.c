/**
    @file game.c
    @author Symone Lundy (slundy)
    This component provides functions to manage game structs. 
    Implemets the rule sets, and interacts with players.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "game.h"
#include "error-codes.h"

//Limit for string char
#define STRING_LIMIT 20

// Two-digit number used to start left padding for printing coordinates in replay function
#define LEFT_PADDED_START 10

/**
    This function creates and returns a new dynamically allocated game struct of the specified 
    type  game_type with all fields initialized. 
    @param board_size size of the board to be created
    @param game_type type of the game to be played
    @param return returns game created 
*/
game* game_create(size_t board_size, unsigned char game_type)
{
    int MOVE_ARRAY_SIZE = (board_size * board_size);
    game *g = ( game *) malloc (sizeof( game ) );

    (*g).board = board_create(board_size);
    (*g).type = game_type;
    (*g).stone = BLACK_STONE;
    (*g).state = GAME_STATE_PLAYING;
    (*g).winner = EMPTY_INTERSECTION;

    //dynamically allocated an array of move structs
    move *movesArray = (move *) malloc (MOVE_ARRAY_SIZE * sizeof( move ) );

    (*g).moves_count = 0;
    (*g).moves_capacity = (board_size * board_size);

    (*g).moves = movesArray;

    return g;
}

/**
    This function frees the memory of a dynamically allocated game struct and it's fields. 
    If g is NULL, the program exit with the code NULL_POINTER_ERR.
    @param g game to be freed
*/
void game_delete(game* g)
{
    if (g == NULL) {
        exit(NULL_POINTER_ERR);
    }
    
    //board_delete(g -> board);
    
    free(g);
    
}
   
/**
    This function controls what happens in the game at each turn. If the state of game g isn't  GAME_STATE_PLAYING, 
    the program will return false. Otherwise, the player will be prompted to enter a move, 
    if the move entered is badly-formatted or out of board boundry, 
    the player will be re-prompted until a valid one is entered; 
    if an  EOF is entered in the process, the game will be stopped. 
    For other input mishaps, the program will exit with the code INPUT_ERR. 
    @param g game to be updated
    @param return false if state of game is not  GAME_STATE_PLAYING
*/
bool game_update(game* g)
{
    bool result = true;
    bool noStone;
    char formalCoord[STRING_LIMIT];
    move m1;
    unsigned char resultCode; 
    
    //if move is on black stone
    if ((*g).state == GAME_STATE_PLAYING && ((*g).moves_count == 0 || (*g).moves_count % 2 == 0 )) {
        (*g).stone = BLACK_STONE;
   
    printf("Black stone's turn, please enter a move: ");
        //if coord is valid or "EOF value"
        if (scanf("%s", formalCoord) != EOF ) {
            
        resultCode = board_coord((*g).board, formalCoord, &(m1.x), &(m1.y) );

            while (resultCode == FORMAL_COORDINATE_ERR) {
                printf("The coordinate you entered is invalid, please try again.\n");
                printf("Black stone's turn, please enter a move: ");
                scanf("%s", formalCoord);

                resultCode = board_coord((*g).board, formalCoord, &(m1.x), &(m1.y) );
            }

            noStone = game_place_stone(g, m1.x, m1.y);

            if ( !noStone ) {
                game_update(g);
            } else {
                m1.stone = BLACK_STONE; 
            } 
        } else {
            printf("The game is stopped.");
            printf("\n");
            (*g).state = GAME_STATE_STOPPED;
            result = false;
            return result;
        }

    } else if ((*g).state == GAME_STATE_PLAYING && (*g).moves_count % 2 == 1) {
        (*g).stone = WHITE_STONE;
        printf("White stone's turn, please enter a move: ");

        if (scanf("%s", formalCoord) != EOF) {
            
        resultCode = board_coord((*g).board, formalCoord, &(m1.x), &(m1.y) );
     
            while (resultCode == FORMAL_COORDINATE_ERR) {
                printf("The coordinate you entered is invalid, please try again.\n");
                printf("White stone's turn, please enter a move: ");
                scanf("%s", formalCoord);

                resultCode = board_coord((*g).board, formalCoord, &(m1.x), &(m1.y) ); 
            }

            noStone = game_place_stone(g, m1.x, m1.y);

            if ( !noStone ) {
                printf("There is already a stone at the coordinate you entered, please try again.\n");
                game_update(g);

            } else {
                m1.stone = WHITE_STONE;
            }

        } else {
                printf("The game is stopped.");
                printf("\n");
                (*g).state = GAME_STATE_STOPPED;
                result = false;
                return result;
            }
    }

    return result;
  
}

/**
    This function controls the game loop, it prints the current board and calls  game_update(), 
    will be repeated until game_update() returns false.
    @param g game that will be analyzed
*/
void game_loop(game* g){
    board_print((*g).board, true);
   
   if (game_update(g)) {
       board_print((*g).board, true);
       game_update(g);
   }
}

/**
    This function restarts the game loop for a saved game. If the state of g is not  
    GAME_STATE_STOPPED, exit with the code RESUME_ERR. 
    Otherwise, the state of g will be set to GAME_STATE_PLAYING.
    @param g game that will be analyzed
*/
void game_resume(game* g)
{
    if (!((*g).state == GAME_STATE_STOPPED)) {
        exit(RESUME_ERR);
    } 
    (*g).state = GAME_STATE_PLAYING;
    while((*g).state == GAME_STATE_PLAYING){
        game_loop(g);
    }
 
}

/**
    This function replays a saved game. Creates a new game struct, and re-make moves saved in g, 
    pauses 1 second before making every move.
    @param g reference to game 
*/
void game_replay(game* g)
{

if((*g).state == GAME_STATE_PLAYING ){
    printf("Moves:\n");
} else {
    printf("The game is stopped.\n");
    printf("Moves:\n");

}
    if ((*g).moves_count == 1 ){
        for (int i = 0; i < (*g).moves_count; i++){
            char x = (*g).moves[i].x;
            size_t y = (*g).moves[i].y;
            printf("Black:");
                if(y < LEFT_PADDED_START) {
                    printf("%3c", x);
                } else {
                    printf("%c", x);
                }

            printf("%zd", y);  
        }
    } else {
        for (int i = 0; i < (*g).moves_count; i++){
            char x = (*g).moves[i].x;
            size_t y = (*g).moves[i].y;

            if((*g).moves[i].stone == BLACK_STONE && i == (*g).moves_count - 1) {
                printf("Black:");
                if(y < LEFT_PADDED_START) {
                    printf("%3c", x);
                } else {
                    printf("%2c", x);
                }

            printf("%zd", y);

            } else if ((*g).moves[i].stone == BLACK_STONE && i != (*g).moves_count - 1){ 
                printf("Black:");
                if(y < LEFT_PADDED_START) {
                    printf("%3c", x);
                } else {
                    printf("%2c", x);
                }

            printf("%zd", y);



              
            } else if ((*g).moves[i].stone == WHITE_STONE ) {
                 printf("  White:");
                if(y < LEFT_PADDED_START) {
                    printf("%3c", x);
                } else {
                    printf("%2c", x);
                }
                printf("%zd\n", y);
                } 
        }  

            }
        
    
    //printf("\n");
}

/**
    This function checks to see if the winning conditions or the draw condition have 
    been met based on the game type and rules, 
    if so, function returns true, else returns false.
    @param g reference to game 
    @return return returns true if winning conditions have been met, else returns false.

static bool check_conditions(game* g)
{
    //access board array 
    //check each row for stone 5 in a row
    bool isWinner;
    int countBlackStone;
    //int countWhiteStone;
    unsigned char *ptr = (*g).board -> grid;
 

    for ( int col = 0; col < (*g).board -> size; col++ ) {
        
        for ( int row = 0; row < (*g).board -> size; row++ ){
            
            if(*ptr == BLACK_STONE) {
                for(int row = row + 1; row < countBlackStone; row++) {
                while (*ptr == BLACK_STONE) {
                 countBlackStone++;
                 printf("%d", countBlackStone);
                 ptr++;
            }
    
            if (countBlackStone == 4) {
                isWinner = true;    
            }
            }
            
        }
    }
 }

return isWinner;
}
*/

/**
    This function checks if the desired intersection is already occupied, 
    if so it prompts the player and returns false; 
    checks if any of the winning conditions or the draw condition is met based on the game type and rules, 
    if so, the move will be saved the move, prompts the player, changes the game state accordingly, and return true; 
    otherwise it will proceed to save the move and return true. 
    @param g reference to game 
    @param x  horizontal coordinate pair from the board
    @param y vertical coorinate pair from the board
    @return return returns true if intersection is already occupied or if any of the winning conditions have been met.
*/
bool game_place_stone(game* g, size_t x, size_t y)
{
    bool result;
    unsigned char intersection = board_get((*g).board, x, y);
    move m1 = {x, y, (*g).stone};

    if (intersection == EMPTY_INTERSECTION ) {
        int i = (*g).moves_count;
        (*g).moves[i] = m1; 

        if ((*g).moves_count == 0 || (*g).moves_count % 2 == 0) {
            (*g).stone = BLACK_STONE;
            m1.stone = BLACK_STONE;  
                } else if ( (*g).moves_count % 2 == 1) {
                    (*g).stone = WHITE_STONE; 
                    m1.stone = WHITE_STONE;

                }
         
        board_set((*g).board, (*g).moves[i].x, (*g).moves[i].y, (*g).stone);     
        (*g).moves_count++;  
        result = true;
        
    }

    if (intersection == BLACK_STONE || intersection == WHITE_STONE ) {
        //printf("There is already a stone at the coordinate you entered, please try again.\n");
        result = false;
    }

    //bool winner;

    //winner = check_conditions(g);
    //if (winner){
        //(*g).state = GAME_STATE_FINISHED;
       // printf("Game concluded, black won.");
       // result = false;

    //}
    
    return result;
}


