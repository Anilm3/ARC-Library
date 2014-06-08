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

#define ARC_ASSERT_TRUE(exp) \
if (!arc_assert_true(exp)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: " #exp " != 0\n"); \
    printf("    Obtained: " #exp " == 0\n"); \
    return 0; \
} 

#define ARC_ASSERT_FALSE(exp) \
if (!arc_assert_false(exp)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: " #exp " == 0\n"); \
    printf("    Obtained: " #exp " != 0\n"); \
    return 0; \
} 

#define ARC_ASSERT_INT_EQUAL(left, right) \
if (!arc_assert_int_equal(left, right)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: " #left " == " #right"\n"); \
    printf("    Obtained: " #left " != " #right"\n"); \
    return 0; \
} 

#define ARC_ASSERT_ULONG_EQUAL(left, right) \
if(!arc_assert_ulong_equal(left, right)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: "  #left " == " #right"\n"); \
    printf("    Obtained: "  #left " != " #right"\n"); \
    return 0; \
} 

#define ARC_ASSERT_STRING_EQUAL(left, right) \
if(!arc_assert_string_equal(left, right)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: "  #left " == " #right"\n"); \
    printf("    Obtained: "  #left " != " #right"\n"); \
    return 0; \
} 

#define ARC_ASSERT_BIT_SET(num, bit) \
if(!arc_assert_bit_set(num, bit)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: " #num"("#bit") == 1""\n"); \
    printf("    Obtained: " #num"("#bit") == 0""\n"); \
    return 0; \
} 

#define ARC_ASSERT_BIT_NOT_SET(num, bit) \
if(!arc_assert_bit_not_set(num, bit)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: " #num"("#bit") == 0""\n"); \
    printf("    Obtained: " #num"("#bit") == 1""\n"); \
    return 0; \
} 

#define ARC_ASSERT_FLOAT_EQUAL(left, right, delta) \
if(!arc_assert_float_equal(left, right, delta)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: "  #left " == " #right" +/-" #delta "\n"); \
    printf("    Obtained: "  #left " != " #right" +/-" #delta "\n"); \
    return 0; \
} 

#define ARC_ASSERT_DOUBLE_EQUAL(left, right, delta) \
if(!arc_assert_double_equal(left, right, delta)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: "  #left " == " #right" +/-" #delta "\n"); \
    printf("    Obtained: "  #left " != " #right" +/-" #delta "\n"); \
    return 0; \
} 

#define ARC_ASSERT_STRING_CONTAINS(str, c) \
if(!arc_assert_string_contains(str, c)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: "  #str " contains " #c"\n"); \
    printf("    Obtained: "  #str " !contains " #c"\n"); \
    return 0; \
}

#define ARC_ASSERT_STRING_DOESNT_CONTAIN(str, c) \
if(!arc_assert_string_doesnt_contain(str, c)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: "  #str " !contains " #c"\n"); \
    printf("    Obtained: "  #str " contains " #c"\n"); \
    return 0; \
} 

#define ARC_ASSERT_STRING_STARTS_WITH(str, c) \
if(!arc_assert_string_starts_with(str, c)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: "  #str "[first] == " #c"\n"); \
    printf("    Obtained: "  #str "[first] != " #c"\n"); \
    return 0; \
} 

#define ARC_ASSERT_STRING_ENDS_WITH(str, c) \
if(!arc_assert_string_ends_with(str, c)) \
{ \
    printf("%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: "  #str "[last] == " #c"\n"); \
    printf("    Obtained: "  #str "[last] != " #c"\n"); \
    return 0; \
} 


#define ARC_TEST(name) \
int name(void) \
{

#define ARC_END_TEST \
    return 1; \
}

#define ARC_TEST_FIXTURE \
int main(void) \
{ \
int passed = 0, failed = 0;


#define ARC_END_TEST_FIXTURE  \
    printf("Passed : %d\nFailed : %d\n", passed, failed); \
    return 0; \
}

#define ARC_ADD_TEST(name) \
printf("Running test : " #name "\n"); \
(name() ? passed++ : failed++);


int arc_assert_true(int exp);
int arc_assert_false(int exp);
int arc_assert_int_equal(int left, int right);
int arc_assert_ulong_equal(unsigned long left, unsigned long right);
int arc_assert_string_equal(const char * left, const char * right);
// int arc_assert_n_array_equal(int exp);
int arc_assert_bit_set(unsigned num, int bit);
int arc_assert_bit_not_set(int num, int bit);
// int arc_assert_bit_mask_matches(int exp);
// int arc_assert_fail(int exp);

int arc_assert_float_equal(float left, float right, float delta);

int arc_assert_double_equal(double left, double right, double delta);

int arc_assert_string_contains(const char * str, char c);

int arc_assert_string_doesnt_contain(const char * str, char c);

int arc_assert_string_starts_with(const char * str, char c);

int arc_assert_string_ends_with(const char * str, char c);

#endif