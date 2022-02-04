/**********************************************************************
Program: reverse!
Author: Ryan Brown
Date: 2/9
Time spent: god...too long...2 hours? little less
Purpose: Reverse a linked list that is given from main...originally I found it took less code to keep the numbers
where they are and swap the addresses.  As a whole I found out that method would work, however it would have to return the 
address of a new start.  So after completing that program, I had to scrap it and swap the numbers instead which took me more
time and took significantly more code.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

//declare your function here.
void reverse(Node* head);

int main(int argc, char* argv[])
{
	Node* head = NULL;
	int i;
	Node* temp;

	//set up a test list with values 9->8->7->...->0
	for (i = 0; i < 10; i++)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			printf("out of memory?\n");
			exit(1);
		}
		temp->data = i;
		temp->next = head;
		head = temp;
	}
	
	//call your function to reverse the list (should work for any list given the head node pointer).
	reverse(head);

	//print the reversed list.
	temp = head;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}

	return 0;
}

//Define your function here
void reverse(Node* head)
{
	Node* future = head->next; 
	Node* previous = head;
	Node* current = head;
	int temp_data = head->data;

	while (future != NULL) //swaps the linked items, node 2 points to node 1 now, 3 to 2, etc.
	{
		current = future; 
		future = current->next;
		current->next = previous;
		previous = current;
	}

	head->next->next = current; //node 2 needs to point to last node now

	//swaps the first node's and the last node's data and pointer
	head->data = current->data;
	head->next = current->next;
	current->data = temp_data;
	current->next = NULL;
}

