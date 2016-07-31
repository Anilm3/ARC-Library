/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup Unit_Common
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 * @ingroup Test
 *
 * @brief Unit test framework
 *
 * @see http://en.wikipedia.org/wiki/Unit_testing
 */

#ifndef ARC_UNIT_COMMON_H_
#define ARC_UNIT_COMMON_H_

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
#define ARC_UNIT_GEN0(function, \
                        expected_fmt, expected_var, \
                        obtained_fmt, obtained_var, \
                        critical) \
{ \
    if (!function()) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        if (critical) return; \
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
#define ARC_UNIT_GEN1(function, \
                      type0, var0, \
                      expected_fmt, expected_var, \
                      obtained_fmt, obtained_var, \
                      critical) \
{ \
    const type0 _0 = (const type0)(var0);\
    if (!function(_0)) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        if (critical) return; \
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
#define ARC_UNIT_GEN2(function, \
                      type0, var0, \
                      type1, var1, \
                      expected_fmt, expected_var, \
                      obtained_fmt, obtained_var, \
                      critical) \
{ \
    const type0 _0 = (const type0)(var0);\
    const type1 _1 = (const type1)(var1);\
    if (!function(_0, _1)) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        if (critical) return; \
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
#define ARC_UNIT_GEN3(function, \
                      type0, var0, \
                      type1, var1, \
                      type2, var2, \
                      expected_fmt, expected_var, \
                      obtained_fmt, obtained_var, \
                      critical) \
{ \
    const type0 _0 = (const type0)(var0);\
    const type1 _1 = (const type1)(var1);\
    const type2 _2 = (const type2)(var2);\
    if (!function(_0, _1, _2)) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        if (critical) return; \
    } \
}

/**
 * @brief Assertion which always fails
 */
#define ARC_UNIT_FAIL(critical) \
    printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
    arc_unit_set_test_failed(); \
    if (critical) return;
/**
 * @brief Asserts the expression is true
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_UNIT_TRUE(exp, critical) \
    ARC_UNIT_GEN1(arc_unit_true, \
                  int, exp, \
                  #exp " == %d", 1, \
                  #exp " == %d", 0, \
                  critical)
/**
 * @brief Asserts the expression is false
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_UNIT_FALSE(exp, critical) \
    ARC_UNIT_GEN1(arc_unit_false, \
                  int, exp, \
                  #exp " == %d", 0, \
                  #exp " == %d", 1, \
                  critical)
/**
 * @brief Asserts the expression is NULL
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_UNIT_POINTER_NULL(exp, critical) \
    ARC_UNIT_GEN1(arc_unit_pointer_null, \
                  void *, exp, \
                  #exp " == %s", "NULL", \
                  #exp " == %p", _0, \
                  critical)
/**
 * @brief Asserts the expression is not NULL
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_UNIT_POINTER_NOT_NULL(exp, critical) \
    ARC_UNIT_GEN1(arc_unit_pointer_not_null, \
                  void *, exp, \
                  #exp " != %s", "NULL", \
                  #exp " == %s", "NULL", \
                  critical)
/**
 * @brief Asserts left and right pointers are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_POINTER_EQ(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_pointer_eq, \
                  void *, left, \
                  void *, right, \
                  #left " == %p", _1, \
                  #left " == %p", _0, \
                  critical)
/**
 * @brief Asserts left and right integers are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_INT_EQ(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_int_eq, \
                  int, left, \
                  int, right, \
                  #left " == %d", _1, \
                  #left " == %d", _0, \
                  critical)
/**
 * @brief Asserts left and right unsigned longs are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_ULONG_EQ(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_ulong_eq, \
                  unsigned long, left, \
                  unsigned long, right, \
                  #left " == %lu", _1, \
                  #left " == %lu", _0, \
                  critical)
/**
 * @brief Asserts left and right floats are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_FLOAT_EQ(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_float_eq, \
                  float, left, \
                  float, right, \
                  double, delta, \
                  #left " +/- " #delta " ~= %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left and right doubles are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_DOUBLE_EQ(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_double_eq, \
                  double, left, \
                  double, right, \
                  double, delta, \
                  #left " +/- " #delta " ~= %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left and right integers are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_INT_NE(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_int_ne, \
                  int, left, \
                  int, right, \
                  #left " != %d", _1, \
                  #left " == %d", _0, \
                  critical)
/**
 * @brief Asserts left and right unsigned longs are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_ULONG_NE(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_ulong_ne, \
                  unsigned long, left, \
                  unsigned long, right, \
                  #left " != %lu", _1, \
                  #left " == %lu", _0, \
                  critical)
/**
 * @brief Asserts left and right floats are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_FLOAT_NE(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_float_ne, \
                  float, left, \
                  float, right, \
                  double, delta, \
                  #left " +/- " #delta " != %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left and right doubles are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_DOUBLE_NE(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_double_ne, \
                  double, left, \
                  double, right, \
                  double, delta, \
                  #left " +/- " #delta " != %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left integer is less than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_INT_LT(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_int_lt, \
                  int, left, \
                  int, right, \
                  #left " < %d", _1, \
                  #left " == %d", _0, \
                  critical)
/**
 * @brief Asserts left unsigned long is less than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_ULONG_LT(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_ulong_lt, \
                  unsigned long, left, \
                  unsigned long, right, \
                  #left " < %lu", _1, \
                  #left " == %lu", _0, \
                  critical)
/**
 * @brief Asserts left float is less than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_FLOAT_LT(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_float_lt, \
                  float, left, \
                  float, right, \
                  double, delta, \
                  #left " +/- " #delta " < %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left double is less than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_DOUBLE_LT(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_double_lt, \
                  double, left, \
                  double, right, \
                  double, delta, \
                  #left " +/- " #delta " < %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)

/**
 * @brief Asserts left integer is less or equal than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_INT_LE(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_int_le, \
                  int, left, \
                  int, right, \
                  #left " <= %d", _1, \
                  #left " == %d", _0, \
                  critical)
/**
 * @brief Asserts left unsigned long is less or equal than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_ULONG_LE(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_ulong_le, \
                  unsigned long, left, \
                  unsigned long, right, \
                  #left " <= %lu", _1, \
                  #left " == %lu", _0, \
                  critical)
/**
 * @brief Asserts left float is less or equal than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_FLOAT_LE(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_float_le, \
                  float, left, \
                  float, right, \
                  double, delta, \
                  #left " +/- " #delta " <= %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left double is less or equal than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_DOUBLE_LE(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_double_le, \
                  double, left, \
                  double, right, \
                  double, delta, \
                  #left " +/- " #delta " <= %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left integer is greater than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_INT_GT(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_int_gt, \
                  int, left, \
                  int, right, \
                  #left " > %d", _1, \
                  #left " == %d", _0, \
                  critical)
/**
 * @brief Asserts unsigned long integer is greaterthan right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_ULONG_GT(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_ulong_gt, \
                  unsigned long, left, \
                  unsigned long, right, \
                  #left " > %lu", _1, \
                  #left " == %lu", _0, \
                  critical)
/**
 * @brief Asserts float integer is greater than float integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_FLOAT_GT(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_float_gt, \
                  float, left, \
                  float, right, \
                  double, delta, \
                  #left " +/- " #delta " > %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left double is greater than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_DOUBLE_GT(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_double_gt, \
                  double, left, \
                  double, right, \
                  double, delta, \
                  #left " +/- " #delta " > %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)

/**
 * @brief Asserts left integer is greater or equal than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_INT_GE(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_int_ge, \
                  int, left, \
                  int, right, \
                  #left " >= %d", _1, \
                  #left " == %d", _0, \
                  critical)
/**
 * @brief Asserts left unsigned long is greater or equal than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_ULONG_GE(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_ulong_ge, \
                  unsigned long, left, \
                  unsigned long, right, \
                  #left " >= %lu", _1, \
                  #left " == %lu", _0, \
                  critical)
/**
 * @brief Asserts left float is greater or equal than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_FLOAT_GE(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_float_ge, \
                  float, left, \
                  float, right, \
                  double, delta, \
                  #left " +/- " #delta " >= %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts left double is greater or equal than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_UNIT_DOUBLE_GE(left, right, delta, critical) \
    ARC_UNIT_GEN3(arc_unit_double_ge, \
                  double, left, \
                  double, right, \
                  double, delta, \
                  #left " +/- " #delta " >= %f", _1, \
                  #left " +/- " #delta " ~= %f", _0, \
                  critical)
/**
 * @brief Asserts bit is set
 *
 * @param[in] num Number on which to evaluate the bit
 * @param[in] bit Bit to evaluate
 */
#define ARC_UNIT_BIT_SET(num, bit, critical) \
    ARC_UNIT_GEN2(arc_unit_bit_set, \
                  unsigned long, num, \
                  int, bit, \
                  #num "(" #bit ") == %d", 1, \
                  #num "(" #bit ") == %d", 0, \
                  critical)
/**
 * @brief Asserts bit is not set
 *
 * @param[in] num Number on which to evaluate the bit
 * @param[in] bit Bit to evaluate
 */
#define ARC_UNIT_BIT_NOT_SET(num, bit, critical) \
    ARC_UNIT_GEN2(arc_unit_bit_not_set, \
                  unsigned long, num, \
                  int, bit, \
                  #num "(" #bit ") == %d", 0, \
                  #num "(" #bit ") == %d", 1, \
                  critical)
/**
 * @brief Asserts left and right strings are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_STRING_EQ(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_string_eq, \
                  char *, left, \
                  char *, right, \
                  #left " == %s", _1, \
                  #left " == %s", _0, \
                  critical)
/**
 * @brief Asserts left and right strings are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_UNIT_STRING_NE(left, right, critical) \
    ARC_UNIT_GEN2(arc_unit_string_ne, \
                  char *, left, \
                  char *, right, \
                  #left " != %s", _1, \
                  #left " == %s", _0, \
                  critical)
/**
 * @brief Asserts the string contains a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_UNIT_STRING_CONTAINS(str, c, critical) \
    ARC_UNIT_GEN2(arc_unit_string_contains, \
                  char *, str, \
                  char, c, \
                  #str " contain %c", _1, \
                  #str " !contain %c", _1, \
                  critical)
/**
 * @brief Asserts the string doesn't contain a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_UNIT_STRING_NOT_CONTAIN(str, c, critical) \
    ARC_UNIT_GEN2(arc_unit_string_not_contain, \
                  char *, str, \
                  char, c, \
                  #str " !contain %c", _1, \
                  #str " contain %c", _1, \
                  critical)
/**
 * @brief Asserts the string starts with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_UNIT_STRING_STARTS(str, c, critical) \
    ARC_UNIT_GEN2(arc_unit_string_starts, \
                  char *, str, \
                  char, c, \
                  #str"[0] == %c", _1, \
                  #str"[0] == %c", (char)((str)[0]), \
                  critical)
/**
 * @brief Asserts the string ends with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_UNIT_STRING_ENDS(str, c, critical) \
    ARC_UNIT_GEN2(arc_unit_string_ends, \
                  char *, str, \
                  char, c, \
                  #str"[last] == %c", _1, \
                  #str"[last] == %c", (char)((str)[strlen(str) - 1]), \
                  critical)

/* Operators */
int arc_unit_true(const int exp);
int arc_unit_false(const int exp);

int arc_unit_pointer_null(const void * pointer);
int arc_unit_pointer_not_null(const void * pointer);
int arc_unit_pointer_eq(const void * left, const void * right);

int arc_unit_int_eq(const int left, const int right);
int arc_unit_ulong_eq(const unsigned long left, const unsigned long right);
int arc_unit_float_eq(const float left, const float right, const double delta);
int arc_unit_double_eq(const double left, const double right, const double delta);

int arc_unit_int_ne(const int left, const int right);
int arc_unit_ulong_ne(const unsigned long left, const unsigned long right);
int arc_unit_float_ne(const float left, const float right, const double delta);
int arc_unit_double_ne(const double left, const double right, const double delta);

int arc_unit_int_lt(const int left, const int right);
int arc_unit_ulong_lt(const unsigned long left, const unsigned long right);
int arc_unit_float_lt(const float left, const float right, const double delta);
int arc_unit_double_lt(const double left, const double right, const double delta);

int arc_unit_int_le(const int left, const int right);
int arc_unit_ulong_le(const unsigned long left, const unsigned long right);
int arc_unit_float_le(const float left, const float right, const double delta);
int arc_unit_double_le(const double left, const double right, const double delta);

int arc_unit_int_gt(const int left, const int right);
int arc_unit_ulong_gt(const unsigned long left, const unsigned long right);
int arc_unit_float_gt(const float left, const float right, const double delta);
int arc_unit_double_gt(const double left, const double right, const double delta);

int arc_unit_int_ge(const int left, const int right);
int arc_unit_ulong_ge(const unsigned long left, const unsigned long right);
int arc_unit_float_ge(const float left, const float right, const double delta);
int arc_unit_double_ge(const double left, const double right, const double delta);

int arc_unit_bit_set(const unsigned long num, const int bit);
int arc_unit_bit_not_set(const unsigned long num, const int bit);

int arc_unit_string_eq(const char * left, const char * right);
int arc_unit_string_ne(const char * left, const char * right);
int arc_unit_string_contains(const char * str, const char c);
int arc_unit_string_not_contain(const char * str, const char c);
int arc_unit_string_starts(const char * str, const char c);
int arc_unit_string_ends(const char * str, const char c);

void arc_unit_add_test(const char * name, void (*fn)(void));
void arc_unit_add_function(void (*fn)(void));

void arc_unit_init(int argc, char *argv[]);
void arc_unit_set_tests(void);
int arc_unit_run(void);

void arc_unit_set_test_failed(void);

#ifdef __cplusplus
}
#endif

#endif /* ARC_UNIT_COMMON_H_ */

/** @} */
