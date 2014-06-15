/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file unit.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Unit test framework
 *
 * @see http://en.wikipedia.org/wiki/Unit_testing
 */

#ifndef ARC_UNIT_H_
#define ARC_UNIT_H_

#include <stdio.h>

/**
 * @brief Generic assertion
 *
 * @param[in] function Function to evaluate
 * @param[in] expected Expected expression to print
 * @param[in] obtained Obtained expression to print
 */
#define ARC_ASSERT_GENERIC(function, expected, obtained) \
if (!function) \
{ \
    printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
    printf("    Expected: " #expected "\n"); \
    printf("    Obtained: " #obtained "\n"); \
    arc_set_test_failed(); \
    return; \
} 
/**
 * @brief Assertion which always fails
 */
#define ARC_ASSERT_FAIL() \
    printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
    arc_set_test_failed(); \
    return;
/**
 * @brief Asserts the expression is true
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_TRUE(exp) \
    ARC_ASSERT_GENERIC(arc_assert_true((int)(exp)), exp != 0, exp == 0)
/**
 * @brief Asserts the expression is false
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_FALSE(exp) \
    ARC_ASSERT_GENERIC(arc_assert_false((int)(exp)), exp == 0, exp != 0)
/**
 * @brief Asserts the expression is NULL
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_POINTER_NULL(exp) \
    ARC_ASSERT_GENERIC(arc_assert_pointer_null((void *)(exp)), \
                       exp == NULL, exp != NULL)
/**
 * @brief Asserts the expression is not NULL
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_POINTER_NOT_NULL(exp) \
    ARC_ASSERT_GENERIC(arc_assert_pointer_not_null((void *)(exp)), \
                       exp != NULL, exp == NULL)
/**
 * @brief Asserts left and right pointers are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 */
#define ARC_ASSERT_POINTER_EQUAL(left, right) \
    ARC_ASSERT_GENERIC(arc_assert_pointer_equal((void *)(left), \
                                                (void *)(right)), \
                       left == right, \
                       left != right)
/**
 * @brief Asserts left and right integers are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 */
#define ARC_ASSERT_INT_EQUAL(left, right) \
    ARC_ASSERT_GENERIC(arc_assert_int_equal((int)(left), (int)(right)), \
                       left == right, \
                       left != right)
/**
 * @brief Asserts left and right unsigned longs are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 */
#define ARC_ASSERT_ULONG_EQUAL(left, right) \
    ARC_ASSERT_GENERIC(arc_assert_ulong_equal((unsigned long)(left), \
                                              (unsigned long)(right)), \
                       left == right, \
                       left != right)
/**
 * @brief Asserts left and right strings are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 */
#define ARC_ASSERT_STRING_EQUAL(left, right) \
    ARC_ASSERT_GENERIC(arc_assert_string_equal((const char *)(left), \
                                               (const char *)(right)), \
                       left == right, \
                       left != right)
/**
 * @brief Asserts bit is set
 *
 * @param[in] num Number on which to evaluate the bit
 * @param[in] bit Bit to evaluate
 */
#define ARC_ASSERT_BIT_SET(num, bit) \
    ARC_ASSERT_GENERIC(arc_assert_bit_set((int)(num), (int)(bit)), \
                       num(bit) == 1, \
                       num(bit) == 0)
/**
 * @brief Asserts bit is not set
 *
 * @param[in] num Number on which to evaluate the bit
 * @param[in] bit Bit to evaluate
 */
#define ARC_ASSERT_BIT_NOT_SET(num, bit) \
    ARC_ASSERT_GENERIC(arc_assert_bit_not_set((int)(num), (int)(bit)), \
                       num(bit) == 0, \
                       num(bit) == 1)
/**
 * @brief Asserts left and right floats are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 * @param[in] delta Floating point equality threshold
 */
#define ARC_ASSERT_FLOAT_EQUAL(left, right, delta) \
    ARC_ASSERT_GENERIC(arc_assert_float_equal((float)(left), \
                                              (float)(right), \
                                              (float)(delta)), \
                       left == right +/- delta, \
                       left != right +/- delta)
/**
 * @brief Asserts left and right doubles are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 * @param[in] delta Floating point equality threshold
 */
#define ARC_ASSERT_DOUBLE_EQUAL(left, right, delta) \
    ARC_ASSERT_GENERIC(arc_assert_double_equal((double)(left), \
                                              (double)(right), \
                                              (double)(delta)), \
                       left == right +/- delta, \
                       left != right +/- delta)
/**
 * @brief Asserts the string contains a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_CONTAINS(str, c) \
    ARC_ASSERT_GENERIC(arc_assert_string_contains((const char *)(str), \
                                                  (char)(c)), \
                       str contains c, \
                       str !contains c)
/**
 * @brief Asserts the string doesn't contain a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_DOESNT_CONTAIN(str, c) \
    ARC_ASSERT_GENERIC(arc_assert_string_doesnt_contain((const char *)(str), \
                                                  (char)(c)), \
                       str !contains c, \
                       str contains c)
/**
 * @brief Asserts the string starts with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_STARTS_WITH(str, c) \
    ARC_ASSERT_GENERIC(arc_assert_string_starts_with((const char *)(str), \
                                                  (char)(c)), \
                       str[first] == c, \
                       str[first] != c)
/**
 * @brief Asserts the string ends with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_ENDS_WITH(str, c) \
    ARC_ASSERT_GENERIC(arc_assert_string_ends_with((const char *)(str), \
                                                  (char)(c)), \
                       str[last] == c, \
                       str[last] != c)

/**
 * @brief Creates a test
 *
 * @param[in] name Name of the test
 */
#define ARC_TEST(name) void name(void)
/**
 * @brief Creates the test fixture
 */
#define ARC_TEST_FIXTURE() void arc_set_tests(void)
/**
 * @brief Adds a test to the fixture
 *
 * @param[in] name Name of the test
 */
#define ARC_ADD_TEST(name) arc_add_test(#name, name);
/**
 * @brief Adds a function to the fixture
 *
 * @param[in] name Name of the function
 */
#define ARC_ADD_FUNCTION(name) arc_add_function(name);
/**
 * @brief Runs the test fixture and prints a report
 */
#define ARC_RUN_TESTS() \
int main(void) \
{ \
    int retval = 0; \
    arc_set_system(); \
    arc_set_tests(); \
    retval = arc_run_fixture(); \
    arc_print_report(); \
    arc_cleanup(); \
    return retval; \
}

/* Internal test fixture functions */
void arc_add_test(const char * name, void (*fn)(void));
void arc_add_function(void (*fn)(void));

void arc_set_system(void);
void arc_set_tests(void);
int arc_run_fixture(void);
void arc_print_report(void);
void arc_cleanup(void);

void arc_set_test_failed(void);
void arc_set_test_passed(void);

/* Assertions */
int arc_assert_true(int exp);
int arc_assert_false(int exp);
int arc_assert_pointer_null(void * pointer);
int arc_assert_pointer_not_null(void * pointer);
int arc_assert_pointer_equal(void * left, void * right);
int arc_assert_int_equal(int left, int right);
int arc_assert_ulong_equal(unsigned long left, unsigned long right);
int arc_assert_string_equal(const char * left, const char * right);
int arc_assert_bit_set(unsigned num, int bit);
int arc_assert_bit_not_set(int num, int bit);
int arc_assert_float_equal(float left, float right, float delta);
int arc_assert_double_equal(double left, double right, double delta);
int arc_assert_string_contains(const char * str, char c);
int arc_assert_string_doesnt_contain(const char * str, char c);
int arc_assert_string_starts_with(const char * str, char c);
int arc_assert_string_ends_with(const char * str, char c);

#endif