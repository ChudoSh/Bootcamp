/*
Dev: BarSH
Rev: 
Date: .6.23
Status: 
*/

#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include <string.h>/*memcpy*/
#include <stdio.h>

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

enum BOOL
{
    FALSE = 0, 
    TRUE = 1
};


enum CHILDREN
{
    LEFT, 
    RIGHT,
    NUM_OF_CHILDREN,
    CREATE,
    BLOCKED
};

enum MASKS
{
    CHAR_MASK = 0xFF,
    SUBNET_MASK = ~0 << 8
};

enum MAGIC
{
    ONE = 1,
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
/*static trie_node_t *NextAvaialableNode(trie_node_t *root, size_t distance);*/ 
static trie_node_t *SetNewIP(trie_node_t *root, 
                                       bitarr_t *requested_ip, size_t distance);
static dhcp_status_t FindAndFreeNode(trie_node_t *root, bitarr_t ip_to_find,
                                     size_t shift);

static trie_node_t *TrieNodeCreate(void);
static void TrieNodeDestroy(trie_node_t *root);

static trie_node_t *GetChild(trie_node_t *node, int child);
static void SetChild(trie_node_t *current, trie_node_t *to_set, int child);
static void SetOccupied(trie_node_t *node); 
static void SetFree(trie_node_t *node);
static int IsLeaf(trie_node_t *node);
static int GetPath(trie_node_t *root);

static trie_node_t *GetTrie(const dhcp_t *dhcp);
static size_t GetSubnetSize(const dhcp_t *dhcp);
static bitarr_t GetSubnetIp(dhcp_t *dhcp);
static int IsOccupied(trie_node_t *node);
/*static int IsValidIP(dhcp_t *dhcp, unsigned char requested_ip[BYTES_IN_IP]);*/
                                   

/*Creates DHCP*/
dhcp_t *DHCPCreate(const unsigned char subnet_ip[BYTES_IN_IP], 
                   size_t subnet_size_in_bits)
{
    dhcp_t *dhcp = NULL;

    assert(subnet_size_in_bits <= 32);

    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (NULL == dhcp)
    {
        return (NULL);
    }

    dhcp->size_subnet_ip = subnet_size_in_bits;
    StringToBit(&(dhcp->subnet_ip), subnet_ip);
    dhcp->subnet_ip >>= (INT_SIZE - GetSubnetSize(dhcp));
   
    dhcp = InitDHCP(dhcp);
    if (NULL == dhcp)
    {
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
dhcp_status_t DHCPAllocIP(dhcp_t *dhcp, const unsigned char request_ip[BYTES_IN_IP], 
                          unsigned char container_ip[BYTES_IN_IP])
{
    size_t size_of_ip = 0;
    bitarr_t bitmask = ~0;
    bitarr_t runner = 0;  

    assert(NULL != dhcp);
    assert(NULL != container_ip);
    assert(0 != DHCPCountFree(dhcp));
    /*assert(IsValidIP(dhcp, (unsigned char *)request_ip));*/
    
    size_of_ip = (INT_SIZE - GetSubnetSize(dhcp));
    bitmask >>= (GetSubnetSize(dhcp));

    if (NULL == request_ip)
    {
        if (NULL ==  SetNewIP(GetTrie(dhcp), 0, size_of_ip))
        {
            return (DHCP_FAILURE);
        }
    }

    else
    {
        StringToBit(&runner , request_ip);
        runner &= bitmask;

        if (NULL == SetNewIP(GetTrie(dhcp), &runner, size_of_ip))
        {
            return (DHCP_FAILURE);
        }

        container_ip[0] = request_ip[0];
        container_ip[1] = request_ip[1];
        container_ip[2] = request_ip[2];
        container_ip[3] = request_ip[3];
    }

    

    return (DHCP_SUCCESS);
}

/*Frees a given IP*/
dhcp_status_t DHCPFreeIP(dhcp_t *dhcp, 
                         const unsigned char ip_to_free[BYTES_IN_IP])
{
    bitarr_t find = 0; 

    assert(NULL != dhcp);
    assert(NULL != ip_to_free);

    StringToBit(&find, ip_to_free);

    return (FindAndFreeNode(GetTrie(dhcp), find, GetSubnetSize(dhcp)));    
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
    bitarr_t dummy0 = 0;
    bitarr_t dummy254 = 0;
    bitarr_t dummy255 = 0;
    unsigned char str0[BYTES_IN_IP] = {'\0'};
    unsigned char str254[BYTES_IN_IP] = {'\0'};
    unsigned char str255[BYTES_IN_IP] = {'\0'};
    unsigned char test0[BYTES_IN_IP] = {'\0'};
    unsigned char test254[BYTES_IN_IP] = {'\0'};
    unsigned char test255[BYTES_IN_IP] = {'\0'};

    assert(NULL != dhcp);

    dhcp->root = TrieNodeCreate();
    if (NULL == GetTrie(dhcp))
    {
        return (NULL);
    }

    dummy0 = GetSubnetIp(dhcp);
    dummy254 = GetSubnetIp(dhcp);
    dummy255 = GetSubnetIp(dhcp);

    dummy0 <<= (INT_SIZE - GetSubnetSize(dhcp));
    dummy254 <<= (INT_SIZE - GetSubnetSize(dhcp));
    dummy255 <<= (INT_SIZE - GetSubnetSize(dhcp));

    dummy254 |= 254;
    dummy255 |= 255;

    BitToString(dummy0, str0);
    BitToString(dummy254, str254);
    BitToString(dummy255, str255);

    if (DHCP_FAILURE == DHCPAllocIP(dhcp, str0, test0))
    {
        return (NULL);
    }

    if (DHCP_FAILURE == DHCPAllocIP(dhcp, str254, test254))
    {
        return (NULL);
    }

    if (DHCP_FAILURE == DHCPAllocIP(dhcp, str255, test255))
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

    if (IsOccupied(root))
    {
        ++(*count);
    }

    CountOccupiedNodes(GetChild(root, LEFT), count);
    CountOccupiedNodes(GetChild(root, RIGHT), count);  
}

static dhcp_status_t FindAndFreeNode(trie_node_t *root, bitarr_t ip_to_find,
                                     size_t shift)
{
    int dir = (ip_to_find & (ONE << shift));

    if (0 == shift)
    {   
        return (DHCP_SUCCESS);
    }

    else if (NULL == GetChild(root, (dir)))
    {   
        return (DHCP_DOUBLE_FREE_FAILURE);
    }

    if (DHCP_SUCCESS != FindAndFreeNode(GetChild(root, (dir)), 
                                        ip_to_find, --(shift)))
    {
        return (DHCP_DOUBLE_FREE_FAILURE);
    }

    if (!IsLeaf(root))
    {      
        SetFree(root);
    }

    else
    {
        free(root);
    }

    return (DHCP_SUCCESS); 

}

/*static trie_node_t *NextAvaialableNode(trie_node_t *root, size_t distance)
{  
    int root_path = 0;
    trie_node_t *insert = NULL;  

    assert(NULL != root);

    if (0 == distance)
    {
        SetOccupied(root);
        return (root);
    }

    root_path = GetPath(root);

    if (NULL != GetChild(root, root_path))
    {
        root = GetChild(root, root_path);
    }

    else
    {
        insert = TrieNodeCreate();
        if (NULL == insert)
        {
            return (NULL);
        }
        SetChild(root, insert, root_path);

        root = insert;      
    }
 
    NextAvaialableNode(root, --(distance));
    
    if (BLOCKED == GetPath(root))
    {
        SetOccupied(root);
    }

    return (root);
}*/

static trie_node_t *SetNewIP(trie_node_t *root, 
                                       bitarr_t *requested_ip, size_t distance)
{  
    int root_path = 0;
    trie_node_t *insert = NULL; 

    if (0 == distance)
    {
        SetOccupied(root);
        return (root);
    }

    root_path = GetPath(root);
    
    if (NULL == GetChild(root, root_path))
    {
        insert = TrieNodeCreate();
        if (NULL == insert)
        {
            return (NULL);
        }
        SetChild(root, insert, root_path);

        root = insert;
    }

    else /*if (NULL == GetChild(root, root_path))*/
    {
        root = GetChild(root, root_path);   
    }
    
    SetNewIP(root, requested_ip, --(distance));

    if (IsOccupied(GetChild(root, RIGHT)) && IsOccupied(GetChild(root, LEFT)))
    {
        SetOccupied(root);
    }

    return (root);
}

/*----------------------Translators-------------------------------------------*/
static void StringToBit(bitarr_t *bit_arr, const unsigned char ip[BYTES_IN_IP])
{
    int i = BYTES_IN_IP - 1;
    unsigned int shift = 0; 

    assert(NULL != ip);
	
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
	
    while (0 <= i)/*to copy 4 times*/
    {
    	container[i] = ((bit_arr >> shift) & CHAR_MASK); /*1111110000011110001010101*/ 

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
        SetChild(root, NULL, LEFT);
    }

    if (NULL != GetChild(root, RIGHT))
    {
        TrieNodeDestroy(GetChild(root, RIGHT));
        SetChild(root, NULL, RIGHT);
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

static bitarr_t GetSubnetIp(dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    return (dhcp->subnet_ip);
}

static int GetPath(trie_node_t *root)
{
    assert(NULL != root);

    if (!IsOccupied(GetChild(root, RIGHT)) || NULL == GetChild(root, RIGHT))
    {
        return (RIGHT);
    }
    
    else if (!IsOccupied(GetChild(root, LEFT))|| NULL == GetChild(root, LEFT))
    {
        return (LEFT);
    }

    return (BLOCKED);
}

static int IsOccupied(trie_node_t *node)
{
    if (NULL == node)
    {
        return (FALSE);
    }
    
    return (OCCUPIED == node->is_occupied);
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

static void SetFree(trie_node_t *node) 
{
    assert(NULL != node);

    node->is_occupied = FREE;
}

static int IsLeaf(trie_node_t *node)
{
    return (NULL == GetChild(node, RIGHT) && NULL == GetChild(node, LEFT));
} 

/*static int IsValidIP(dhcp_t *dhcp, unsigned char requested_ip[BYTES_IN_IP])
{
    bitarr_t check_request = 0; 

    assert(NULL != dhcp);
    assert(NULL != requested_ip);

    StringToBit(&check_request, requested_ip);

    check_request >>= INT_SIZE - GetSubnetSize(dhcp);

    return (check_request == GetSubnetIp(dhcp));
}*/

