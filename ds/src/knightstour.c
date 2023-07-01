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

#include <sys/types.h> /* size_t */
#include <assert.h> /* assert */
#include <time.h> /* clock */

#include "knighttour.h"


#define MOVEMENTS (8)
#define TOTAL_TILES (64)
#define ALL_ON_64 (0xFFFFFFFFFFFFFFFF)
#define MAX_MOVES (63)
#define ILLEGAL (64)

typedef size_t (*action_t)(size_t x, size_t y);

/**********************************STATICS*************************************/

static status_t BruteForce(size_t board, size_t current_tile,  
                           unsigned char *path, size_t moves, 
                           unsigned int timeout_in_sec, clock_t start,
                           size_t movesLUT[TOTAL_TILES][MOVEMENTS]);
static status_t Warnsdorff(size_t board, size_t current_tile,  
                           unsigned char *path, size_t moves, 
                           unsigned int timeout_in_sec, clock_t start,
                           size_t movesLUT[TOTAL_TILES][MOVEMENTS]);
static void LutInit(size_t LUT[TOTAL_TILES][MOVEMENTS]);

static size_t UUR(size_t x, size_t y);
static size_t UUL(size_t x, size_t y);
static size_t DDR(size_t x, size_t y);
static size_t DDL(size_t x, size_t y);
static size_t LLU(size_t x, size_t y);
static size_t LLD(size_t x, size_t y);
static size_t RRU(size_t x, size_t y);
static size_t RRD(size_t x, size_t y);

static size_t CountAvailable(size_t board, size_t current_tile, 
                             size_t movesLUT[TOTAL_TILES][MOVEMENTS]);
static size_t FewestAvailable(size_t board, size_t current_tile, 
                              size_t movesLUT[TOTAL_TILES][MOVEMENTS]);

/******************************************************************************/

status_t KnightsTour(unsigned char column, unsigned char row, 
                     unsigned int timeout_in_sec, is_heuristic_t status, 
                     unsigned char *path)
{
    size_t board = 0;
    status_t stat = KNIGHT_TOUR_SUCCESS;
    size_t i = ((int)row * MOVEMENTS) + (int)column;
    size_t movesLUT[TOTAL_TILES][MOVEMENTS] = {0};
    clock_t start = clock();

    LutInit(movesLUT);

    assert(NULL != path);

    if(0 == timeout_in_sec)
    {
        return (KNIGHT_TOUR_TIME_OUT);
    }

    if(FALSE == status)
    {
        stat = (BruteForce(board, i, path, 0, timeout_in_sec, start, movesLUT));
    }
    else
    {
        stat = (Warnsdorff(board, i, path, 0, timeout_in_sec, start, movesLUT));
    }

    return (stat);
}

/**********************************STATICS*************************************/

static status_t BruteForce(size_t board, size_t current_tile,  
                           unsigned char *path, size_t moves, 
                           unsigned int timeout_in_sec, clock_t start,
                           size_t movesLUT[TOTAL_TILES][MOVEMENTS])
{
    size_t j = 0;
    size_t next_tile = 0;
    status_t ret = KNIGHT_TOUR_SUCCESS;
    clock_t end = clock();

    if((end - start) / CLOCKS_PER_SEC > timeout_in_sec)
    {
        return (KNIGHT_TOUR_TIME_OUT);
    }

    if(MAX_MOVES == moves)
    {
        *path = current_tile;

        return (KNIGHT_TOUR_SUCCESS);
    }

    for(j = 0; j < MOVEMENTS; ++j)
    {
        next_tile = movesLUT[current_tile][j];

        if((ILLEGAL != next_tile) && (0 == BitArrGetVal(board, next_tile)))
        {
            ret = BruteForce(BitArrSetOn(board, current_tile), next_tile, 
                             path + 1, moves + 1, timeout_in_sec, start, 
                             movesLUT);
            if(KNIGHT_TOUR_TIME_OUT == ret)
            {
                return (ret);
            }

            if(KNIGHT_TOUR_SUCCESS == ret)
            {
                *path = current_tile;
                return (KNIGHT_TOUR_SUCCESS);
            }
        }
    }

    return (KNIGHT_TOUR_NOT_FOUND);
}

/******************************************************************************/

static status_t Warnsdorff(size_t board, size_t current_tile,  
                           unsigned char *path, size_t moves, 
                           unsigned int timeout_in_sec, clock_t start,
                           size_t movesLUT[TOTAL_TILES][MOVEMENTS])
{
    size_t j = 0;
    status_t ret = KNIGHT_TOUR_SUCCESS;
    clock_t end = clock();
    size_t next = 0;

    if((end - start) / CLOCKS_PER_SEC > timeout_in_sec)
    {
        return (KNIGHT_TOUR_TIME_OUT);
    }

    if(MAX_MOVES == moves)
    {
        *(path + moves) = (unsigned char)current_tile;

        return (KNIGHT_TOUR_SUCCESS);
    }

    next = FewestAvailable(board, current_tile, movesLUT);
    if(ILLEGAL == next)
    {
        return (KNIGHT_TOUR_NOT_FOUND);
    }

    ret = Warnsdorff(BitArrSetOn(board, current_tile), next, path + 1, 
                     moves + 1, timeout_in_sec, start, movesLUT);
    if(KNIGHT_TOUR_TIME_OUT == ret)
    {
        return (ret);
    }

    if(KNIGHT_TOUR_SUCCESS == ret)
    {
        *path = current_tile;
        return (KNIGHT_TOUR_SUCCESS);
    }

    return (KNIGHT_TOUR_NOT_FOUND);
}

/******************************************************************************/

static void LutInit(size_t LUT[TOTAL_TILES][MOVEMENTS])
{
    size_t i = 0;
    size_t j = 0;
    size_t x = 0;
    size_t y = 0;
    action_t arr[MOVEMENTS] = {UUR, UUL, DDR, DDL, LLU, LLD, RRU, RRD};

    for(j = 0; j < MOVEMENTS; ++j)
    {
        for(x = 0; x < MOVEMENTS; ++x)
        {
            for(y = 0; y < MOVEMENTS; ++y)
            {
                i = x + (y * MOVEMENTS);
                LUT[i][j] = arr[j](x, y);
            }
        }
    }
}

/******************************************************************************/

static size_t UUR(size_t x, size_t y)
{
    if(((y + 2) >= MOVEMENTS) || ((x + 1) >= MOVEMENTS))
    {
        return (ILLEGAL);
    }

    return (((y + 2) * MOVEMENTS) + (x + 1));
}

static size_t UUL(size_t x, size_t y)
{
    if(((y + 2) >= MOVEMENTS) || (((int)x - 1) < 0))
    {
        return (ILLEGAL);
    }

    return (((y + 2) * MOVEMENTS) + (x - 1));
}

static size_t DDR(size_t x, size_t y)
{
    if((((int)y - 2) < 0) || ((x + 1) >= MOVEMENTS))
    {
        return (ILLEGAL);
    }

    return (((y - 2) * MOVEMENTS) + (x + 1));
}

static size_t DDL(size_t x, size_t y)
{
    if((((int)y - 2) < 0) || (((int)x - 1) < 0))
    {
        return (ILLEGAL);
    }

    return (((y - 2) * MOVEMENTS) + (x - 1));
}

static size_t LLU(size_t x, size_t y)
{
    if(((y + 1) >= MOVEMENTS) || (((int)x - 2) < 0))
    {
        return (ILLEGAL);
    }

    return (((y + 1) * MOVEMENTS) + (x - 2));
}

static size_t LLD(size_t x, size_t y)
{
    if((((int)y - 1) < 0) || (((int)x - 2) < 0))
    {
        return (ILLEGAL);
    }

    return (((y - 1) * MOVEMENTS) + (x - 2));
}

static size_t RRU(size_t x, size_t y)
{
    if(((y + 1) >= MOVEMENTS) || ((x + 2) >= MOVEMENTS))
    {
        return (ILLEGAL);
    }

    return (((y + 1) * MOVEMENTS) + (x + 2));
}

static size_t RRD(size_t x, size_t y)
{
    if((((int)y - 1) < 0) || ((x + 2) >= MOVEMENTS))
    {
        return (ILLEGAL);
    }

    return (((y - 1) * MOVEMENTS) + (x + 2));
}

/******************************************************************************/

static size_t CountAvailable(size_t board, size_t current_tile, 
                             size_t movesLUT[TOTAL_TILES][MOVEMENTS])
{
    size_t i = 0;
    size_t counter = 0;

    for(i = 0; i < MOVEMENTS; ++i)
    {
        if((ILLEGAL != movesLUT[current_tile][i]) && 
            (0 == BitArrGetVal(board, movesLUT[current_tile][i])))
        {
            ++counter;
        }
    }
    
    return (counter);
}

/******************************************************************************/

static size_t FewestAvailable(size_t board, size_t current_tile,
                              size_t movesLUT[TOTAL_TILES][MOVEMENTS])
{
    size_t i = 0;
    size_t min_val = 8;
    size_t min_index = 0;
    size_t available = 0;

    for(i = (rand() % MOVEMENTS); i < MOVEMENTS; ++i)
    {
        if((ILLEGAL != movesLUT[current_tile][i]) && 
            (0 == BitArrGetVal(board, movesLUT[current_tile][i])))
        {
            available = CountAvailable(board, movesLUT[current_tile][i], movesLUT);
            if(min_val > available)
            {
                min_val = available;
                min_index = movesLUT[current_tile][i];
            }
        }
    }

    if(0 == available)
    {
        return (ILLEGAL);
    }

    return (min_index);
}


/*enum MAGIC
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


status_t KnightsTour(unsigned char column, unsigned char row, 
					 unsigned int timeout_in_sec, is_heuristic_t status, 
					 unsigned char *path)
{
    int table[TILES][POTENTIAL_MOVES] = {0};
    time_t stop_time = 0;
    bitarr_t board = 0;
    unsigned char start_pos = 0;  

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
}*/

