/*
Dev: BarSH
Rev: 
Date: 6.7.23
Status: 
*/

#include <arpa/inet.h>/*inet_ntoa*/
#include <sys/socket.h>/*sockaddr_in*/
#include <ifaddrs.h>/*ifaddrs*/
#include <string.h>/*memcmp*/
#include <time.h>/*time*/
#include <unistd.h>/*getpid*/
#include <netdb.h>
#include <sys/types.h>

#include <pthread.h> /*pthread_mutex_unlock*/



#include "uid.h"

#define ASCII (256)

enum BOOL
{
	FALSE,
	TRUE
};

const ilrd_uid_t UIDBadUID = {0};
static size_t index = 1;

static char *GetIP(void);
static size_t GetIndex(void);

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new_uid = {0};
	
	new_uid.pid = getpid();
	new_uid.time = time(NULL);
	new_uid.counter = GetIndex(); 

    while (NULL == strcpy(new_uid.ip, GetIP()));
    if (NULL == new_uid.ip)
    {
    	return (UIDBadUID);
    }
     
    return (new_uid);	
}

int UIDIsSame(ilrd_uid_t id1, ilrd_uid_t id2)
{
	return (!memcmp(&id1, &id2, sizeof(ilrd_uid_t)));
}

static char *GetIP()
{
	char hostbuffer[256] = {'\0'};
    char *IPbuffer = NULL;
    struct hostent *host_entry = NULL;
   
	gethostname(hostbuffer, sizeof(hostbuffer));
 
    host_entry = gethostbyname(hostbuffer);
 
    IPbuffer = inet_ntoa(*((struct in_addr*)
                        host_entry->h_addr_list[0]));
    
    return (IPbuffer);
}

static size_t GetIndex(void)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	size_t tmp = 0;

	pthread_mutex_lock(&mutex);
	{
		tmp = index;
		++(index);
	}
	pthread_mutex_unlock(&mutex);

	return (tmp);
}

