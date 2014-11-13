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
    type0 _0 = (type0)(var0);\
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
    type0 _0 = (type0)(var0);\
    type1 _1 = (type1)(var1);\
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
    type0 _0 = (type0)(var0);\
    type1 _1 = (type1)(var1);\
    type2 _2 = (type2)(var2);\
    if (!function(_0, _1, _2)) \
    { \
        printf("\n%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("    Expected: " expected_fmt "\n", expected_var); \
        printf("    Obtained: " obtained_fmt "\n", obtained_var); \
        arc_unit_set_test_failed(); \
        if (critical) return; \
    } \
}

/* Operators */
int arc_unit_true(int exp);
int arc_unit_false(int exp);

int arc_unit_pointer_null(void * pointer);
int arc_unit_pointer_not_null(void * pointer);
int arc_unit_pointer_eq(void * left, void * right);

int arc_unit_int_eq(int left, int right);
int arc_unit_ulong_eq(unsigned long left, unsigned long right);
int arc_unit_float_eq(float left, float right, double delta);
int arc_unit_double_eq(double left, double right, double delta);

int arc_unit_int_ne(int left, int right);
int arc_unit_ulong_ne(unsigned long left, unsigned long right);
int arc_unit_float_ne(float left, float right, double delta);
int arc_unit_double_ne(double left, double right, double delta);

int arc_unit_int_lt(int left, int right);
int arc_unit_ulong_lt(unsigned long left, unsigned long right);
int arc_unit_float_lt(float left, float right, double delta);
int arc_unit_double_lt(double left, double right, double delta);

int arc_unit_int_le(int left, int right);
int arc_unit_ulong_le(unsigned long left, unsigned long right);
int arc_unit_float_le(float left, float right, double delta);
int arc_unit_double_le(double left, double right, double delta);

int arc_unit_int_gt(int left, int right);
int arc_unit_ulong_gt(unsigned long left, unsigned long right);
int arc_unit_float_gt(float left, float right, double delta);
int arc_unit_double_gt(double left, double right, double delta);

int arc_unit_int_ge(int left, int right);
int arc_unit_ulong_ge(unsigned long left, unsigned long right);
int arc_unit_float_ge(float left, float right, double delta);
int arc_unit_double_ge(double left, double right, double delta);

int arc_unit_bit_set(unsigned long num, int bit);
int arc_unit_bit_not_set(unsigned long num, int bit);

int arc_unit_string_eq(const char * left, const char * right);
int arc_unit_string_ne(const char * left, const char * right);
int arc_unit_string_contains(const char * str, char c);
int arc_unit_string_not_contain(const char * str, char c);
int arc_unit_string_starts(const char * str, char c);
int arc_unit_string_ends(const char * str, char c);

#ifdef __cplusplus
}
#endif

#endif