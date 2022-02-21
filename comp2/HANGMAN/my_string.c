#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "my_string.h"

struct my_string 
{
	int size;
	int capacity;
	char* data;
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
	My_string* pMy_string;
	pMy_string=(My_string*)malloc(sizeof(My_string));
	if(pMy_string == NULL)
	{
		printf("failed to allocate space\n");
		return NULL;
	}	
	pMy_string->size=0;
	pMy_string->capacity=7;
	pMy_string->data = (char*)malloc(sizeof(char)*(pMy_string->capacity));
	if (pMy_string->data == NULL)
	{
		printf("failed to allocate space\n");
		return NULL;
	}
	return (MY_STRING)pMy_string;
}

void my_string_destroy(ITEM* phMy_string)
{
	My_string* pMy_string = (My_string*)*phMy_string;
	free(pMy_string->data);
	pMy_string->data = NULL;
	free(pMy_string);
	*phMy_string=NULL;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
	int i = 0;
	int j = 0;
	while(c_string[i] != '\0' )
	{
		i++;
	}
	//count is found
	
	My_string* pMy_string;
	pMy_string=(My_string*)malloc(sizeof(My_string));
	if(pMy_string == NULL)
	{
		printf("failed to allocated space\n");
		return NULL;
	}
	pMy_string->size=i;
	pMy_string->capacity=i+1;//include null terminator
	pMy_string->data=(char*)malloc(sizeof(char)*(pMy_string->capacity));
	if(pMy_string->data == NULL)
	{
		printf("failed to allocate space \n");
		return NULL;
	}
	while(j<i+1)
	{
		(pMy_string->data)[j] = c_string[j];
		j++;
	}
	pMy_string->data[i]='\0';
	pMy_string->size = i;

	return (MY_STRING)pMy_string;

}

int my_string_get_capacity(MY_STRING hMystring)
{
	My_string* phMy_vector = (My_string*)hMystring;
	return phMy_vector->capacity;
}


int my_string_get_size(MY_STRING hMystring)
{
	My_string* phMy_vector = (My_string*)hMystring;
	return phMy_vector->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	int left_empty,right_empty; 	
	left_empty = my_string_empty(hLeft_string);
	right_empty = my_string_empty(hRight_string);
	if(left_empty || right_empty)
	{
		if(left_empty && right_empty)return 0;
		if(left_empty) return 1;
		if(right_empty) return -1;
	}
	My_string* pLeft_string = (My_string*)hLeft_string;
	My_string* pRight_string = (My_string*)hRight_string;
	pLeft_string->data[pLeft_string->size] = '\0';
	pRight_string->data[pRight_string->size] = '\0';
	int i=0;
	int size = pLeft_string->size;
	if(pRight_string->size < size) size = pRight_string->size;
	for(i=0;(pRight_string->data[i] != '\0' )&& (pLeft_string->data[i] != '\0') &&i<size;i++)
	{
		if(pRight_string->data[i] != pLeft_string->data[i])
		{
			if (pRight_string->data[i] > pLeft_string->data[i]) return -1;
			return 1;
		}	
	}
	if (pRight_string->data[i] == '\0' && pLeft_string->data[i] == '\0') return 0;
	if(pRight_string->data[i] == '\0') return -1;
	if(pLeft_string->data[i] == '\0') return 1;
	return -42;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	char c;
	int noc = fscanf(fp,"%c",&c);
	My_string* pMy_string=(My_string*)hMy_string;
	pMy_string->size=0;
	while(noc != -1)
	{
		while(isspace(c)&&noc != -1)
		{
			noc = fscanf(fp,"%c",&c);
		}
		while(!isspace(c)&& noc != -1)
		{
			if(pMy_string->size+2 < pMy_string->capacity)
			{
				pMy_string->data[my_string_get_size(hMy_string)]=c;
				pMy_string->size++;
			}
			else
			{
				char* temp = NULL;
				temp = malloc(sizeof(char)*my_string_get_capacity(hMy_string)*2);
				if (temp == NULL)
				{
					printf("Memory allocation failed\n");
					return FAILURE;
				}
				int i;
				for(i=0;i<pMy_string->size;i++)
				{
					temp[i]=pMy_string->data[i];
				}
				free(pMy_string->data);
				pMy_string->data = temp;
				temp = NULL;
				pMy_string->capacity *= 2;
				pMy_string->data[pMy_string->size]=c;
				pMy_string->size++;
			}
			noc = fscanf(fp,"%c",&c);
		}
		pMy_string->data[my_string_get_size(hMy_string)]='\0';
		return SUCCESS;
	}
	return FAILURE;	
}


Status my_string_insertion (MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	int i;
	for(i=0;i<pMy_string->size;i++)
	{
		fprintf(fp,"%c",(char)pMy_string->data[i]);
	}
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{	
	My_string* pMy_string = (My_string*)hMy_string;
	if(pMy_string->size+1 <  pMy_string->capacity)
	{
		pMy_string->data[pMy_string->size]=item;
		pMy_string->size++;
		return SUCCESS;
	}
	int capacity_new = pMy_string->capacity*2;
	int i;
	char* temp = NULL;
	temp = (char*)malloc(sizeof(char)*capacity_new);
	if(temp == NULL)
	{
		return FAILURE;
	}
	for(i=0;i<pMy_string->size;i++)
	{
		temp[i]=pMy_string->data[i];
	}
	free(pMy_string->data);
	pMy_string->data = temp;
	temp = NULL;
	pMy_string->data[pMy_string->size]=item;
	pMy_string->size++;
	pMy_string->capacity = capacity_new;
	return SUCCESS;	

}
Status my_string_pop_back(MY_STRING hMy_string)
{	
	My_string* pMy_string = (My_string*)hMy_string;
	if(my_string_empty(hMy_string)) return FAILURE;
	pMy_string->size--;
	pMy_string->data[pMy_string->size]='\0';
	return SUCCESS;
}
char* my_string_at(MY_STRING hMy_string, int index)
{	
	My_string* pMy_string = (My_string*)hMy_string;
	if(index >= pMy_string->size) return NULL;
	return &(pMy_string->data[index]);
}
char* my_string_c_str(MY_STRING hMy_string)
{	
	My_string* pMy_string = (My_string*)hMy_string;
	pMy_string->data[pMy_string->size]='\0';
	return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string* pResult = (My_string*)hResult;
	My_string* pAppend = (My_string*)hAppend;
	char* temp = NULL;
	while(pResult->capacity < (pResult->size + pAppend->size + 1))
	{
		temp=(char*)malloc(sizeof(char)*pResult->capacity*2);
		if(temp == NULL)
		{
			return FAILURE;
		}
		for(int i=0;i<pResult->size;i++)
		{
			temp[i]=pResult->data[i];
		}
		free(pResult->data);
		pResult->data = temp;
		temp = NULL;
		pResult->capacity *= 2;
	}
	for(int i=(pResult->size);i<(pResult->size+(pAppend->size));i++)
	{
		pResult->data[i] = pAppend->data[i-pResult->size];
	}
	pResult->size += pAppend->size;
	pResult->data[pResult->size]='\0';
	return SUCCESS;
}
Boolean my_string_empty(MY_STRING hMy_string)
{	
	My_string* pMy_string = (My_string*)hMy_string;
	if(pMy_string==NULL) return TRUE;
	if(pMy_string->size <= 0) return TRUE;
	return FALSE;
}
Status  my_string_assignment(ITEM* pLeft, ITEM Right)
{
	My_string* pRight_string = (My_string*)Right;
	if(*pLeft == NULL)
	{
		*pLeft = (ITEM)my_string_init_c_string(my_string_c_str((MY_STRING)pRight_string));
		if(*pLeft != NULL) return SUCCESS;
		return FAILURE;	
	}
	else
	{
		My_string** pLeft_string =(My_string**)pLeft;
		(*pLeft_string)->size=0;
		return my_string_concat((MY_STRING)*pLeft,(MY_STRING)pRight_string);
	}
}
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	My_string* pWord_family = (My_string*)current_word_family;
	My_string* pNew_key = (My_string*)new_key;
	My_string* pWord = (My_string*)word;
	int i;
	if(!my_string_assignment(&new_key, current_word_family)) return FAILURE;	
	for(i=0;i<pWord->size;i++)
	{
		if(toupper(*my_string_at(pWord,i)) == toupper(guess))
		{
			pNew_key->data[i] = (i==0)?toupper(guess):tolower(guess);
		}
	}
}
