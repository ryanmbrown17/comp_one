#include <stdio.h>

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);

int main(int argc, char* argv[])
{
	unsigned int flag_holder[5] = { 0 };//Set the first integer to zero and all others
	//to zero by default.
	set_flag(flag_holder, 3);
	set_flag(flag_holder, 16);
	set_flag(flag_holder, 31);
	set_flag(flag_holder, 87);
	display_flags(flag_holder, 5);
	printf("\n\n");
	unset_flag(flag_holder, 31);
	unset_flag(flag_holder, 3);
	set_flag(flag_holder, 99);
	set_flag(flag_holder, 100);
	display_flags(flag_holder, 5);
	return 0;
}
void set_flag(unsigned int flag_holder[], int flag_position)
{
	if(check_flag(flag_holder, flag_position) == 0) flag_holder[(flag_position / 32)] += 1 << (flag_position - (flag_position / 32) * 31);
}
void unset_flag(unsigned int flag_holder[], int flag_position)
{
	if (check_flag(flag_holder, flag_position ) == 1)
	{
		flag_holder[(flag_position / 32)] -= 1 << flag_position;
	}
}
int check_flag(unsigned int flag_holder[], int flag_position)
{
	unsigned int copy_flag_holder = flag_holder[flag_position / 32];
	copy_flag_holder = copy_flag_holder >> (flag_position - (flag_position / 32) * 31);
	if (copy_flag_holder % 2 == 1) return 1;
	return 0;
}

void display_32_flags_as_array(unsigned int flag_holder)
{
	int i;
	for (i = 31; i >= 0; i--)
	{
		printf("%d", check_flag(&flag_holder, i));
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
}

void display_flags(unsigned int flag_holder[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		display_32_flags_as_array(flag_holder[i]);
	}
}
