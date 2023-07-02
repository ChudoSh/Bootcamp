/*
Rev: EtaiSh
Dev: BarSh
status: Approved
date: 2.7.23
*/

#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "bitarray.h"

typedef enum heuristic_status
{
	FALSE = 0,
	TRUE
}is_heuristic_t;

typedef enum knights_tour_status
{
	KNIGHT_TOUR_TIME_OUT = -1,
	KNIGHT_TOUR_SUCCESS = 0,
	KNIGHT_TOUR_NOT_FOUND = 1
}status_t;

/*
typedef bitarr_t board_t;
*/

/*
Description: Make the knight tour in a bruteforce and 
			 heuristic way depending on the enum value.
Arguments: 
	column 	       - Coulmn on the bit map.
	row 		   - Row on the bit map.
	timeout_in_sec - Amount of time the program has to get result before timeout in seconds.
	status         - Clarify in what method the knight tour will be made.
	*path 		   - Array of the path made.
Return: KNIGHT_TOUR_SUCCESS(0) if the function got and answer before 
		timeout and KNIGHT_TOUR_TIME_OUT(-1) if not.
Time complexity: O(n^2 *k). n- size of row/column. k - amount of moves.
Space complexity: O(n^2).
*/
status_t KnightsTour(unsigned char column, unsigned char row, 
					 unsigned int timeout_in_sec, is_heuristic_t status, 
					 unsigned char *path);

#endif /*__KNIGHT_H__*/