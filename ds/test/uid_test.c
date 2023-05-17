/*
Dev: BarSH
Rev: 
Date: 16.5.23
Status: 
*/

#include <stdio.h>


#include "uid.h"

static void PrintUID(ilrd_uid_t uid);

int main()
{
	ilrd_uid_t uid1 = UIDCreate();
	ilrd_uid_t uid2 = UIDCreate();
	
	PrintUID(uid1);
	PrintUID(uid2);
	
	
	printf("uid1 is equal to uid1? %d\n", UIDIsSame(uid1, uid1));
	printf("uid1 is equal to uid2? %d\n", UIDIsSame(uid1, uid2));
	
	return (0);
	
}

static void PrintUID(ilrd_uid_t uid)
{
	printf("This is the count of the uid: %lu \n", uid.counter);
	printf("This is the PID of the uid: %d \n", uid.pid);
	printf("This is the timestamp of the uid: %lu \n", uid.time);
	printf("This is the ip of the uid: %s \n", uid.ip);
}
