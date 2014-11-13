/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file unit_assert.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Unit test framework
 *
 * @see http://en.wikipedia.org/wiki/Unit_testing
 */

#ifndef ARC_UNIT_ASSERT_H_
#define ARC_UNIT_ASSERT_H_

#include <stdio.h>
#include <string.h>
#include <arc/test/unit_common.h>

#ifdef __cplusplus
extern "C"{
#endif 

/**
 * @brief Assertion which always fails
 */
#define ARC_ASSERT_FAIL() \
    ARC_UNIT_FAIL(1)
/**
 * @brief Asserts the expression is true
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_TRUE(exp) \
    ARC_UNIT_TRUE(exp, 1)
/**
 * @brief Asserts the expression is false
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_FALSE(exp) \
    ARC_UNIT_FALSE(exp, 1)
/**
 * @brief Asserts the expression is NULL
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_POINTER_NULL(exp) \
    ARC_UNIT_POINTER_NULL(exp, 1)
/**
 * @brief Asserts the expression is not NULL
 *
 * @param[in] exp Expression to evaluate
 */
#define ARC_ASSERT_POINTER_NOT_NULL(exp) \
    ARC_UNIT_POINTER_NOT_NULL(exp, 1)
/**
 * @brief Asserts left and right pointers are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_POINTER_EQ(left, right) \
    ARC_UNIT_POINTER_EQ(left, right, 1)
/**
 * @brief Asserts left and right integers are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_EQ(left, right) \
    ARC_UNIT_INT_EQ(left, right, 1)
/**
 * @brief Asserts left and right unsigned longs are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_EQ(left, right) \
    ARC_UNIT_ULONG_EQ(left, right, 1)
/**
 * @brief Asserts left and right floats are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_EQ(left, right, delta) \
    ARC_UNIT_FLOAT_EQ(left, right, delta, 1)
/**
 * @brief Asserts left and right doubles are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_EQ(left, right, delta) \
    ARC_UNIT_DOUBLE_EQ(left, right, delta, 1)
/**
 * @brief Asserts left and right integers are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_NE(left, right) \
    ARC_UNIT_INT_NE(left, right, 1)
/**
 * @brief Asserts left and right unsigned longs are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_NE(left, right) \
    ARC_UNIT_ULONG_NE(left, right, 1)
/**
 * @brief Asserts left and right floats are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_NE(left, right, delta) \
    ARC_UNIT_FLOAT_NE(left, right, delta, 1)
/**
 * @brief Asserts left and right doubles are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_NE(left, right, delta) \
    ARC_UNIT_DOUBLE_NE(left, right, delta, 1)
/**
 * @brief Asserts left integer is less than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_LT(left, right) \
    ARC_UNIT_INT_LT(left, right, 1)
/**
 * @brief Asserts left unsigned long is less than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_LT(left, right) \
    ARC_UNIT_ULONG_LT(left, right, 1)
/**
 * @brief Asserts left float is less than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_LT(left, right, delta) \
    ARC_UNIT_FLOAT_LT(left, right, delta, 1)
/**
 * @brief Asserts left double is less than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_LT(left, right, delta) \
    ARC_UNIT_DOUBLE_LT(left, right, delta, 1)

/**
 * @brief Asserts left integer is less or equal than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_LE(left, right) \
    ARC_UNIT_INT_LE(left, right, 1)
/**
 * @brief Asserts left unsigned long is less or equal than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_LE(left, right) \
    ARC_UNIT_ULONG_LE(left, right, 1)
/**
 * @brief Asserts left float is less or equal than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_LE(left, right, delta) \
    ARC_UNIT_FLOAT_LE(left, right, delta, 1)
/**
 * @brief Asserts left double is less or equal than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_LE(left, right, delta) \
    ARC_UNIT_DOUBLE_LE(left, right, delta, 1)
/**
 * @brief Asserts left integer is greater than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_GT(left, right) \
    ARC_UNIT_INT_GT(left, right, 1)
/**
 * @brief Asserts unsigned long integer is greaterthan right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_GT(left, right) \
    ARC_UNIT_ULONG_GT(left, right, 1)
/**
 * @brief Asserts float integer is greater than float integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_GT(left, right, delta) \
    ARC_UNIT_FLOAT_GT(left, right, delta, 1)
/**
 * @brief Asserts left double is greater than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_GT(left, right, delta) \
    ARC_UNIT_DOUBLE_GT(left, right, delta, 1)
/**
 * @brief Asserts left integer is greater or equal than right integer
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_INT_GE(left, right) \
    ARC_UNIT_INT_GE(left, right, 1)
/**
 * @brief Asserts left unsigned long is greater or equal than right unsigned long
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_ULONG_GE(left, right) \
    ARC_UNIT_ULONG_GE(left, right, 1)
/**
 * @brief Asserts left float is greater or equal than right float
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_FLOAT_GE(left, right, delta) \
    ARC_UNIT_FLOAT_GE(left, right, delta, 1)
/**
 * @brief Asserts left double is greater or equal than right double
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 * @param[in] delta Floating point comparison threshold
 */
#define ARC_ASSERT_DOUBLE_GE(left, right, delta) \
    ARC_UNIT_DOUBLE_GE(left, right, delta, 1)
/**
 * @brief Asserts left and right strings are equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_STRING_EQ(left, right) \
    ARC_UNIT_STRING_EQ(left, right, 1)
/**
 * @brief Asserts left and right strings are not equal
 *
 * @param[in] left Left value of the comparison
 * @param[in] right Right value of the comparison
 */
#define ARC_ASSERT_STRING_NE(left, right) \
    ARC_UNIT_STRING_NE(left, right, 1)
/**
 * @brief Asserts bit is set
 *
 * @param[in] num Number on which to evaluate the bit
 * @param[in] bit Bit to evaluate
 */
#define ARC_ASSERT_BIT_SET(num, bit) \
    ARC_UNIT_BIT_SET(num, bit, 1)
/**
 * @brief Asserts bit is not set
 *
 * @param[in] num Number on which to evaluate the bit
 * @param[in] bit Bit to evaluate
 */
#define ARC_ASSERT_BIT_NOT_SET(num, bit) \
    ARC_UNIT_BIT_NOT_SET(num, bit, 1)
/**
 * @brief Asserts the string contains a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_CONTAINS(str, c) \
    ARC_UNIT_STRING_CONTAINS(str, c, 1)
/**
 * @brief Asserts the string doesn't contain a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_NOT_CONTAIN(str, c) \
    ARC_UNIT_STRING_NOT_CONTAIN(str, c, 1)
/**
 * @brief Asserts the string starts with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_STARTS(str, c) \
    ARC_UNIT_STRING_STARTS(str, c, 1)
/**
 * @brief Asserts the string ends with a character
 *
 * @param[in] str String container
 * @param[in] c Character contained
 */
#define ARC_ASSERT_STRING_ENDS(str, c) \
    ARC_UNIT_STRING_ENDS(str, c, 1)

#ifdef __cplusplus
}
#endif

#endif