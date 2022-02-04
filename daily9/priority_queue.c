#include <stdlib.h>
#include <stdio.h>
#include "priority_queue.h"

struct element {
	int priority;
	int data;
};
typedef struct element Element;

struct priority_queue{
	int size;
	int capacity;
	Element** data;
};
typedef struct priority_queue Priority_queue;

//Local Functions
Element* element_init(int priority, int data)
{
	Element* pElement = (Element*)malloc(sizeof(Element));
	if(pElement != NULL)
	{
		pElement->priority = priority;
		pElement->data = data;	
	}
	return pElement;
}
void swap_elements(Element** pp1, Element** pp2)
{
	Element* temp;
        temp = *pp2;
	*pp2 = *pp1;
	*pp1 = temp;
}
void fix_up(Element** ppData, int index)
{
	int index_of_parent = (index-1)/2;
	Element** pChild =&ppData[index];
	Element** pParent =&ppData[index_of_parent];
	if((*pChild)->priority > (*pParent)->priority)
	{
		swap_elements(pChild, pParent);
		fix_up(ppData, index_of_parent);
	}
}
void fix_down(Element** ppData, int index, int size)
{
	int index_left_child = 2*index+1;
	int index_right_child = 2*index+2;
	int index_of_largest_child;
	if(index_left_child > size-1)
	{
		index_of_largest_child = -1;
	}
	else if (index_right_child > size-1) 
	{
		index_of_largest_child=index_left_child;

	}	
	else
	{
		index_of_largest_child = (ppData[index_left_child]->priority > ppData[index_right_child]->priority)?
			index_left_child:index_right_child;
	}
	if(index_of_largest_child != -1 && ppData[index]->priority < ppData[index_of_largest_child]->priority)
	{
		swap_elements(&ppData[index], &ppData[index_of_largest_child]);
		fix_down(ppData, index_of_largest_child, size);
	}

}
//Functions in Header
PRIORITY_QUEUE priority_queue_init_default(void)
{
	Priority_queue* pPriority_queue=(Priority_queue*)malloc(sizeof(Priority_queue));
	if(pPriority_queue != NULL)
	{
		pPriority_queue->size = 0;
		pPriority_queue->capacity = 8;
		pPriority_queue->data = (Element**)malloc(sizeof(Element*)*pPriority_queue->capacity);
		if(pPriority_queue->data != NULL)
		{
			for(int i=0;i<pPriority_queue->capacity;i++)
			{
				pPriority_queue->data[i]=NULL;
			}

			return (PRIORITY_QUEUE) pPriority_queue;
		}
		free(pPriority_queue);
		pPriority_queue = NULL;
	}	
	return NULL;
}
Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
	Priority_queue* pQueue = (Priority_queue*)hQueue;
	if(pQueue->size+1 > pQueue->capacity)
	{
		Element** data = (Element**)malloc(sizeof(Element*)*pQueue->capacity*2);
		if(data == NULL) return FAILURE;
		pQueue->capacity *= 2;
		for(int i=0;i<pQueue->capacity;i++)
		{
			if(i<pQueue->size) data[i]=pQueue->data[i];
			else data[i]=NULL;
		}
		free(pQueue->data);
		pQueue->data = data;
		data = NULL;
	}
	if(pQueue->data[pQueue->size] != NULL) free(pQueue->data[pQueue->size]);
      	pQueue->data[pQueue->size] = element_init(priority_level, data_item);

	fix_up(pQueue->data, pQueue->size);
	pQueue->size++;
	return SUCCESS;
}
Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	if(priority_queue_is_empty(hQueue))return FAILURE;
	Priority_queue* pQueue = (Priority_queue*)hQueue;
	pQueue->size--;
	Element* temp = pQueue->data[0];
	pQueue->data[0]=pQueue->data[pQueue->size];
	pQueue->data[pQueue->size]=temp;
	temp = NULL;
	fix_down(pQueue->data,0,pQueue->size);
	return SUCCESS;
}
int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
	Priority_queue* pQueue = (Priority_queue*)hQueue;
	if(pQueue->size >0) 
	{
		if(pStatus != NULL) *pStatus = SUCCESS;
		return pQueue->data[0]->data;
	}
	if(pStatus != NULL) *pStatus = FAILURE;
	return -99999;
}
Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{	
	Priority_queue* pQueue = (Priority_queue*)hQueue;
	if(pQueue->size >0) return FALSE;
	return TRUE;
}
void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
	int i;
	Priority_queue* pQueue = (Priority_queue*)*phQueue;
	for(i=0;i<pQueue->capacity;i++)
	{
		if(pQueue->data[i] != NULL) free(pQueue->data[i]);
	}
	free(pQueue->data);
	free(pQueue);
	*phQueue = NULL;
}
