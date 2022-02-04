#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"
void print_bit_flags(BIT_FLAGS hBit);
void clear_keyboard_buffer(void);
int main(int argc, char* argv[])
{
	int d;
	BIT_FLAGS hBit = bit_flags_init_number_of_bits(8);
	printf("Input numbers ended by '-1'\n");
	int noc = scanf("%d",&d);
	clear_keyboard_buffer();
	while(noc == 1 && d != -1)
	{
		bit_flags_set_flag(hBit, d);
		noc = scanf("%d",&d);
		clear_keyboard_buffer();
	}	
	print_bit_flags(hBit);
	bit_flags_destroy(&hBit);
	return 0;

}

void print_bit_flags(BIT_FLAGS hBit)
{
	int i;
	int max = bit_flags_get_size(hBit);
	printf("Printing from 0 to %d\n",max);
	for(i=0;i<max;i++)
	{
		if(bit_flags_check_flag(hBit, i) == 1)printf("%d\n",i);
	}
}
void clear_keyboard_buffer(void)
{
	char c;
	int NOC = scanf("%c", &c);
	while (NOC != -1 && c != '\n')
	{
		scanf("%c", &c);
	}
}
