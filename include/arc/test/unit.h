/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#ifndef ARC_UNIT_H_
#define ARC_UNIT_H_

#include <stdio.h>

#define ARC_ASSERT_GENERIC(function, expected, obtained) \
if (!function) \
{ \
    printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: " #expected "\n"); \
    printf("    Obtained: " #obtained "\n"); \
    return 0; \
} 

#define ARC_ASSERT_FAIL \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    return 0;

#define ARC_ASSERT_TRUE(exp) \
    ARC_ASSERT_GENERIC(arc_assert_true((int)(exp)), exp != 0, exp == 0)

#define ARC_ASSERT_FALSE(exp) \
    ARC_ASSERT_GENERIC(arc_assert_false((int)(exp)), exp == 0, exp != 0)

#define ARC_ASSERT_POINTER_NULL(exp) \
    ARC_ASSERT_GENERIC(arc_assert_pointer_null((void *)(exp)), \
                       exp == NULL, exp != NULL)

#define ARC_ASSERT_POINTER_NOT_NULL(exp) \
    ARC_ASSERT_GENERIC(arc_assert_pointer_not_null((void *)(exp)), \
                       exp != NULL, exp == NULL)

#define ARC_ASSERT_POINTER_EQUAL(left, right) \
    ARC_ASSERT_GENERIC(arc_assert_pointer_equal((void *)(left), \
                                                (void *)(right)), \
                       left == right, \
                       left != right)

#define ARC_ASSERT_INT_EQUAL(left, right) \
    ARC_ASSERT_GENERIC(arc_assert_int_equal((int)(left), (int)(right)), \
                       left == right, \
                       left != right)

#define ARC_ASSERT_ULONG_EQUAL(left, right) \
    ARC_ASSERT_GENERIC(arc_assert_ulong_equal((unsigned long)(left), \
                                              (unsigned long)(right)), \
                       left == right, \
                       left != right)

#define ARC_ASSERT_STRING_EQUAL(left, right) \
    ARC_ASSERT_GENERIC(arc_assert_string_equal((const char *)(left), \
                                               (const char *)(right)), \
                       left == right, \
                       left != right)

#define ARC_ASSERT_BIT_SET(num, bit) \
    ARC_ASSERT_GENERIC(arc_assert_bit_set((int)(num), (int)(bit)), \
                       num(bit) == 1, \
                       num(bit) == 0)

#define ARC_ASSERT_BIT_NOT_SET(num, bit) \
    ARC_ASSERT_GENERIC(arc_assert_bit_not_set((int)(num), (int)(bit)), \
                       num(bit) == 0, \
                       num(bit) == 1)

#define ARC_ASSERT_FLOAT_EQUAL(left, right, delta) \
    ARC_ASSERT_GENERIC(arc_assert_float_equal((float)(left), \
                                              (float)(right), \
                                              (float)(delta)), \
                       left == right +/-delta, \
                       left != right +/-delta)

#define ARC_ASSERT_DOUBLE_EQUAL(left, right, delta) \
    ARC_ASSERT_GENERIC(arc_assert_double_equal((double)(left), \
                                              (double)(right), \
                                              (double)(delta)), \
                       left == right +/-delta, \
                       left != right +/-delta)

#define ARC_ASSERT_STRING_CONTAINS(str, c) \
    ARC_ASSERT_GENERIC(arc_assert_string_contains((const char *)(str), \
                                                  (char)(c)), \
                       str contains c, \
                       str !contains c)

#define ARC_ASSERT_STRING_DOESNT_CONTAIN(str, c) \
    ARC_ASSERT_GENERIC(arc_assert_string_doesnt_contain((const char *)(str), \
                                                  (char)(c)), \
                       str !contains c, \
                       str contains c)

#define ARC_ASSERT_STRING_STARTS_WITH(str, c) \
    ARC_ASSERT_GENERIC(arc_assert_string_starts_with((const char *)(str), \
                                                  (char)(c)), \
                       str[first] == c, \
                       str[first] != c)

#define ARC_ASSERT_STRING_ENDS_WITH(str, c) \
    ARC_ASSERT_GENERIC(arc_assert_string_ends_with((const char *)(str), \
                                                  (char)(c)), \
                       str[last] == c, \
                       str[last] != c)

#define ARC_TEST(name) \
int name(void) \
{

#define ARC_END_TEST \
    return 1; \
}

#define ARC_SETUP \
void arc_setup(void) \
{

#define ARC_END_SETUP }


#define ARC_TEARDOWN \
void arc_teardown(void) \
{

#define ARC_END_TEARDOWN }

#define ARC_TEST_FIXTURE \
int main(void) \
{ \
    int passed = 0, failed = 0; \
    arc_setup();


#define ARC_END_TEST_FIXTURE  \
    printf("Tests passed: %d/%d : %s\n",  \
            passed, failed + passed, (failed ? "FAILED" : "OK")); \
    arc_teardown(); \
    return 0; \
}

#define ARC_ADD_TEST(name) \
printf("Running : " #name); \
if (name()) \
{ \
    passed++; \
    printf(" : OK\n"); \
} \
else \
{ \
    failed++; \
}

int arc_assert_true(int exp);
int arc_assert_false(int exp);
int arc_assert_pointer_null(void * pointer);
int arc_assert_pointer_not_null(void * pointer);
int arc_assert_pointer_equal(void * left, void * right);
int arc_assert_int_equal(int left, int right);
int arc_assert_ulong_equal(unsigned long left, unsigned long right);
int arc_assert_string_equal(const char * left, const char * right);
// int arc_assert_n_array_equal(int exp);
int arc_assert_bit_set(unsigned num, int bit);
int arc_assert_bit_not_set(int num, int bit);
// int arc_assert_bit_mask_matches(int exp);
int arc_assert_float_equal(float left, float right, float delta);
int arc_assert_double_equal(double left, double right, double delta);
int arc_assert_string_contains(const char * str, char c);
int arc_assert_string_doesnt_contain(const char * str, char c);
int arc_assert_string_starts_with(const char * str, char c);
int arc_assert_string_ends_with(const char * str, char c);

#endif