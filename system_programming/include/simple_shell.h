/*
Dev: BarSh
Rev:
Status:
Date: 28.6.23
*/

#ifndef __SIMPLE_SHELL__
#define __SIMPLE_SHELL__

#include <sys/types.h>/*system*/
#include <unistd.h>/*system*/
#include <stdlib.h>/*fork*/
#include <string.h>/*strcmp*/
#include <stdio.h>/*scanf*/
#include <sys/types.h>/*wait*/
#include <sys/wait.h>/*wait*/


/*
Description: Create a process via fork or system
Arguments:
    - new_proc: A alid pointer to a pid_t to store the new pid if forked is used
Return:
    0 if successful, else -1
Time Complexity: 0(1)
Space Complexity: 0(1)
*/
int CreateProcess();

#endif /*__SIMPLE_SHELL__*/
