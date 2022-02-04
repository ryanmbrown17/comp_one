#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_get_capacity_on_init_default_returns_7 (char* buffer, int length);
Status test_init_c_string_compared_to_extraction_returns_0_via_compare (char* buffer, int length);
Status test_init_c_string_compared_to_extraction_returns_less_than_0_via_compare (char* buffer, int length);
Status test_init_c_string_compared_to_extraction_returns_greater_than_0_via_compare (char* buffer, int length);
Status test_at_on_init_c_string (char* buffer, int length);
Status test_pop_back_on_init_c_string_via_compare_with_c_string_init (char* buffer, int length);
Status test_pop_back_failure_on_empty_init_default (char* buffer, int length);
Status test_push_back_on_empty_init_deafult (char* buffer, int length);
Status test_pop_back_on_init_c_string_via_get_size (char* buffer, int length);
Status test_push_back_on_init_c_string_via_get_size (char* buffer, int length);
Status test_push_back_capacity_is_larger_than_size_via_get (char* buffer, int length);
Status test_concat_via_get_size (char* buffer, int length);
Status test_concat_via_compare_with_init_c_string (char* buffer, int length);
Status test_destroy_returns_NULL (char* buffer, int length);
Status test_get_size_on_int_c_str (char* buffer, int length);
Status test_get_capacity_init_c_str (char* buffer, int length);
Status test_init_c_str_insertion_extraction_compare (char* buffer, int length);
Status test_int_c_str_insertion_extration_get_size (char* buffer, int length);
Status test_capacity_resize_on_init_default_after_8_push_bakcs (char* buffer, int length);
Status test_compare_with_two_init_c_str_str1_abc_str2_abcd (char* buffer, int length);
Status test_compare_with_two_init_c_str_str1_abcd_str2_abc (char* buffer, int length);
Status test_at_out_of_bounds_returns_NULL (char* buffer, int length);
Status test_empty_on_non_empty_list (char* buffer, int length);

#endif
