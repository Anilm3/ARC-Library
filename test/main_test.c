#include <stdlib.h>
#include <stdio.h>

int arc_assert_true(int exp);
int arc_assert_false(int exp);
int arc_assert_int_equal(int left, int right);
int arc_assert_ulong_equal(unsigned long left, unsigned long right);
int arc_assert_string_equal(char * left, char * right);
int arc_assert_n_array_equal(int exp);
int arc_assert_bit_set(int exp);
int arc_assert_bit_not_set(int exp);
int arc_assert_bit_mask_matches(int exp);
int arc_assert_fail(int exp);
int arc_assert_float_equal(int exp);
int arc_assert_double_equal(int exp);
int arc_assert_string_contains(int exp);
int arc_assert_string_doesnt_contain(int exp);
int arc_assert_string_starts_with(int exp);
int arc_assert_string_ends_with(int exp);