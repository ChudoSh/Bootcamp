/*
Dev: BarSH
Rev: 
Date: 16.5.23
Status: 
*/

#include <string.h>/*memcmp*/
#include <time.h>/*time*/
#include <unistd.h>/*getpid*/
#include <sys/types.h>/*pid_t*/



#ifndef __UID_H__
#define __UID_H__

typedef struct UID
{
	pid_t pid;
	time_t time;
	size_t counter;
	char ip[16];
	
}ilrd_uid_t;

extern const ilrd_uid_t UIDBadUID;

/***********************************************************************/
/*
Description: Creates a UID.
Arguments:
	- None.
Return: 
	Returns a UID.
Time complexity: O(1).
Space complexity: O(1).
*/
ilrd_uid_t UIDCreate(void);

/***********************************************************************/
/*
Description: Checks if two UID's are the same.
Arguments:
	- id1 : A UID.
	- id2 : A UID.
Return: 
	Returns 1 if equal, 0 otherwise.
Time complexity: O(1).
Space complexity: O(1).
*/
int UIDIsSame(ilrd_uid_t id1, ilrd_uid_t id2);

#endif /* __UID_H__ */
