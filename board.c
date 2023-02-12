/**
    @file board.c
    @author Symone Lundy (slundy)
    This component provides functions to manage board structs. 
    Implemets the board and prints board to output.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "board.h"
#include "error-codes.h"
// Two-digit number used to start left padding of the vertical header
#define LEFT_PADDED_START 10
//ACII code for the start of the horizontal header of board
#define HORIZONTAL_MARK_START 65
//represents game board of 15
#define BOARD_SIZE_FIFTEEN 15
//represents game board of 17
#define BOARD_SIZE_SEVENTEEN 17
//represents game board of 19
#define BOARD_SIZE_NINETEEN 19


/**
    This function creates a new dynamically allocated board struct, 
    initializes board.size with the parameter size, 
    initializes board.grid with a new dynamically allocated array, 
    initializes all grid intersections with EMPTY_INTERSECTION, 
    and returns the struct created. If an invalid size is given, 
    it will exit with the code BOARD_SIZE_ERR as defined in  error-codes.h.
    @param size represents the size of the board
    @return  returns the board struct created. If invalid size returns error code.
*/
board* board_create(size_t size)
{
   
    if (!(size == BOARD_SIZE_FIFTEEN || size == BOARD_SIZE_SEVENTEEN || size == BOARD_SIZE_NINETEEN)){
        exit(BOARD_SIZE_ERR);  
    } 

    //Allocated data for the board structure
    board *b1 = ( board *) malloc (sizeof( board ) );

    unsigned char (*gridArray)[size];
    gridArray = ( unsigned char (*)[size] ) malloc( size * size * sizeof( unsigned char ));
    for ( int i = 0; i < size; i++ ) {
        for ( int j = 0; j < size; j++ ){
            gridArray[i][j] = EMPTY_INTERSECTION;
           
        }
    }

    (*b1).size = size;
    
    (*b1).grid = *gridArray;
        
    return b1;
}

/**
    This function frees the memory of a dynamically allocated board struct, 
    and frees the memory of its dynamically allocated grid field.
    If the pointer b is NULL, program will exit with the 
    code NULL_POINTER_ERR.
    @param b board struct to be deleted
*/
void board_delete(board* b) {
    if (b == NULL) {
        exit(NULL_POINTER_ERR);
    }
    free(b);
    free(b -> grid);     
}


/**
    This function prints the board in the format specified. 
    If in_place is true, it clears the terminal first.
    @param b board struct to be printed
    @param in_place boolean representation of whether or not stone has been placed on board
*/
void board_print(board* b, bool in_place)
{
    //if ( in_place ){
       clear();
    //}

    unsigned char *ptr = b -> grid;
       
    int lineNumber = b -> size;
    char marks = HORIZONTAL_MARK_START;
    for ( int i = 0; i < b -> size; i++ ) {
        if(lineNumber < LEFT_PADDED_START) {
           printf("%2d ", lineNumber);
            } else {
                printf("%d ", lineNumber);
            }
        
        for ( int j = 0;  j < b -> size; j++){
            if(*ptr == EMPTY_INTERSECTION) {     
                if (j < b -> size - 1) {
                    printf("%c", '+');
                    printf("%c", '-'); 
                    } else if (j == b -> size - 1){
                        printf("%c", '+');     
                    }   

            } else if (*ptr == BLACK_STONE ) { 
                if ( j < b -> size - 1){
                    printf("\u25CF-");
                    } else if (j == b -> size - 1){
                        printf("\u25CF");
                    }
            } else if (*ptr == WHITE_STONE ) { 
                if ( j < b -> size - 1){
                    printf("\u25CB-");
                    } else if (j == b -> size - 1){
                        printf("\u25CB");
                    }
                }

            ptr++;
        }
        
        printf("\n"); 
        lineNumber--;  
        
    }
  
    for ( int k = 0; k < (b -> size) * 2; k++ ){
        if(k == 0){
           printf("   %c ", marks);
           marks++;  
        }
        
        else if(k % 2 == 0 && k != ((b -> size - 1) * 2)){
            printf("%c ", marks);
            marks++;
        }

         else if(k == ((b -> size - 1) * 2 )){
            printf("%c", marks);
            marks++;
        }

    }
    printf("\n"); 
}


/**
    This function converts the horizontal coordinate x and vertical coordinate y for a  
    board.grid to a "letter + number" formal coordinate, and stores the result in the buffer  
    formal_coord, and returns SUCCESS. If the x and y coordinates are invalid for board b, 
    returns  COORDINATE_ERR instead.  
    @param b board of coordinates to be converted 
    @param x the horizontal coordinates to be converted
    @param y the vertical coordinates to be converted
    @param formal_coord location to store results of updated grid
    @return returns the code corresponding to valid or invalid x and y coordinates
*/
unsigned char board_formal_coord(board* b, size_t x, size_t y, char* formal_coord);
/**{
    printf("%zd\n", x);
    printf("%zd\n", y);
    //printf("%s\n", formal_coord);

return SUCCESS;

}*/

/**
    This function converts a "letter + number" formal coordinate string formal_coord to the 
    horizontal and vertical coordinates for a board.grid, and stores the results in x and  y 
    that are passed by reference, and returns SUCCESS.
    If formal_coord is invalid for board b, return FORMAL_COORDINATE_ERR instead.
    @param b pass by reference to the board of coordinates to be converted
    @param x pass by refernce to the horizontal coordinates to be converted
    @param y pass by reference to the vertical coordinates to be converted
    @param formal_coord location to store results of updated grid
    @return returns the code corresponding to valid or invalid x and y coordinates
*/
unsigned char board_coord(board* b, const char* formal_coord, size_t* x, size_t* y)
{

    if ( (*b).size == BOARD_SIZE_FIFTEEN ) {
        //printf("%c\n", formal_coord); 
        *x = formal_coord[0];
        char str[25];

        for ( int i = 1; formal_coord[i]; i++)  {
            str[i - 1] = formal_coord[i];
        }

        *y = atoi(str);
        
            if (!( (*x >= 65 && *x <= 79) && (*y >= 1 && *y <= BOARD_SIZE_FIFTEEN) )) {
                return  FORMAL_COORDINATE_ERR;  
            } 
      

        } else if ( (*b).size == BOARD_SIZE_SEVENTEEN ) {
            *x = formal_coord[0];
            char str[25];

            for ( int i = 1; formal_coord[i]; i++)  {
                str[i - 1] = formal_coord[i];
            }

            *y = atoi(str);
        
            if (!( (*x >= 65 && *x <= 81) && (*y >= 1 && *y <= BOARD_SIZE_SEVENTEEN) )) {
                return  FORMAL_COORDINATE_ERR;  
            } 

        } else if ( (*b).size == BOARD_SIZE_NINETEEN ) {
            *x = formal_coord[0];
            char str[25];

            for ( int i = 1; formal_coord[i]; i++)  {
                str[i - 1] = formal_coord[i];
            }

            *y = atoi(str);
        
            if (!( (*x >= 65 && *x <= 83) && (*y >= 1 && *y <= BOARD_SIZE_NINETEEN) )) {
                return  FORMAL_COORDINATE_ERR;  
            } 

        }
    
    return SUCCESS;
}

/**
    This function returns the intersection occupation state stored in a board.grid 
    at the given horizontal and vertical coordinate pair x and y.
    @param b reference to the board
    @param x  horizontal coordinate pair from the board
    @param y vertical coorinate pair from the board
    @return returns the intersection occupation state
*/
unsigned char board_get(board* b, size_t x, size_t y)
{
    unsigned char occupationState;
    int index = ((*b).size - y) * (*b).size + (((char)x - 'A'));

    if ((*b).grid[index] == EMPTY_INTERSECTION ){
        occupationState = EMPTY_INTERSECTION;
    } else if ( (*b).grid[index] == BLACK_STONE ){
        occupationState = BLACK_STONE;
    } else if ( (*b).grid[index] == WHITE_STONE ){
        occupationState = WHITE_STONE;
    }
    
    return occupationState;

} 

/**
    This function stores the intersection occupation state stone to a board.grid at 
    the given horizontal and vertical coordinate pair x and y. 
    If stone is neither BLACK_STONE or WHITE_STONE, the program will exit with the code  
    STONE_TYPE_ERR.
    @param b reference to the board
    @param x  horizontal coordinate pair from the board
    @param y vertical coorinate pair from the board
    @param stone occupation state of the stone
*/
void board_set(board* b, size_t x, size_t y, unsigned char stone)
{
    
    int index = ((*b).size - y) * (*b).size + (((char)x - 'A'));
    
    if (!( stone == BLACK_STONE || stone == WHITE_STONE )) {
        exit(STONE_TYPE_ERR);
    }
        (*b).grid[index] = stone; 
} 


/**
    This function returns true if all intersections of a board.grid is occupied by a stone, 
    otherwise it returns false.
    @param b reference to the board
    @return true if all intersections of board contains a stone, else returns false.
*/
bool board_is_full(board* b);