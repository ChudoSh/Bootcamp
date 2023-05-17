/*
Dev: BarSH
Rev: 
Date: 16.5.23
Status: 
*/

#include <arpa/inet.h>/*inet_ntoa*/
#include <sys/socket.h>/*sockaddr_in*/
#include <ifaddrs.h>/*ifaddrs*/
#include <string.h>/*memcmp*/
#include <time.h>/*time*/
#include <unistd.h>/*getpid*/

#include "uid.h"

#define TRUE (1)
#define FALSE (0)

const ilrd_uid_t UIDBadUID = {0};

static char *GetIP();

ilrd_uid_t UIDCreate(void)
{
	static size_t index = 1;
	
	ilrd_uid_t new_uid = {0};
	
	new_uid.pid = getpid();
	new_uid.time = time(NULL);
	new_uid.counter = index; 
	
    strcpy(new_uid.ip, GetIP());
    
    if (-1 == new_uid.ip)
    {
    	return (UIDBadUID);
    }
    
    ++(index);
     
    return (new_uid);	
}

int UIDIsSame(ilrd_uid_t id1, ilrd_uid_t id2)
{
	if (0 == memcmp(&id1, &id2, sizeof(ilrd_uid_t)))
	{
		return (TRUE);
	}
	
	return (FALSE);
}

static char *GetIP()
{
	struct ifaddrs *ifap = NULL;
	struct sockaddr_in *sa;
	char *addr;

    getifaddrs (&ifap);
   
    sa = (struct sockaddr_in *)ifap->ifa_addr;
    addr = inet_ntoa(sa->sin_addr);

    freeifaddrs(ifap);
    
    return (addr);
}
