/*
Dev: BarSh
Rev: 
Date:
Status:
*/
#ifndef __ILRD_WATCHDOG__
#define __ILRD_WATCHDOG__

#include <stddef.h>
#include "scheduler_heap.h"

enum WD_STATUS
{
	FAILED_TO_CREATE_CHILD_PROCESS = -1,
    WD_SUCCESS, 
	FAILED_TO_CREATE_WATCHDOG
};

/*
Name: WDStart
Description: 
Start a watchdog to protect a section of code.
Arguments:
exe_path - path to an executable file
Return: status
Time complexity: O(1)
Space complexity: O(1)  
*/ 
int WDStart(char **path);

/*
Name: WDStop
Description: 
Stop the watchdog
Arguments:
timeout - max time to wait for graceful exit 
Return: none
Time complexity: O(1)
Space complexity: O(1)  
*/
void WDStop(size_t timeout);

#endif /*__ILRD_WATCHDOG__*/