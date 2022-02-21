#include "bit_flags.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct bit_flags {
unsigned int size;
unsigned int capacity;
unsigned int* data;
};
typedef struct bit_flags Bit_flags;

const unsigned int bit_flags_holder = sizeof(unsigned int)*8;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	Bit_flags* pBit_flags = NULL; 
	pBit_flags= (Bit_flags*)malloc(sizeof(Bit_flags));
	if(pBit_flags != NULL)
	{
		unsigned int to_free =number_of_bits/bit_flags_holder;
		if(number_of_bits % bit_flags_holder != 0) to_free++;
		pBit_flags->data = (unsigned int*)malloc(sizeof(unsigned int)*to_free);
		if(pBit_flags->data != NULL)
		{
			for(int i = 0;i<to_free;i++)
			{
				pBit_flags->data[i] = 0;
			}
			pBit_flags->size = number_of_bits;
			pBit_flags->capacity = to_free*bit_flags_holder;
			return (BIT_FLAGS)pBit_flags;
		}
		free(pBit_flags);
	}
	return FAILURE;

}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	if(bit_flags_check_flag(hBit_flags, flag_position)==1) return FAILURE;
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	unsigned int true_flag_holder = flag_position/bit_flags_holder;
	unsigned int relative_flag_position = flag_position - true_flag_holder*bit_flags_holder;
	int i;
	unsigned int* temp = NULL;
	if(flag_position >= pBit_flags->capacity)
	{	
		unsigned int to_free = (flag_position+1)/bit_flags_holder;
		if((flag_position+1) % bit_flags_holder != 0) to_free++;
		temp = (unsigned int*)malloc(sizeof(unsigned int)*to_free);
		if(temp == NULL) return FAILURE;
		for(i=0;i<pBit_flags->capacity/bit_flags_holder;i++)
		{
			temp[i] = pBit_flags->data[i];
		}
		while(i<to_free)
		{
			temp[i]=0;
			i++;
		}
		free(pBit_flags->data);
		pBit_flags->data = temp;
		pBit_flags->size = flag_position+1;
		pBit_flags->capacity = to_free*bit_flags_holder;
		temp = NULL;
	}
	
	unsigned int add = 1 << relative_flag_position;

	pBit_flags->data[true_flag_holder] += add;
	
	if(flag_position >= pBit_flags->size) pBit_flags->size = flag_position+1;

	return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	unsigned int true_flag_holder = flag_position/bit_flags_holder;
	unsigned int relative_flag_position = flag_position - true_flag_holder*bit_flags_holder;
	int i;
	unsigned int* temp = NULL;
	if(flag_position >= pBit_flags->capacity)
	{	
		unsigned int to_free = (flag_position+1)/bit_flags_holder;
		if((flag_position+1) % bit_flags_holder != 0) to_free++;
		temp = (unsigned int*)malloc(sizeof(unsigned int)*to_free);
		if(temp == NULL) return FAILURE;
		for(i=0;i<pBit_flags->capacity/bit_flags_holder;i++)
		{
			temp[i] = pBit_flags->data[i];
		}
		while(i<to_free)
		{
			temp[i]=0;
			i++;
		}
		free((pBit_flags->data));
		pBit_flags->data = temp;
		pBit_flags->size = flag_position+1;
		pBit_flags->capacity = to_free*bit_flags_holder;
		temp = NULL;
		return SUCCESS; 
	}
	if(bit_flags_check_flag(hBit_flags,flag_position)==0) return SUCCESS;


	unsigned int subtract = 1 << relative_flag_position;

	pBit_flags->data[true_flag_holder] -= subtract;
	
	if(flag_position >= pBit_flags->size) pBit_flags->size = flag_position+1;

	return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	if(pBit_flags->capacity>flag_position)
	{
		unsigned int true_flag_holder = flag_position/bit_flags_holder;
		unsigned int relative_flag_position = flag_position - true_flag_holder*bit_flags_holder;
		unsigned int data = pBit_flags->data[true_flag_holder];
       		data = data >> relative_flag_position;
		if(data%2==1) return 1;	       
		return 0;
	}
	return -1;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	return pBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{	
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	return pBit_flags->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)*phBit_flags;
	free(pBit_flags->data);
	pBit_flags->data = NULL;
	free(pBit_flags);
	*phBit_flags=NULL;
}

