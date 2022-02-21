#include "status.h"
#include "bit_flags.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void print(BIT_FLAGS hBit_flags);
void print_cap(BIT_FLAGS hBit_flags);
void failure(BIT_FLAGS hBit_flags);

int main (int argc, char* argv[])
{
	srand(time(NULL));
	for(int i = 0; i < 1; i++)
	{
		BIT_FLAGS hBits = bit_flags_init_number_of_bits(32);
		failure(hBits);
		for(int j=0;j<33;j++)
		{
			bit_flags_set_flag(hBits,j);
			print(hBits);
		}
		printf("New bit_flag object\n");
		print(hBits);
		bit_flags_destroy(&hBits);
	}
	

	return 0;
}

void failure(BIT_FLAGS hBit_flags)
{
	if(hBit_flags == NULL)
	{
		printf("FAILURE\n");
		exit(1);
	}
}
void print(BIT_FLAGS hBit_flags)
{
	printf("\n");
	printf("size of bit flags =%d\n",bit_flags_get_size(hBit_flags));
	printf("capacity of bit flags =%d\n",bit_flags_get_capacity(hBit_flags));
	for(int i = bit_flags_get_capacity(hBit_flags)-1;i>=0;i--)
	{
		printf("%u",bit_flags_check_flag(hBit_flags,i));
		if(i%4==0)printf(" ");
		if(i%32==0)printf("\n");
	}
	printf("\n");
}

void print_cap(BIT_FLAGS hBit_flags)
{
	int size = bit_flags_get_size(hBit_flags);
	int capacity = bit_flags_get_capacity(hBit_flags);
	if(size > capacity)
	{
		printf("error, size is larger than capacity\nSize=%d\nCapacity=%d\n\n",size,capacity);
	}
	if(capacity % 32 != 0)
	{
		printf("capacity of %d is invalid as %d is the remainder of capacity/32\n",capacity,capacity%32);
	} 
}

