#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main(int argc, char* argv[])
{	
	PRIORITY_QUEUE hQueue = priority_queue_init_default();
	if(hQueue == NULL)
	{
		printf("Queue not properly created\n");
		exit(1);
	}
	printf("Queue should be Empty...1?%d\n",priority_queue_is_empty(hQueue));
	for(int i=0;i<17;i++)
	{
		if(!priority_queue_insert(hQueue,i,i))
		{
			printf("Failure to Insert\n");
			exit(2);
		}
		printf("Front is %d\n",priority_queue_front(hQueue,NULL));
	}
	printf("Queue should be not be Empty...0?%d\n",priority_queue_is_empty(hQueue));
	for(int i=17;i>0;i--)
	{
		if(!priority_queue_service(hQueue))
		{
			printf("Failure to Insert\n");
			exit(2);
		}
		printf("Front is %d\n",priority_queue_front(hQueue,NULL));
	}
	printf("Queue should be Empty...1?%d\n",priority_queue_is_empty(hQueue));
	priority_queue_destroy(&hQueue);
}
