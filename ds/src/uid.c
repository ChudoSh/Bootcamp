/*
Dev: BarSH
Rev: 
Date: 6.7.23
Status: 
*/

#include <ifaddrs.h>/*struct ifaddrs, getifaddrs*/
#include <arpa/inet.h>/*inet_ntoa*/
#include <string.h>/*memcmp*/
#include <time.h>/*time*/
#include <unistd.h>/*getpid*/
#include <stdatomic.h> /*atomic*/
#include <stdlib.h> /*free*/

#include "uid.h"

enum BOOL
{
	FALSE,
	TRUE
};

enum STATUS
{
	FAIL = -1,
	SUCCESS
};

const ilrd_uid_t UIDBadUID = {0};

static void GetIP(char **new_ip);

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new_uid = {0};
	static atomic_size_t counter = 0;
	char *new_ip = NULL;

	new_uid.pid = getpid();
	new_uid.time = time(NULL);
	new_uid.counter =  ++(counter);
	GetIP(&new_ip);
	
	if (NULL == new_ip)
	{
		return (UIDBadUID);
	}

    if (NULL == strcpy(new_uid.ip, new_ip))
    {
    	return (UIDBadUID);
    }
     
    return (new_uid);	
}

int UIDIsSame(ilrd_uid_t id1, ilrd_uid_t id2)
{
	return (!memcmp(&id1, &id2, sizeof(ilrd_uid_t)));
}

static void GetIP(char **new_ip)
{
	struct ifaddrs *ifap = NULL; 
	struct ifaddrs *ifa = NULL;
	struct sockaddr_in *sa = NULL;

	if(FAIL == getifaddrs(&ifap))
	{
		new_ip = NULL;
	}
		
	ifa = ifap;
	
	while (AF_INET != ifa->ifa_addr->sa_family && NULL != ifa->ifa_next)
	{
		ifa = ifa->ifa_next;		
	}
	
	sa = (struct sockaddr_in *) ifa->ifa_addr;

	*new_ip = inet_ntoa(sa->sin_addr);

	freeifaddrs(ifap);
}
