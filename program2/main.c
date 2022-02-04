#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

int ferry_scenario(void);
void clear_keyboard_buffer(void);

int main(int argv, char* argc[])
{
	int d,i;
	char c;
	FILE* fp = NULL;
	fp = fopen("output.txt","w");
	scanf("%d",&d);
	clear_keyboard_buffer();
	for(i=0;i<d;i++)
	{
		c=ferry_scenario();	
		printf("%d\n",c);
		fprintf(fp,"%d\n",c);
		clear_keyboard_buffer();
	}
	fclose(fp);

	return 0;
}


int  ferry_scenario(void)
{
	int l,m,i;
	int trips = 0;
	int size = 0;
	char side = 'n';
	char c;
	Status status = SUCCESS;
	QUEUE hQueue_left = NULL;
	QUEUE hQueue_right = NULL;

	scanf("%d%d",&l,&m);
	l *= 100;

	hQueue_left = queue_init_default();
	if(hQueue_left == NULL)
	{
		printf("FAILED to allocate for left\n");
		exit(1);
	}
	hQueue_right = queue_init_default();
	if(hQueue_right == NULL)
	{
		printf("FAILED to allocate for right\n");
		exit(1);
	}
	for(i=0;i<m;i++)
	{
		clear_keyboard_buffer();		
		scanf("%d",&size);	
		scanf("%c",&c);
		scanf("%c",&side);
		if(side == 'r') queue_enqueue(hQueue_right, size);
		else queue_enqueue(hQueue_left, size);	
	}
	
	while(!queue_is_empty(hQueue_left) || !queue_is_empty(hQueue_right))
	{
		i=0;
		if(!queue_is_empty(hQueue_left))while(queue_front(hQueue_left,&status)+i <= l && status != FAILURE)
		{
			i += queue_front(hQueue_left,NULL);
			queue_service(hQueue_left);
		}
		if(i>0 || !queue_is_empty(hQueue_right))
		{
			trips++;
		}
		i=0;
		if(!queue_is_empty(hQueue_right))while(queue_front(hQueue_right,&status)+i <= l && status != FAILURE)
		{
			i += queue_front(hQueue_right,NULL);
			queue_service(hQueue_right);
		}
		if(i>0 || !queue_is_empty(hQueue_left))
		{
			trips++;
		}

	}	




	queue_destroy(&hQueue_left);
	queue_destroy(&hQueue_right);
	return trips;
}

void clear_keyboard_buffer(void)
{
	char c;
	int noc = scanf("%c",&c);
	while(noc == 1 && c != '\n')
	{
		noc = scanf("%c",&c);
	}
}
