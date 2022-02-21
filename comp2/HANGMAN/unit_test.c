#include <stdio.h>
#include "unit_test.h"
int main(int argc, char* argv[])
{
 Status (*tests[])(char*, int) =
 {
 test_init_default_returns_nonNULL,
 test_get_size_on_init_default_returns_0,
 test_get_capacity_on_init_default_returns_7,
 test_init_c_string_compared_to_extraction_returns_0_via_compare,
 test_init_c_string_compared_to_extraction_returns_less_than_0_via_compare,
 test_init_c_string_compared_to_extraction_returns_greater_than_0_via_compare,
 test_at_on_init_c_string,
 test_pop_back_on_init_c_string_via_compare_with_c_string_init,
 test_pop_back_failure_on_empty_init_default, 
 test_push_back_on_empty_init_deafult,
 test_pop_back_on_init_c_string_via_get_size,
 test_push_back_on_init_c_string_via_get_size,
 test_push_back_capacity_is_larger_than_size_via_get,
 test_concat_via_get_size,
 test_concat_via_compare_with_init_c_string,
 test_destroy_returns_NULL,
 test_get_size_on_int_c_str, 
 test_get_capacity_init_c_str,
 test_init_c_str_insertion_extraction_compare,
 test_int_c_str_insertion_extration_get_size,
 test_capacity_resize_on_init_default_after_8_push_bakcs,
 test_compare_with_two_init_c_str_str1_abc_str2_abcd,
 test_compare_with_two_init_c_str_str1_abcd_str2_abc,
 test_at_out_of_bounds_returns_NULL,
 test_empty_on_non_empty_list,
 };
 int number_of_functions = sizeof(tests) / sizeof(tests[0]);
 int i;
 char buffer[500];
 int success_count = 0;
 int failure_count = 0;
 for(i=0; i<number_of_functions; i++)
 {
	 if(tests[i](buffer, 500) == FAILURE)
 	{
 		printf("FAILED: Test %d failed miserably\n", i);
 		printf("\t%s\n", buffer);
 		failure_count++;
 	}
 	else
 	{
		// printf("PASS: Test %d passed\n", i);
		// printf("\t%s\n", buffer);
 		success_count++;
 	}
 }
 printf("Total number of tests: %d\n", number_of_functions);
 printf("%d/%d Pass, %d/%d Failure\n", success_count,
 number_of_functions, failure_count, number_of_functions);
 return 0;
}
