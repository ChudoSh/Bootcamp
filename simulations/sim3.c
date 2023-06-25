
#define WORD sizeof(size_t)

void Shuffle(dvector_t playlist)
{
	size_t i = 0;
	size_t play_index = 0; 

	assert(NULL != playlist);

	i = DVectorSize(playlist);

	return (playlist);

}

int IsAligned(char *p)
{
	return (0 == (p % WORD));
}


void *memcpy(void *dest, void *src, size_t size)
{	
	char *tempdest = NULL;
	char *tempsrc = NULL; 
	
	assert(NULL != dest);
	assert(NULL != src);
	
	tempdest = (char *)dest; 
	tempsrc = (char *)src;
	
	while (WORD < size)
	{
		if (IsAligned(tempdest))
		{
			*(size_t *)tempdest = *(size_t *)tempsrc;
		
			tempdest += WORD;
			tempsrc += WORD;
			size -= WORD;
		}
		
		else
		{
			*tempdest = *(char *)tempsrc;
			
			++(tempdest);
			++(tempsrc);
			--(size);
		}	  
	}
	
	while (0 < size)
	{
		*tempdest = *(char *)tempsrc;
			
		++(tempdest);
		++(tempsrc);
		--(size);
	}
	
	return (dest); 
}


typedef Struct Node
{
	void *data; 
	node_t *next;
}node_t; 


node_t *FlipList(node_t *head)
{
	node_t *current = NULL; 
	node_t *forward = NULL;
	node_t *previous = NULL;
	
	assert(NULL != head); 
	
	current = head; 
	forward = head->next;
	
	while (NULL != current)
	{
		forward = current->next; 
		current->next = previous; 
		previous = current; 
		current = forward;	
	}

	return (previous);	
}







