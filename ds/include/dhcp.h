/*
Dev: BarSH
Rev: MariaP
Date: 25.6.23
Status: Approved
*/

#ifndef _ILRD_DHCP_H_
#define _ILRD_DHCP_H_

#include <stddef.h> /*size_t, NULL*/

#define BYTES_IN_IP (4)

typedef struct dhcp dhcp_t;

typedef enum dhcp_status
{
    DHCP_SUCCESS,
    DHCP_FAILURE,
    DHCP_DOUBLE_FREE_FAILURE
}dhcp_status_t;


/*===========================================================================*//*
Description: Creates dhcp_t instance.
Arguments: 
    -subnet_ip: valid char array of subnet ip.
    -subnet_size_in_bits: size of subnet ip in bits.

Return: dhcp_t pointer, or NULL if fails.

Time complexity: O(1)
Space complexity: O(1)
*/
dhcp_t *DHCPCreate (const unsigned char subnet_ip[BYTES_IN_IP], 
                    size_t subnet_size_in_bits);
/*===========================================================================*/
/*
Description: Destroys dhcp_t instance.
Arguments: 
        -dhcp: valid dhcp_t pointer.
Return: nothing

Time complexity: O(n)
Space complexity: O(1)
*/
void DHCPDestroy(dhcp_t *dhcp);
/*===========================================================================*/
/*
Description: Allocates new ip for user, if possible returns requsted ip.
Arguments: 
        -dhcp: valid dhcp pointer.
        -request_ip: ip may be NULL for no specific request.
        -container_ip: container for users new ip, if request is unavailable
                        will contain next available ip.
Return: DHCP_SUCCESS if successful or DHCP_FAILURE if fails.

Time complexity: O(log(n))
Space complexity: O(1)
*/
dhcp_status_t DHCPAllocIP(dhcp_t *dhcp, const unsigned char request_ip[BYTES_IN_IP], 
                          unsigned char container_ip[BYTES_IN_IP]);
/*===========================================================================*/
/*
Description: Frees requested ip.
Arguments: 
        -dhcp: valid dhcp pointer.
        -ip_to_free: allocated ip, for dhcp to free.
Return: DHCP_SUCCESS if successful or DHCP_DOUBLE_FREE_FAILURE if occurs.

Time complexity: O(log(n))
Space complexity: O(1)
*/
dhcp_status_t DHCPFreeIP(dhcp_t *dhcp, const unsigned char ip_to_free[BYTES_IN_IP]);
/*===========================================================================*/
/*
Description: returns amount of non allocated possible ips.
Arguments: 
        -dhcp: valid dhcp pointer.

Return: Amount of non allocated possible ips

Time complexity: O(n)
Space complexity: O(1)
*/
size_t DHCPCountFree(const dhcp_t *dhcp);


#endif /*_ILRD_DHCP_H_*/