/*
Rev: 
Dev: BarSh
status: 
date: .6.23
*/


#include <stdlib.h>/*malloc*/
#include <time.h>/*time_t*/
#include <assert.h>/*assert*/
#include <stdio.h>

#include "knightstour.h"

enum MAGIC
{   
    POTENTIAL_MOVES = 8,
    TILES = 64,
    CHAR_CONVERT = 48, 
    LOWER_BOUND = -1,
    UPPER_BOUND = 8
};

bitarr_t full_board = ~0U;

typedef enum STATUS
{   
    INVALID = -99,
    VALID = 0   
}move_status_t;

static status_t InitTour(int table[TILES][POTENTIAL_MOVES], int index, bitarr_t *board,
                         time_t stop_time, is_heuristic_t status, 
					     unsigned char *path);
static void InitTable(int table[TILES][POTENTIAL_MOVES]);
static int PointToIndex(unsigned char row, unsigned char column);

/******************************************************************************/
status_t KnightsTour(unsigned char column, unsigned char row, 
					 unsigned int timeout_in_sec, is_heuristic_t status, 
					 unsigned char *path)
{
    int table[TILES][POTENTIAL_MOVES] = {0};
    time_t stop_time = 0;
    bitarr_t board = 0;
    unsigned char start_pos = 0;  

    /*assert(TILES > column && LOWER_BOUND < column);
    assert(TILES > row && LOWER_BOUND < row);*/
    assert(NULL != path);

    if (0 == timeout_in_sec)
    {
        return (KNIGHT_TOUR_TIME_OUT);
    }

    stop_time = time(NULL) + timeout_in_sec;
    start_pos = column + row * POTENTIAL_MOVES;

    InitTable(table);

    return (InitTour(table, start_pos, &board, stop_time, status, path));
}
/*============================Static Functions================================*/
static void InitTable(int table[TILES][POTENTIAL_MOVES])
{
    int i = 0;
    int j = 0;
    int possible_row_moves[POTENTIAL_MOVES] =  {-2, -1, 1, 2, 2, 1, -1, -2};
    int possible_col_moves[POTENTIAL_MOVES] =  {-1, -2, -2, -1, 1 , 2, 2, 1};
    int new_row = 0;
    int new_col = 0; 

    for (i = 0; i < TILES; ++i)
    {
        for (j = 0; j < POTENTIAL_MOVES; ++j)
        {
            new_row = (i / POTENTIAL_MOVES) + possible_row_moves[j];
            new_col = (i % POTENTIAL_MOVES) + possible_col_moves[j];

            if (LOWER_BOUND < new_row  && UPPER_BOUND > new_row && 
                LOWER_BOUND < new_col && UPPER_BOUND > new_col)
            {
                table[i][j] = (new_row * POTENTIAL_MOVES) + new_col;
            }

            else
            {
                table[i][j] = INVALID;
            }
        }   
    }  
}

static status_t InitTour(int table[TILES][POTENTIAL_MOVES], int index, bitarr_t *board,
                         time_t stop_time, is_heuristic_t status, 
					     unsigned char *path)
{
    int i = 0;
    status_t brute_status = 0; 
    *board = BitArrSetOn(*board, index);
    *path = index;

    if (time(NULL) >= stop_time)
    {
        return (KNIGHT_TOUR_TIME_OUT);
    }

    if (full_board == *board)
    {
        return (KNIGHT_TOUR_SUCCESS);
    }

    for (i = 0; i < POTENTIAL_MOVES; ++i)
    {
        if (INVALID != table[index][i] && 
            !BitArrGetVal(*board, table[index][i]))
        {
            brute_status = InitTour(table, table[index][i], board, stop_time, 
                                    status, (path + 1));

            if (KNIGHT_TOUR_NOT_FOUND == brute_status)
            {
               *board = BitArrSetOff(*board, table[index][i]); 
            }
            else 
            {
                return (brute_status);
            }
        }
    }
    return (KNIGHT_TOUR_NOT_FOUND);
}

