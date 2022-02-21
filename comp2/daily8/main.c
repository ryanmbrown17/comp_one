#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void clear_keyboard_buffer(void);
Boolean should_push_c(char c);
Boolean should_pop_c(char c, STACK hStack);
Boolean check(void);

int main(int argc, char* argv[]) 
{
	int d,i;
	FILE* fp;

	scanf("%d",&d);
	clear_keyboard_buffer();
	for(i=0;i<d;i++)
	{
		switch(check())
		{
		case(TRUE):
		       printf("Yes\n");
			break;
		default:
			printf("No\n");	
		}
	}
	return 0;
}

Boolean check(void)
{
	char c='a';
	int noc=0;
	STACK hStack;

	hStack = stack_init_default();
	while(c != '\n' && noc != -1)
	{
		scanf("%c",&c);	
		if(should_push_c(c))
		{	
			stack_push(hStack,c);
		}
		if(should_pop_c(c, hStack))
		{	
			stack_pop(hStack);
		}
		else if (c == ')' || c == '}' || c == ']') 
		{
			clear_keyboard_buffer();
			stack_destroy(&hStack);
			return FALSE;
		}
	}
	noc = stack_is_empty(hStack);
	stack_destroy(&hStack);
	if(noc)return TRUE;
	return FALSE;
}


void clear_keyboard_buffer(void)
{
	char c;
	int noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
		{
			noc = scanf("%c", &c);
		}
}

Boolean should_push_c(char c)
{
	switch ((int)c)
	{
	case('('):
	case('{'):
	case('['):
		return TRUE;
	default:
		return FALSE;
	}
}
Boolean should_pop_c(char c, STACK hStack)
{
	switch ((int)stack_top(hStack,NULL))
	{
	case('('):
		if ((int)c == ')') return TRUE;
		break;
	case('{'):
		if ((int)c == '}') return TRUE;
		break;
	case('['):
		if ((int)c == ']') return TRUE;
		break;
	default:
		break;
	}
	return FALSE;
}
