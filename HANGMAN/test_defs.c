#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unit_test.h"
Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	 MY_STRING hString = NULL;
	 hString = my_string_init_default();
 	if(hString == NULL)
 	{
	 	strncpy(buffer, "test_init_default_returns_nonNULL\n"
	 	"my_string_init_default returns NULL", length);
 		return FAILURE;
 	}
 	else
 	{
 		my_string_destroy((Item*)&hString);
 		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
 		return SUCCESS;
 	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
 	MY_STRING hString = NULL;
 	Status status;
 	hString = my_string_init_default();
 	if(my_string_get_size(hString) != 0)
 	{
 		status = FAILURE;
 		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
 		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
 		"Did not receive 0 from get_size after init_default\n", length);
	 }
 	else
	 {
	 	status = SUCCESS;
	 	strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	 	, length);
	 }
	 my_string_destroy((Item*)&hString);
	 return status;
}
Status test_get_capacity_on_init_default_returns_7 (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_capacity(hString) != 7)
	{
		status = FAILURE;
		printf("Expected a capacity of 7, but go %d\n",my_string_get_size(hString));
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n" 
		"Did not recieve 7 from get_capacitity after init_deefault\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n",length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_init_c_string_compared_to_extraction_returns_0_via_compare (char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	FILE* fp = NULL;
	Status status;
	hString1 = my_string_init_c_string("Live_Long_and_Prosper");
	fp = fopen("input.txt","w");
	fprintf(fp,"Live_Long_and_Prosper");
	fclose(fp);
	fp = fopen("input.txt","r");
	hString2 = my_string_init_default();
	status = my_string_extraction(hString2,fp);
	fclose(fp);
	if(my_string_compare(hString1,hString2)!=0)
	{
		status = FAILURE;
		printf("Expected the same string, but got\nString 1: %s\nString 2: %s \n",my_string_c_str(hString1),my_string_c_str(hString2));
		strncpy(buffer, "test_init_c_string_compared_to_extraction_returns_0_via_compare\n" 
		"Did not recieve 0 from compare after init_c_string and init_default + extraction\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_init_c_string_compared_to_extraction_returns_0_via_compare\n",length);
	}
	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}

Status test_init_c_string_compared_to_extraction_returns_less_than_0_via_compare (char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	FILE* fp = NULL;
	Status status;
	hString1 = my_string_init_c_string("Live_Long_and_Prosper");
	fp = fopen("input.txt","w");
	fprintf(fp,"Peace_and_Long_Life");
	fclose(fp);
	fp = fopen("input.txt","r");
	hString2 = my_string_init_default();
	status = my_string_extraction(hString2,fp);
	fclose(fp);
	if( my_string_compare(hString1,hString2) >= 0)
	{
		status = FAILURE;
		printf("Expected string2 to be larger and compare to return a number less than 0.  Got %d\nStr1 Supposed to be:Live_Long_and_Prosper\ngot:%s\nStr2 Supposed to be Peace_and_Long_Life\nGot:%s\n",my_string_compare(hString1,hString2),my_string_c_str(hString1),my_string_c_str(hString2));
		strncpy(buffer, "test_init_c_string_compared_to_extraction_returns_less_than_0_via_compare\n" 
		"Did not recieve a number less than 0 from compare after init_c_string and init_default + extraction\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_init_c_string_compared_to_extraction_returns_less_than_0_via_compare\n",length);
	}
	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}

Status test_init_c_string_compared_to_extraction_returns_greater_than_0_via_compare (char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	FILE* fp = NULL;
	Status status;
	hString1 = my_string_init_c_string("Xylophone");
	fp = fopen("input.txt","w");
	fprintf(fp,"Without_Freedom_of_Choice_there_is_no_Creativity");
	fclose(fp);
	fp = fopen("input.txt","r");
	hString2 = my_string_init_default();
	status = my_string_extraction(hString2,fp);
	fclose(fp);
	if( my_string_compare(hString1,hString2) <= 0)
	{
		status = FAILURE;
		printf("Expected string1 to be larger and compare to return a number greater than 0.  Got %d\nStr1 Supposed to be:Xylophone\ngot:%s\nStr2 Supposed to be Without_Freedom_of_Choice_there_is_no_Creativity \nGot:%s\n",my_string_compare(hString1,hString2),my_string_c_str(hString1),my_string_c_str(hString2));
		strncpy(buffer, "test_init_c_string_compared_to_extraction_returns_greater_than_0_via_compare\n" 
		"Did not recieve a number more than 0 from compare after init_c_string and init_default + extraction\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_init_c_string_compared_to_extraction_returns_greater_than_0_via_compare\n",length);
	}
	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}
Status test_at_on_init_c_string (char* buffer, int length)
{
	Status status;
	char* d;
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("So_Long_and_Thanks_for_All_the_Fish");
	d=my_string_at(hString,3);
	if(*d != 'L')
	{	
		status = FAILURE;
		printf("Expected L to be 3rd index in So_Long_and_Thanks_for_All_the_Fish, got %c, with a number value of %d\n",*d,*d);
		strncpy(buffer, "test_at_on_init_c_string\n" 
		"Did not recieve L as 3rd index, but it is 4th letter of the string\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_at_on_init_c_string\n",length);
	}	
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_pop_back_on_init_c_string_via_compare_with_c_string_init (char* buffer, int length)
{
	MY_STRING hString = NULL;
	MY_STRING hString2 = NULL;
	Status status;
	hString = my_string_init_c_string("Hello");
	status = my_string_pop_back(hString);
	hString2 = my_string_init_c_string("Hell");
	if(my_string_compare(hString,hString2) || status == FAILURE)	
	{	
		status = FAILURE;
		printf("Expected Str1 and Str2 to be the same.\nStr one was supposed to be 'Hello' with popback making it 'Hell'.  It was %s\nStr two was supposed to be 'Hell'.  It was %s\nCompare function returned %d\n",my_string_c_str(hString),my_string_c_str(hString2),my_string_compare(hString,hString2));
		strncpy(buffer, "test_pop_back_on_init_c_string_via_compare_with_c_string_init\n" 
		"Either failed to pop, or popped wrong, or compared wrong\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_pop_back_on_init_c_string_via_compare_with_c_string_init\n",length);
	}
	my_string_destroy((Item*)&hString);
	my_string_destroy((Item*)&hString2);	
	return status;
}
Status test_pop_back_failure_on_empty_init_default (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	status = my_string_pop_back(hString);

	if(status != 0) 	
	{	
		status = FAILURE;
		printf("Expected empty init default string to fail on pop back\n");
		strncpy(buffer, "test_pop_back_failure_on_empty_init_default\n" 
		"Did not return failure on pop back on empty init default my_string\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_pop_back_failure_on_empty_init_default\n",length);
	}	
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_push_back_on_empty_init_deafult (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	status = my_string_push_back(hString,'h');
	int empty = my_string_empty(hString);
	int size = my_string_get_size(hString);

		
	if(empty == 1 || size != 1 || status == FAILURE)
	{	
		status = FAILURE;
		printf("Expected a nonempty, size of one, string from my_string_init_default and push back a character (h)\n");
		strncpy(buffer, "test_push_back_on_empty_init_default\n" 
		"returned a failure push back, a incorect size or empty sring\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_push_back_on_empty_init_default\n",length);
	}	
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_pop_back_on_init_c_string_via_get_size (char* buffer, int length)
{

	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Three");
	status = my_string_pop_back(hString);
	int empty = my_string_empty(hString);
	int size = my_string_get_size(hString);

		
	if(empty == 1 || size != 4 || status == FAILURE)
	{	
		status = FAILURE;
		printf("Expected a nonempty, size of 4, string from init_c_string 'three' and a pop back\n");
		strncpy(buffer, "test_pop_back_on_init_c_string_via_get_size\n" 
		"returned a failure pop back, a incorect size or empty sring\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_pop_back_on_init_c_string_via_get_size\n",length);
	}	
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_push_back_on_init_c_string_via_get_size (char* buffer, int length)
{

	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Three");
	status = my_string_push_back(hString,'s');
	int empty = my_string_empty(hString);
	int size = my_string_get_size(hString);

		
	if(empty == 1 || size != 6 || status == FAILURE)
	{	
		status = FAILURE;
		printf("Expected a nonempty, size of 6, string from init_c_string 'three' and a push back (3)\n");
		strncpy(buffer, "test_push_back_on_init_c_string_via_get_size\n" 
		"returned a failure push back, a incorect size or empty sring\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_push_back_on_init_c_string_via_get_size\n",length);
	}	
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_push_back_capacity_is_larger_than_size_via_get(char* buffer, int length)
{

	MY_STRING hString = NULL;
	Status status = SUCCESS;
	int i=0;
	hString = my_string_init_c_string("YOU_CANT_HANDLE_THE_TRUTH");
	while(status != FAILURE && i<5)
	{
		status = my_string_push_back(hString,'!');
		i++;
	}
	int size = my_string_get_size(hString);
	int capacity = my_string_get_capacity(hString);
		
	if(size != 30 || capacity < size || status == FAILURE)
	{	
		status = FAILURE;
		printf("Expected a size 30 string, with a larger capacity, or nonfailure from push_back.\n  Size %d, Capacity%d\n",size,capacity);
		strncpy(buffer, "test_push_back_capacity_is_larger_than_size_via_get\n" 
		"returned a failure push back, a incorect size or smaller capacity than size\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_push_back_capacity_is_larger_than_size_via_get\n",length);
	}	
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_concat_via_get_size (char* buffer, int length)
{
	MY_STRING hString = NULL;
	MY_STRING hStr2 = NULL;
	Status status;
	hString = my_string_init_c_string("hello");
	hStr2 = my_string_init_c_string("_m8");

	status = my_string_concat(hString,hStr2);
	int size = my_string_get_size(hString);
	if(size != 8 || status == FAILURE)
	{	
		status = FAILURE;
		printf("Expected a size 8 with 'hello' and '_m8' being the two strings.  Either size != 8 or concat returned failure\n");
		strncpy(buffer, "test_concat_via_get_size\n" 
		"returned a failure from concat, or incorect size\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_concat_via_get_size\n",length);
	}	
	my_string_destroy((Item*)&hString);
	my_string_destroy((Item*)&hStr2);
	return status;
}

Status test_concat_via_compare_with_init_c_string (char* buffer, int length)
{
	MY_STRING hString = NULL;
	MY_STRING hStr2 = NULL;
	MY_STRING hSTRfinal = NULL;
	Status status;
	hString = my_string_init_c_string("hello");
	hStr2 = my_string_init_c_string("_m8");
	hSTRfinal = my_string_init_c_string("hello_m8");
	status = my_string_concat(hString,hStr2);
	int compare = my_string_compare(hString,hSTRfinal);
	if(compare != 0 || status == FAILURE)
	{	
		status = FAILURE;
		printf("Expected a return of 0 from compare.  Compared the concat of 'hello' and '_m8' being the two strings with 'hello_m8' either compare didn't return 0 or concat returned failure\nCompare is %d\nStr1 is %s\nStr2 is %s\n",compare,my_string_c_str(hString),my_string_c_str(hSTRfinal));
		strncpy(buffer, "test_concat_via_compare_with_init_c_string\n" 
		"returned a failure from concat, or compare failed correctly or incorrectly\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_concat_via_compare_with_init_c_string\n",length);
	}	
	my_string_destroy((Item*)&hString);
	my_string_destroy((Item*)&hStr2);
	my_string_destroy((Item*)&hSTRfinal);
	return status;
}

Status test_destroy_returns_NULL (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	my_string_destroy((Item*)&hString);	
	if(hString != NULL)
	{
		status = FAILURE;
		printf("expected NULL after destroyed stack\n");
		strncpy(buffer, "test_destroy_returns_NULL\n"
				"Destroy does not make hString NULL\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_destroy_returns_NULL\n",length);
	}
	return status;

}
Status test_get_size_on_int_c_str (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Pokemon_go_to_the_polls");
	if(my_string_get_size(hString) != 23)
	{
		status = FAILURE;
		printf("Expected a size of 23, but got %d\n",my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_int_c_str\n" 
		"Did not recieve 23 from get_size after init c string of 23\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_int_c_str\n",length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_get_capacity_init_c_str (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Pokemon_go_to_the_polls");
	if(my_string_get_capacity(hString) <= 23)
	{
		status = FAILURE;
		printf("Expected a size of 23, but got a capacity lower or at. Cap= %d\n",my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_on_int_c_str\n" 
		"Did not recieve a value larger than 23 from get_capacity after init c string of 23\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_int_c_str\n",length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_init_c_str_insertion_extraction_compare (char* buffer, int length)
{
	MY_STRING hString = NULL;
	FILE* fp = NULL;
	Status status;
	hString = my_string_init_c_string("Pokemon_go_to_the_polls");
	fp = fopen("input.txt","w");
	status=	my_string_insertion(hString,fp);
	fclose(fp);
	MY_STRING hStr2 = NULL;
	hStr2 = my_string_init_default();
	if(status != FAILURE)
	{
		fp=fopen("input.txt","r");
		status = my_string_extraction(hStr2,fp);
		fclose(fp);
	}
	int compare = my_string_compare(hString, hStr2);
	if(compare != 0 || status == FAILURE)
	{
		status = FAILURE;
		printf("Expected insertion and extraction to succeed and return 0 from compare.  STR left is original. Got %d\nSTR left (1) is %s\nStr right (II) is %s\n",compare,my_string_c_str(hString),my_string_c_str(hStr2));
		strncpy(buffer, "test_init_c_str_insertion_extraction_compare\n" 
		"Did not recieve 0 from compare or extraction/insertion failed\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_init_c_str_insertion_extraction_comare\n",length);
	}
	my_string_destroy((Item*)&hString);
	my_string_destroy((Item*)&hStr2);
	return status;
}


Status test_int_c_str_insertion_extration_get_size (char* buffer, int length)
{
	MY_STRING hString = NULL;
	FILE* fp = NULL;
	Status status;
	hString = my_string_init_c_string("Pokemon_go_to_the_polls");
	fp = fopen("input.txt","w");
	status=	my_string_insertion(hString,fp);
	fclose(fp);
	MY_STRING hStr2 = NULL;
	hStr2 = my_string_init_default();
	if(status != FAILURE)
	{
		fp=fopen("input.txt","r");
		status = my_string_extraction(hStr2,fp);
		fclose(fp);
	}
	int size1 = my_string_get_size(hString);
	int size2 = my_string_get_size(hStr2);

	if(size1 != size2 || status == FAILURE)
	{
		status = FAILURE;
		printf("Expected insertion and extraction to succeed and return same size from original and new.  %d orginal. %d new\n",size1,size2);
		strncpy(buffer, "test_init_c_str_insertion_exttraction_get_size\n" 
		"Did not recieve same size for string after insertion/extraction.  or failure \n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_init_c_str_insertion_extraction_get_size\n",length);
	}
	my_string_destroy((Item*)&hString);
	my_string_destroy((Item*)&hStr2);
	return status;
}
Status test_capacity_resize_on_init_default_after_8_push_bakcs (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	int i = 0;
	hString = my_string_init_default();

	for(;i<8;i++)
	{
		my_string_push_back(hString,'a');
	}
	int capacity = my_string_get_capacity(hString);
	if(capacity <= 7)
	{
		status = FAILURE;
		printf("Expected capacity to be bigger after init default and 8 push backs. %d cap\n",capacity);
		strncpy(buffer, "test_capacity_resize_on_init_default_after_8_push_backs\n" 
		"Did not recieve large enough capacity\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_capacity_resize_on_init_default_after_8_push_backs\n",length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_compare_with_two_init_c_str_str1_abc_str2_abcd (char* buffer, int length)
{
	MY_STRING hString = NULL;
	MY_STRING hString2 = NULL;
	Status status;
	hString = my_string_init_c_string("abc");
	hString2 = my_string_init_c_string("abcd");
	int compare = my_string_compare(hString, hString2);

	if(compare <= 0)
	{
		status = FAILURE;
		printf("Expected compare to result in number greater than 0, since right string is larger.  Got %d \n",compare);
		strncpy(buffer, "test_compare_with_two_init_c_str_str1_abc_str2_abcd\n" 
		"Did not recieve a number greater than 0 from compare\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_compare_with_two_init_c_str_str1_abc_str2_abcd\n",length);
	}
	my_string_destroy((Item*)&hString);
	my_string_destroy((Item*)&hString2);
	return status;
}
Status test_compare_with_two_init_c_str_str1_abcd_str2_abc (char* buffer, int length)
{
	MY_STRING hString = NULL;
	MY_STRING hString2 = NULL;
	Status status;
	hString = my_string_init_c_string("abc");
	hString2 = my_string_init_c_string("abcd");
	int compare = my_string_compare(hString2, hString);

	if(compare >= 0)
	{
		status = FAILURE;
		printf("Expected compare to result in number less than 0, since lest string is larger.  Got %d \n",compare);
		strncpy(buffer, "test_compare_with_two_init_c_str_str1_abcd_str2_abc\n" 
		"Did not recieve a number less than 0 from compare\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_compare_with_two_init_c_str_str1_abcd_str2_abc\n",length);
	}
	my_string_destroy((Item*)&hString);
	my_string_destroy((Item*)&hString2);
	return status;
}
Status test_at_out_of_bounds_returns_NULL (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("WandaVision");
	char* at11 = my_string_at(hString,11);
       	if(at11 != NULL)
	{
		status = FAILURE;
		printf("Checked a 11 long string at index 11 (place 12) and did not recieve null \n");
		strncpy(buffer, "test_at_out_of_bounds_returns_NULL\n" 
		"Did not recieve NULL from at index that is out of bounds\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_compare_at_out_of_bounds_returns_NULL\n",length);
	}
	my_string_destroy((Item*)&hString);	
	return status;
}
Status test_empty_on_non_empty_list (char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("WandaVision");
	int empty = my_string_empty(hString);
	if(empty == 1)
	{
		status = FAILURE;
		printf("Checked the size of a nonempty string, got empty \n");
		strncpy(buffer, "test_empty_on_non_empty_list\n" 
		"Recieved empty from nonempty list\n",length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_empty_on_non_empty_list\n",length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}
