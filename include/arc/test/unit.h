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
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif 

/**
 * @brief Generic assertion expecting a function with 0 parameters
 *
 * @param[in] function Function to evaluate
 * @param[in] expected_fmt Expected format to print
 * @param[in] expected_var Expected variable to print
 * @param[in] obtained_fmt Obtained format to print
 * @param[in] obtained_var Obtained variable to print
 */
#define ARC_ASSERT_GEN0(function, \
                        expected_fmt, expected_var, \
                        obtained_fmt, obtained_var) \
{ \
    if (!function()) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        return; \
    } \
}
/**
 * @brief Generic assertion expecting a function with 1 parameters
 *
 * @param[in] function Function to evaluate
 * @param[in] type0 Type of variable 0
 * @param[in] var0 Variable number 0 to be used with the function
 * @param[in] expected_fmt Expected format to print
 * @param[in] expected_var Expected variable to print
 * @param[in] obtained_fmt Obtained format to print
 * @param[in] obtained_var Obtained variable to print
 */
#define ARC_ASSERT_GEN1(function, \
                        type0, var0, \
                        expected_fmt, expected_var, \
                        obtained_fmt, obtained_var) \
{ \
    type0 _0 = (type0)(var0);\
    if (!function(_0)) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        return; \
    } \
}
/**
 * @brief Generic assertion expecting a function with 2 parameters
 *
 * @param[in] function Function to evaluate
 * @param[in] type0 Type of variable 0
 * @param[in] var0 Variable number 0 to be used with the function
 * @param[in] type1 Type of variable 1
 * @param[in] var1 Variable number 1 to be used with the function
 * @param[in] expected_fmt Expected format to print
 * @param[in] expected_var Expected variable to print
 * @param[in] obtained_fmt Obtained format to print
 * @param[in] obtained_var Obtained variable to print
 */
#define ARC_ASSERT_GEN2(function, \
                        type0, var0, \
                        type1, var1, \
                        expected_fmt, expected_var, \
                        obtained_fmt, obtained_var) \
{ \
    type0 _0 = (type0)(var0);\
    type1 _1 = (type1)(var1);\
    if (!function(_0, _1)) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        return; \
    } \
}
/**
 * @brief Generic assertion expecting a function with 3 parameters
 *
 * @param[in] function Function to evaluate
 * @param[in] type0 Type of variable 0
 * @param[in] var0 Variable number 0 to be used with the function
 * @param[in] type1 Type of variable 1
 * @param[in] var1 Variable number 1 to be used with the function
 * @param[in] type2 Type of variable 2
 * @param[in] var2 Variable number 2 to be used with the function
 * @param[in] expected_fmt Expected format to print
 * @param[in] expected_var Expected variable to print
 * @param[in] obtained_fmt Obtained format to print
 * @param[in] obtained_var Obtained variable to print
 */
#define ARC_ASSERT_GEN3(function, \
                        type0, var0, \
                        type1, var1, \
                        type2, var2, \
                        expected_fmt, expected_var, \
                        obtained_fmt, obtained_var) \
{ \
    type0 _0 = (type0)(var0);\
    type1 _1 = (type1)(var1);\
    type2 _2 = (type2)(var2);\
    if (!function(_0, _1, _2)) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        return; \
    } \
}
/**
 * @brief Assertion which always fails
 */
#define ARC_ASSERT_FAIL() \
    printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
    arc_unit_set_test_failed(); \
    return;
/**
 * @brief Asserts the expression is true
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_TRUE(exp) \
    ARC_ASSERT_GEN1(arc_assert_true, \
                    int, exp, \
                    #exp " == %d", 1, \
                    #exp " == %d", 0) 
/**
 * @brief Asserts the expression is false
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_FALSE(exp) \
    ARC_ASSERT_GEN1(arc_assert_false, \
                    int, exp, \
                    #exp " == %d", 0, \
                    #exp " == %d", 1) 
/**
 * @brief Asserts the expression is NULL
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_POINTER_NULL(exp) \
    ARC_ASSERT_GEN1(arc_assert_pointer_null, \
                    void *, exp, \
                    #exp " == %s", "NULL", \
                    #exp " == %p", _0) 
/**
 * @brief Asserts the expression is not NULL
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_POINTER_NOT_NULL(exp) \
    ARC_ASSERT_GEN1(arc_assert_pointer_not_null, \
                    void *, exp, \
                    #exp " != %s", "NULL", \
                    #exp " == %s", "NULL") 
/**
 * @brief Asserts left and right pointers are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 */
#define ARC_ASSERT_POINTER_EQUAL(left, right) \
    ARC_ASSERT_GEN2(arc_assert_pointer_equal, \
                    void *, left, \
                    void *, right, \
                    #left " == %p", _1, \
                    #left " == %p", _0) \
/**
 * @brief Asserts left and right integers are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 */
#define ARC_ASSERT_INT_EQUAL(left, right) \
    ARC_ASSERT_GEN2(arc_assert_int_equal, \
                    int, left, \
                    int, right, \
                    #left " == %d", _1, \
                    #left " == %d", _0) \
/**
 * @brief Asserts left and right unsigned longs are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 */
#define ARC_ASSERT_ULONG_EQUAL(left, right) \
    ARC_ASSERT_GEN2(arc_assert_ulong_equal, \
                    unsigned long, left, \
                    unsigned long, right, \
                    #left " == %lu", _1, \
                    #left " == %lu", _0) \
/**
 * @brief Asserts left and right strings are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 */
#define ARC_ASSERT_STRING_EQUAL(left, right) \
    ARC_ASSERT_GEN2(arc_assert_string_equal, \
                    const char *, left, \
                    const char *, right, \
                    #left " == %s", _1, \
                    #left " == %s", _0) \
/**
 * @brief Asserts bit is set
 *
 * @param[in] num Number on which to evaluate the bit
 * @param[in] bit Bit to evaluate
 */
#define ARC_ASSERT_BIT_SET(num, bit) \
    ARC_ASSERT_GEN2(arc_assert_bit_set, \
                    unsigned long, num, \
                    int, bit, \
                    #num "(" #bit ") == %d", 1, \
                    #num "(" #bit ") == %d", 0) \
/**
 * @brief Asserts bit is not set
 *
 * @param[in] num Number on which to evaluate the bit
 * @param[in] bit Bit to evaluate
 */
#define ARC_ASSERT_BIT_NOT_SET(num, bit) \
    ARC_ASSERT_GEN2(arc_assert_bit_not_set, \
                    unsigned long, num, \
                    int, bit, \
                    #num "(" #bit ") == %d", 0, \
                    #num "(" #bit ") == %d", 1) \
/**
 * @brief Asserts left and right floats are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 * @param[in] delta Floating point equality threshold
 */
#define ARC_ASSERT_FLOAT_EQUAL(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_float_equal, \
                    float, left, \
                    float, right, \
                    double, delta, \
                    #left " +/- " #delta " ~= %f", _1, \
                    #left " +/- " #delta " ~= %f", _0) \
/**
 * @brief Asserts left and right doubles are equal
 *
 * @param[in] left Left value of the equality
 * @param[in] right Right value of the equality
 * @param[in] delta Floating point equality threshold
 */
#define ARC_ASSERT_DOUBLE_EQUAL(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_double_equal, \
                    double, left, \
                    double, right, \
                    double, delta, \
                    #left " +/- " #delta " ~= %f", _1, \
                    #left " +/- " #delta " ~= %f", _0) \
/**
 * @brief Asserts the string contains a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_CONTAINS(str, c) \
    ARC_ASSERT_GEN2(arc_assert_string_contains, \
                    const char *, str, \
                    char, c, \
                    #str " contain %c", _1, \
                    #str " !contain %c", _1) \
/**
 * @brief Asserts the string doesn't contain a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_DOESNT_CONTAIN(str, c) \
    ARC_ASSERT_GEN2(arc_assert_string_doesnt_contain, \
                    const char *, str, \
                    char, c, \
                    #str " !contain %c", _1, \
                    #str " contain %c", _1) \
/**
 * @brief Asserts the string starts with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_STARTS_WITH(str, c) \
    ARC_ASSERT_GEN2(arc_assert_string_starts_with, \
                    const char *, str, \
                    char, c, \
                    #str"[0] == %c", _1, \
                    #str"[0] == %c", (char)((str)[0])) 
/**
 * @brief Asserts the string ends with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_ENDS_WITH(str, c) \
    ARC_ASSERT_GEN2(arc_assert_string_ends_with, \
                    const char *, str, \
                    char, c, \
                    #str"[last] == %c", _1, \
                    #str"[last] == %c", (char)((str)[strlen(str) - 1]))
/**
 * @brief Creates a test
 *
 * @param[in] name Name of the test
 */
#define ARC_UNIT_TEST(name) void name ## _ ## test(void)
/**
 * @brief Creates a function
 *
 * @param[in] name Name of the test
 */
#define ARC_UNIT_FUNCTION(name) void name ## _ ## function(void)
/**
 * @brief Creates the test fixture
 */
#define ARC_UNIT_TEST_FIXTURE() void arc_unit_set_tests(void)
/**
 * @brief Adds a test to the fixture
 *
 * @param[in] name Name of the test
 */
#define ARC_UNIT_ADD_TEST(name) arc_unit_add_test(#name, name ## _ ## test);
/**
 * @brief Adds a function to the fixture
 *
 * @param[in] name Name of the function
 */
#define ARC_UNIT_ADD_FUNCTION(name) arc_unit_add_function(name ## _ ## function);
/**
 * @brief Runs the test fixture and prints a report
 */
#define ARC_UNIT_RUN_TESTS() \
int main(void) \
{ \
    int retval = 0; \
    arc_unit_set_system(); \
    arc_unit_set_tests(); \
    retval = arc_unit_run_fixture(); \
    arc_unit_print_report(); \
    arc_unit_cleanup(); \
    return retval; \
}

/* Internal test fixture functions */
void arc_unit_add_test(const char * name, void (*fn)(void));
void arc_unit_add_function(void (*fn)(void));

void arc_unit_set_system(void);
void arc_unit_set_tests(void);
int arc_unit_run_fixture(void);
void arc_unit_print_report(void);
void arc_unit_cleanup(void);

void arc_unit_set_test_failed(void);
void arc_unit_set_test_passed(void);

/* Assertions */
int arc_assert_true(int exp);
int arc_assert_false(int exp);
int arc_assert_pointer_null(void * pointer);
int arc_assert_pointer_not_null(void * pointer);
int arc_assert_pointer_equal(void * left, void * right);
int arc_assert_int_equal(int left, int right);
int arc_assert_ulong_equal(unsigned long left, unsigned long right);
int arc_assert_string_equal(const char * left, const char * right);
int arc_assert_bit_set(unsigned long num, int bit);
int arc_assert_bit_not_set(unsigned long num, int bit);
int arc_assert_float_equal(float left, float right, double delta);
int arc_assert_double_equal(double left, double right, double delta);
int arc_assert_string_contains(const char * str, char c);
int arc_assert_string_doesnt_contain(const char * str, char c);
int arc_assert_string_starts_with(const char * str, char c);
int arc_assert_string_ends_with(const char * str, char c);

#ifdef __cplusplus
}
#endif

#endif