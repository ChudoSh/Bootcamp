/*
Dev: BarSH
Rev: MariaP
Date: 25.6.23
Status: Approved
*/

#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include <string.h>/*memcpy*/

#include "dhcp.h"

typedef enum NODE_STATUS
{
    FREE, 
    OCCUPIED 
}node_status_t;

enum STATUS
{
    FAIL = -1, 
    SUCCESS = 0
};

enum CHILDREN
{
    LEFT, 
    RIGHT,
    NUM_OF_CHILDREN,
    BLOCKED
};

enum MASKS
{
    ZERO = 0U,
    ONE = 1U,
    CHAR_MASK = 0xFF
};

enum MAGIC
{ 
    CHAR_SIZE = 8,
    INT_SIZE = 32
};

typedef struct NODE_TRIE trie_node_t;
typedef unsigned int bitarr_t;

struct NODE_TRIE
{
    trie_node_t *children[NUM_OF_CHILDREN];
    node_status_t is_occupied;
};

struct dhcp
{
    trie_node_t *root;
    size_t size_subnet_ip;
    bitarr_t subnet_ip;
};

static dhcp_t *InitDHCP(dhcp_t *dhcp);

static void BitToString(bitarr_t bit_arr,
                                  unsigned char container[BYTES_IN_IP]);
static void StringToBit(bitarr_t *bit_arr, 
                            const unsigned char ip[BYTES_IN_IP]);

static void CountOccupiedNodes(trie_node_t *root, size_t *count);
static int SetRequestedIP(trie_node_t *root, bitarr_t *requested_ip, 
                                    size_t distance);
static int SetAvailableIP(trie_node_t *root, bitarr_t *new_ip, 
                          size_t distance);
static dhcp_status_t FindAndFreeNode(trie_node_t *root, bitarr_t ip_to_find,
                                     size_t shift);

static trie_node_t *TrieNodeCreate(void);
static void TrieNodeDestroy(trie_node_t *root);

static trie_node_t *GetChild(trie_node_t *node, int child);
static void SetChild(trie_node_t *current, trie_node_t *to_set, int child);
static void SetOccupied(trie_node_t *node); 
static void SetFree(trie_node_t *node);
static int IsLeaf(trie_node_t *node);
static int GetPath(bitarr_t ip, size_t shit);
static void SetOccupiedTrie(trie_node_t *node);

static trie_node_t *GetTrie(const dhcp_t *dhcp);
static size_t GetSubnetSize(const dhcp_t *dhcp);
static int IsOccupied(trie_node_t *node);
                                  
/******************************************************************************/
/*Creates DHCP*/
dhcp_t *DHCPCreate(const unsigned char subnet_ip[BYTES_IN_IP], 
                   size_t subnet_size_in_bits)
{
    dhcp_t *dhcp = NULL;
    bitarr_t bitmask = ~ZERO; 

    assert(subnet_size_in_bits <= INT_SIZE);

    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (NULL == dhcp)
    {
        return (NULL);
    }

    dhcp->size_subnet_ip = subnet_size_in_bits;

    StringToBit(&(dhcp->subnet_ip), subnet_ip);
    dhcp->subnet_ip |= (bitmask << (INT_SIZE - subnet_size_in_bits));
   
    dhcp = InitDHCP(dhcp);
    if (NULL == dhcp)
    {
        DHCPDestroy(dhcp);
        return (NULL);
    }

    return (dhcp);
}

/*Destroys DHCP*/
void DHCPDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    TrieNodeDestroy(GetTrie(dhcp));

    free(dhcp);
}

/*Create a new IP address*/
dhcp_status_t DHCPAllocIP(dhcp_t *dhcp, 
                          const unsigned char request_ip[BYTES_IN_IP], 
                          unsigned char container_ip[BYTES_IN_IP])
{
    size_t size_of_ip = 0;
    bitarr_t bitmask = ~ZERO;
    bitarr_t runner = 0; 
    int status = 0; 

    assert(NULL != dhcp);
    assert(NULL != container_ip);
    assert(0 != DHCPCountFree(dhcp));
    
    size_of_ip = (INT_SIZE - GetSubnetSize(dhcp));
    StringToBit(&runner, request_ip);
    runner &= (bitmask >> GetSubnetSize(dhcp));

    status = SetRequestedIP(GetTrie(dhcp), &runner, size_of_ip);
    if (BLOCKED == status)
    {
        runner = 0; 
        status = SetAvailableIP(GetTrie(dhcp), &runner, size_of_ip);
    }

    if (FAIL == status)
    {
        return (DHCP_FAILURE);
    }

    BitToString(runner, container_ip);
    
    return (DHCP_SUCCESS);
}

/*Frees a given IP*/
dhcp_status_t DHCPFreeIP(dhcp_t *dhcp, 
                         const unsigned char ip_to_free[BYTES_IN_IP])
{
    bitarr_t find = 0; 
    bitarr_t bitmask = ~ZERO;
    size_t size_of_ip = 0;

    assert(NULL != dhcp);
    assert(NULL != ip_to_free);

    StringToBit(&find, ip_to_free);
    find &= (bitmask >> GetSubnetSize(dhcp));
    size_of_ip = (INT_SIZE - GetSubnetSize(dhcp));

    return (FindAndFreeNode(GetTrie(dhcp), find, size_of_ip));    
}

/*Counts how many IP are left to allocate*/
size_t DHCPCountFree(const dhcp_t *dhcp)
{
    size_t count = 0;
    size_t result = 0; 

    assert(NULL != dhcp);

    result |=  (ONE << (INT_SIZE - GetSubnetSize(dhcp)));

    CountOccupiedNodes(GetTrie(dhcp), &count);

    return (result - count);
}

/*==========================Static functions==================================*/

/*----------------------------Fucntional--------------------------------------*/ 

static dhcp_t *InitDHCP(dhcp_t *dhcp)
{
    unsigned char network[BYTES_IN_IP] = {'\0','\0', '\0', '\0'};
    unsigned char server[BYTES_IN_IP] = {255, 255, 255, 254};
    unsigned char broadcast[BYTES_IN_IP] = {255, 255, 255, 255};
    unsigned char dummy[BYTES_IN_IP] = {'\0','\0', '\0', '\0'};

    assert(NULL != dhcp);

    dhcp->root = TrieNodeCreate();
    if (NULL == GetTrie(dhcp))
    {
        return (NULL);
    }

    if (DHCP_FAILURE == DHCPAllocIP(dhcp, network, dummy))
    {
        return (NULL);
    }

    if (DHCP_FAILURE == DHCPAllocIP(dhcp, server, dummy))
    {
        return (NULL);
    }

    if (DHCP_FAILURE == DHCPAllocIP(dhcp, broadcast, dummy))
    {
        return (NULL);
    }

    return (dhcp);

}

static void CountOccupiedNodes(trie_node_t *root, size_t *count)
{
    assert(NULL != count);

    if (NULL == root)
    {
       return;
    }

    if (IsLeaf(root))
    {
        ++(*count);
    }

    CountOccupiedNodes(GetChild(root, LEFT), count);
    CountOccupiedNodes(GetChild(root, RIGHT), count);  
}

static dhcp_status_t FindAndFreeNode(trie_node_t *root, bitarr_t ip_to_find,
                                     size_t shift)
{
    int dir = GetPath(ip_to_find, (shift - 1));

    if (0 == shift)
    {   
        return (DHCP_SUCCESS);   
    }

    else if (NULL == GetChild(root, dir))
    {   
        return (DHCP_DOUBLE_FREE_FAILURE);
    }

    if (DHCP_DOUBLE_FREE_FAILURE == FindAndFreeNode(GetChild(root, dir), 
                                                    ip_to_find, (shift - 1)))
    {
        return (DHCP_DOUBLE_FREE_FAILURE);
    }

    if (!IsLeaf(GetChild(root, dir)))
    {      
        SetFree(root);
    }

    else
    {
        free(GetChild(root, dir));
        SetChild(root, NULL, dir);
    }

    return (DHCP_SUCCESS); 
}

static int SetAvailableIP(trie_node_t *root, bitarr_t *new_ip, 
                          size_t distance)
{  
    int status = 0; 
    int root_path = GetPath(*new_ip, (distance - 1)); 

    if (ZERO == root_path)
    {
        *new_ip |= (ONE << (distance - 1));
        status = SetRequestedIP(GetChild(root, root_path), new_ip, 
                                (distance - 1));
        SetOccupiedTrie(root);

        return (status);
    }

    else 
    {
        *new_ip &= (~ZERO << (distance - 1));

        return (BLOCKED);
    }

}

static int SetRequestedIP(trie_node_t *root, bitarr_t *requested_ip, 
                          size_t distance)
{  
    int root_path = 0;
    int status = 0;
    trie_node_t *insert = NULL; 

    if (IsOccupied(root))
    {
        return (BLOCKED);
    }

    if (0 == distance)
    {
        SetOccupied(root);
        return (SUCCESS);
    }

    root_path = GetPath(*requested_ip, (distance - 1));
    
    if (NULL == GetChild(root, root_path))
    {
        insert = TrieNodeCreate();
        if (NULL == insert)
        {
            return (FAIL);
        }
        SetChild(root, insert, root_path);

        status = SetRequestedIP(insert, requested_ip, (distance - 1));
        SetOccupiedTrie(root);

        return (status);
    }

    status =  SetRequestedIP(GetChild(root, root_path), 
                                      requested_ip, (distance - 1));
    
    if (BLOCKED == status)
    {
        status = SetAvailableIP(root, requested_ip, distance);  
    }
    SetOccupiedTrie(root);

    return (status);
}

/*----------------------Translators-------------------------------------------*/
static void StringToBit(bitarr_t *bit_arr, const unsigned char ip[BYTES_IN_IP])
{
    int i = BYTES_IN_IP - 1;
    unsigned int shift = 0; 

    if (NULL == ip)
    {
        *bit_arr = 0;
        return;
    }
	
    while (0 <= i)
    {
    	*bit_arr |= (ip[i] << shift); 

        shift += CHAR_SIZE;
        --(i);
    }
    
}

static void BitToString(bitarr_t bit_arr, unsigned char container[BYTES_IN_IP])
{  
    int i = BYTES_IN_IP - 1; 
    unsigned int shift = 0;
	
    while (0 <= i)
    {
    	container[i] = ((bit_arr >> shift) & CHAR_MASK); 
        shift += CHAR_SIZE;
        --(i);
    }
}
/*---------------------------------Trie Funcs---------------------------------*/
static trie_node_t *TrieNodeCreate(void)
{
    trie_node_t *node = NULL;

    node = (trie_node_t *)malloc(sizeof(trie_node_t));
    if (NULL == node)
    {
        return (NULL);
    }

    node->is_occupied = FREE;
    node->children[LEFT] = NULL; 
    node->children[RIGHT] = NULL;
    
    return (node);
}

static void TrieNodeDestroy(trie_node_t *root)
{
    assert(NULL != root);

    if (NULL != GetChild(root, LEFT))
    {
        TrieNodeDestroy(GetChild(root, LEFT));
    }

    if (NULL != GetChild(root, RIGHT))
    {
        TrieNodeDestroy(GetChild(root, RIGHT));
    }

    free(root);
}
/*-------------------------Getters and setters--------------------------------*/
static trie_node_t *GetChild(trie_node_t *node, int child)
{
    assert(NULL != node);
    
    return (node->children[child]);
}

static trie_node_t *GetTrie(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    return (dhcp->root);
}

static size_t GetSubnetSize(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    return (dhcp->size_subnet_ip);
}

static int GetPath(bitarr_t ip, size_t shift)
{
    return ((ip >> shift) & ONE);
}

static int IsOccupied(trie_node_t *node)
{
    if (NULL == node)
    {
        return (FREE);
    }
    
    return (node->is_occupied);
}

static void SetChild(trie_node_t *current, trie_node_t *to_set, int child)
{
    current->children[child] = to_set;
}

static void SetOccupied(trie_node_t *node) 
{
    assert(NULL != node);

    node->is_occupied = OCCUPIED;
}

static void SetOccupiedTrie(trie_node_t *node) 
{
    assert(NULL != node);

    if (IsOccupied(GetChild(node, LEFT)) && IsOccupied(GetChild(node, RIGHT)))
    {
        SetOccupied(node);
    }

}

static void SetFree(trie_node_t *node) 
{
    assert(NULL != node);

    node->is_occupied = FREE;
}

static int IsLeaf(trie_node_t *node)
{
    return (NULL == GetChild(node, RIGHT) && NULL == GetChild(node, LEFT));
} 

