/*
Dev: BarSH
Rev: 
Status: 
Date: 21.6.23
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dhcp.h"

static void AutoTest(int val, const char *func, int line);
static void CreateDestroyTest();

int main()
{
	CreateDestroyTest();
	return (0);
}

static void CreateDestroyTest()
{   
    dhcp_t *dhcp = NULL; 
    const unsigned char subnet_ip[4] = {'B','a','r', '\0'};
    const unsigned char test_ip[4] = {'B','a','r', 'S'};
    unsigned char contain_ip[4] = {'\0'};

    /*subnet_size = (subnet_ip[0] << 24) | (subnet_ip[1] << 16) | (subnet_ip[2] << 8) | subnet_ip[3];*/

    dhcp = DHCPCreate(subnet_ip, 24);

    AutoTest(252 == DHCPCountFree(dhcp),"Create",__LINE__);

    AutoTest(DHCP_SUCCESS == DHCPAllocIP(dhcp, test_ip, contain_ip), "Alloc Req", __LINE__);

    printf("%lu\n", DHCPCountFree(dhcp));
    AutoTest(251 == DHCPCountFree(dhcp),"Count",__LINE__);

    AutoTest(DHCP_SUCCESS == DHCPAllocIP(dhcp, NULL, contain_ip), "Alloc Null", __LINE__);

    printf("%lu\n", DHCPCountFree(dhcp));
    AutoTest(250 == DHCPCountFree(dhcp),"Count",__LINE__);

    DHCPDestroy(dhcp);
}



static void AutoTest(int val, const char *func, int line)
{
	char str2[47];
	char temp[17] = {'\0'};
	sprintf(temp, " %d       ", line);
	strncpy(str2, temp, strlen(temp));
	sprintf(temp, "         ");
	sprintf(temp, " %s               ", func);
	strncpy(&str2[6], temp, strlen(temp));
	
	if(val)
	{
		strcpy(&str2[23], "\033[1;32msuccess\033[0m");
	}
	else
	{
		strcpy(&str2[23], "\033[1;31mfail\033[0m");
	}
	
	printf("%s\n", str2);
}



