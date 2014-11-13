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
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_POINTER_EQ(left, right) \
    ARC_ASSERT_GEN2(arc_assert_pointer_eq, \
                    void *, left, \
                    void *, right, \
                    #left " == %p", _1, \
                    #left " == %p", _0)
/**
 * @brief Asserts left and right integers are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_EQ(left, right) \
    ARC_ASSERT_GEN2(arc_assert_int_eq, \
                    int, left, \
                    int, right, \
                    #left " == %d", _1, \
                    #left " == %d", _0)
/**
 * @brief Asserts left and right unsigned longs are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_EQ(left, right) \
    ARC_ASSERT_GEN2(arc_assert_ulong_eq, \
                    unsigned long, left, \
                    unsigned long, right, \
                    #left " == %lu", _1, \
                    #left " == %lu", _0)
/**
 * @brief Asserts left and right floats are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_EQ(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_float_eq, \
                    float, left, \
                    float, right, \
                    double, delta, \
                    #left " +/- " #delta " ~= %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left and right doubles are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_EQ(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_double_eq, \
                    double, left, \
                    double, right, \
                    double, delta, \
                    #left " +/- " #delta " ~= %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left and right integers are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_NE(left, right) \
    ARC_ASSERT_GEN2(arc_assert_int_ne, \
                    int, left, \
                    int, right, \
                    #left " != %d", _1, \
                    #left " == %d", _0)
/**
 * @brief Asserts left and right unsigned longs are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_NE(left, right) \
    ARC_ASSERT_GEN2(arc_assert_ulong_ne, \
                    unsigned long, left, \
                    unsigned long, right, \
                    #left " != %lu", _1, \
                    #left " == %lu", _0)
/**
 * @brief Asserts left and right floats are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_NE(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_float_ne, \
                    float, left, \
                    float, right, \
                    double, delta, \
                    #left " +/- " #delta " != %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left and right doubles are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_NE(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_double_ne, \
                    double, left, \
                    double, right, \
                    double, delta, \
                    #left " +/- " #delta " != %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left integer is less than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_LT(left, right) \
    ARC_ASSERT_GEN2(arc_assert_int_lt, \
                    int, left, \
                    int, right, \
                    #left " < %d", _1, \
                    #left " == %d", _0)
/**
 * @brief Asserts left unsigned long is less than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_LT(left, right) \
    ARC_ASSERT_GEN2(arc_assert_ulong_lt, \
                    unsigned long, left, \
                    unsigned long, right, \
                    #left " < %lu", _1, \
                    #left " == %lu", _0)
/**
 * @brief Asserts left float is less than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_LT(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_float_lt, \
                    float, left, \
                    float, right, \
                    double, delta, \
                    #left " +/- " #delta " < %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left double is less than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_LT(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_double_lt, \
                    double, left, \
                    double, right, \
                    double, delta, \
                    #left " +/- " #delta " < %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)

/**
 * @brief Asserts left integer is less or equal than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_LE(left, right) \
    ARC_ASSERT_GEN2(arc_assert_int_le, \
                    int, left, \
                    int, right, \
                    #left " <= %d", _1, \
                    #left " == %d", _0)
/**
 * @brief Asserts left unsigned long is less or equal than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_LE(left, right) \
    ARC_ASSERT_GEN2(arc_assert_ulong_le, \
                    unsigned long, left, \
                    unsigned long, right, \
                    #left " <= %lu", _1, \
                    #left " == %lu", _0)
/**
 * @brief Asserts left float is less or equal than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_LE(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_float_le, \
                    float, left, \
                    float, right, \
                    double, delta, \
                    #left " +/- " #delta " <= %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left double is less or equal than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_LE(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_double_le, \
                    double, left, \
                    double, right, \
                    double, delta, \
                    #left " +/- " #delta " <= %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left integer is greater than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_GT(left, right) \
    ARC_ASSERT_GEN2(arc_assert_int_gt, \
                    int, left, \
                    int, right, \
                    #left " > %d", _1, \
                    #left " == %d", _0)
/**
 * @brief Asserts unsigned long integer is greaterthan right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_GT(left, right) \
    ARC_ASSERT_GEN2(arc_assert_ulong_gt, \
                    unsigned long, left, \
                    unsigned long, right, \
                    #left " > %lu", _1, \
                    #left " == %lu", _0)
/**
 * @brief Asserts float integer is greater than float integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_GT(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_float_gt, \
                    float, left, \
                    float, right, \
                    double, delta, \
                    #left " +/- " #delta " > %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left double is greater than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_GT(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_double_gt, \
                    double, left, \
                    double, right, \
                    double, delta, \
                    #left " +/- " #delta " > %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)

/**
 * @brief Asserts left integer is greater or equal than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_GE(left, right) \
    ARC_ASSERT_GEN2(arc_assert_int_ge, \
                    int, left, \
                    int, right, \
                    #left " >= %d", _1, \
                    #left " == %d", _0)
/**
 * @brief Asserts left unsigned long is greater or equal than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_GE(left, right) \
    ARC_ASSERT_GEN2(arc_assert_ulong_ge, \
                    unsigned long, left, \
                    unsigned long, right, \
                    #left " >= %lu", _1, \
                    #left " == %lu", _0)
/**
 * @brief Asserts left float is greater or equal than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_GE(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_float_ge, \
                    float, left, \
                    float, right, \
                    double, delta, \
                    #left " +/- " #delta " >= %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left double is greater or equal than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_GE(left, right, delta) \
    ARC_ASSERT_GEN3(arc_assert_double_ge, \
                    double, left, \
                    double, right, \
                    double, delta, \
                    #left " +/- " #delta " >= %f", _1, \
                    #left " +/- " #delta " ~= %f", _0)
/**
 * @brief Asserts left and right strings are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_STRING_EQ(left, right) \
    ARC_ASSERT_GEN2(arc_assert_string_eq, \
                    const char *, left, \
                    const char *, right, \
                    #left " == %s", _1, \
                    #left " == %s", _0)
/**
 * @brief Asserts left and right strings are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_STRING_NE(left, right) \
    ARC_ASSERT_GEN2(arc_assert_string_ne, \
                    const char *, left, \
                    const char *, right, \
                    #left " != %s", _1, \
                    #left " == %s", _0)
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
                    #num "(" #bit ") == %d", 0)
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
                    #num "(" #bit ") == %d", 1)
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
                    #str " !contain %c", _1)
/**
 * @brief Asserts the string doesn't contain a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_NOT_CONTAIN(str, c) \
    ARC_ASSERT_GEN2(arc_assert_string_not_contain, \
                    const char *, str, \
                    char, c, \
                    #str " !contain %c", _1, \
                    #str " contain %c", _1)
/**
 * @brief Asserts the string starts with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_STARTS(str, c) \
    ARC_ASSERT_GEN2(arc_assert_string_starts, \
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
#define ARC_ASSERT_STRING_ENDS(str, c) \
    ARC_ASSERT_GEN2(arc_assert_string_ends, \
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
int main(int argc, char *argv[]) \
{ \
    arc_unit_init(argc, argv); \
    arc_unit_set_tests(); \
    return arc_unit_run(); \
}

/* Internal test fixture functions */
void arc_unit_add_test(const char * name, void (*fn)(void));
void arc_unit_add_function(void (*fn)(void));

void arc_unit_init(int argc, char *argv[]);
void arc_unit_set_tests(void);
int arc_unit_run(void);

void arc_unit_set_test_failed(void);

/* Assertions */
int arc_assert_true(int exp);
int arc_assert_false(int exp);

int arc_assert_pointer_null(void * pointer);
int arc_assert_pointer_not_null(void * pointer);
int arc_assert_pointer_eq(void * left, void * right);

int arc_assert_int_eq(int left, int right);
int arc_assert_ulong_eq(unsigned long left, unsigned long right);
int arc_assert_float_eq(float left, float right, double delta);
int arc_assert_double_eq(double left, double right, double delta);

int arc_assert_int_ne(int left, int right);
int arc_assert_ulong_ne(unsigned long left, unsigned long right);
int arc_assert_float_ne(float left, float right, double delta);
int arc_assert_double_ne(double left, double right, double delta);

int arc_assert_int_lt(int left, int right);
int arc_assert_ulong_lt(unsigned long left, unsigned long right);
int arc_assert_float_lt(float left, float right, double delta);
int arc_assert_double_lt(double left, double right, double delta);

int arc_assert_int_le(int left, int right);
int arc_assert_ulong_le(unsigned long left, unsigned long right);
int arc_assert_float_le(float left, float right, double delta);
int arc_assert_double_le(double left, double right, double delta);

int arc_assert_int_gt(int left, int right);
int arc_assert_ulong_gt(unsigned long left, unsigned long right);
int arc_assert_float_gt(float left, float right, double delta);
int arc_assert_double_gt(double left, double right, double delta);

int arc_assert_int_ge(int left, int right);
int arc_assert_ulong_ge(unsigned long left, unsigned long right);
int arc_assert_float_ge(float left, float right, double delta);
int arc_assert_double_ge(double left, double right, double delta);

int arc_assert_bit_set(unsigned long num, int bit);
int arc_assert_bit_not_set(unsigned long num, int bit);

int arc_assert_string_eq(const char * left, const char * right);
int arc_assert_string_ne(const char * left, const char * right);
int arc_assert_string_contains(const char * str, char c);
int arc_assert_string_not_contain(const char * str, char c);
int arc_assert_string_starts(const char * str, char c);
int arc_assert_string_ends(const char * str, char c);

#ifdef __cplusplus
}
#endif

#endif