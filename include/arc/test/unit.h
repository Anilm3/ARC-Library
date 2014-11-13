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
#include <arc/test/unit_common.h>

#ifdef __cplusplus
extern "C"{
#endif 

/** @copydoc ARC_UNIT_FAIL */
#define ARC_ASSERT_FAIL() \
    ARC_UNIT_FAIL(1)

/** @copydoc ARC_UNIT_FAIL */
#define ARC_EXPECT_FAIL() \
    ARC_UNIT_FAIL(0)

/** @copydoc ARC_UNIT_TRUE */
#define ARC_ASSERT_TRUE(exp) \
    ARC_UNIT_TRUE(exp, 1)

/** @copydoc ARC_UNIT_TRUE */
#define ARC_EXPECT_TRUE(exp) \
    ARC_UNIT_TRUE(exp, 0)

/** @copydoc ARC_UNIT_FALSE */
#define ARC_ASSERT_FALSE(exp) \
    ARC_UNIT_FALSE(exp, 1)

/** @copydoc ARC_UNIT_FALSE */
#define ARC_EXPECT_FALSE(exp) \
    ARC_UNIT_FALSE(exp, 0)

/** @copydoc ARC_UNIT_POINTER_NULL */
#define ARC_ASSERT_POINTER_NULL(exp) \
    ARC_UNIT_POINTER_NULL(exp, 1)

/** @copydoc ARC_UNIT_POINTER_NULL */
#define ARC_EXPECT_POINTER_NULL(exp) \
    ARC_UNIT_POINTER_NULL(exp, 0)

/** @copydoc ARC_UNIT_POINTER_NOT_NULL */
#define ARC_ASSERT_POINTER_NOT_NULL(exp) \
    ARC_UNIT_POINTER_NOT_NULL(exp, 1)

/** @copydoc ARC_UNIT_POINTER_NOT_NULL */
#define ARC_EXPECT_POINTER_NOT_NULL(exp) \
    ARC_UNIT_POINTER_NOT_NULL(exp, 0)

/** @copydoc ARC_UNIT_POINTER_EQ */
#define ARC_ASSERT_POINTER_EQ(left, right) \
    ARC_UNIT_POINTER_EQ(left, right, 1)

/** @copydoc ARC_UNIT_POINTER_EQ */
#define ARC_EXPECT_POINTER_EQ(left, right) \
    ARC_UNIT_POINTER_EQ(left, right, 0)

/** @copydoc ARC_UNIT_INT_EQ */
#define ARC_ASSERT_INT_EQ(left, right) \
    ARC_UNIT_INT_EQ(left, right, 1)

/** @copydoc ARC_UNIT_INT_EQ */
#define ARC_EXPECT_INT_EQ(left, right) \
    ARC_UNIT_INT_EQ(left, right, 0)

/** @copydoc ARC_UNIT_ULONG_EQ */
#define ARC_ASSERT_ULONG_EQ(left, right) \
    ARC_UNIT_ULONG_EQ(left, right, 1)

/** @copydoc ARC_UNIT_ULONG_EQ */
#define ARC_EXPECT_ULONG_EQ(left, right) \
    ARC_UNIT_ULONG_EQ(left, right, 0)

/** @copydoc ARC_UNIT_FLOAT_EQ */
#define ARC_ASSERT_FLOAT_EQ(left, right, delta) \
    ARC_UNIT_FLOAT_EQ(left, right, delta, 1)

/** @copydoc ARC_UNIT_FLOAT_EQ */
#define ARC_EXPECT_FLOAT_EQ(left, right, delta) \
    ARC_UNIT_FLOAT_EQ(left, right, delta, 0)

/** @copydoc ARC_UNIT_DOUBLE_EQ */
#define ARC_ASSERT_DOUBLE_EQ(left, right, delta) \
    ARC_UNIT_DOUBLE_EQ(left, right, delta, 1)

/** @copydoc ARC_UNIT_DOUBLE_EQ */
#define ARC_EXPECT_DOUBLE_EQ(left, right, delta) \
    ARC_UNIT_DOUBLE_EQ(left, right, delta, 0)

/** @copydoc ARC_UNIT_INT_NE */
#define ARC_ASSERT_INT_NE(left, right) \
    ARC_UNIT_INT_NE(left, right, 1)

/** @copydoc ARC_UNIT_INT_NE */
#define ARC_EXPECT_INT_NE(left, right) \
    ARC_UNIT_INT_NE(left, right, 0)

/** @copydoc ARC_UNIT_ULONG_NE */
#define ARC_ASSERT_ULONG_NE(left, right) \
    ARC_UNIT_ULONG_NE(left, right, 1)

/** @copydoc ARC_UNIT_ULONG_NE */
#define ARC_EXPECT_ULONG_NE(left, right) \
    ARC_UNIT_ULONG_NE(left, right, 0)

/** @copydoc ARC_UNIT_FLOAT_NE */
#define ARC_ASSERT_FLOAT_NE(left, right, delta) \
    ARC_UNIT_FLOAT_NE(left, right, delta, 1)

/** @copydoc ARC_UNIT_FLOAT_NE */
#define ARC_EXPECT_FLOAT_NE(left, right, delta) \
    ARC_UNIT_FLOAT_NE(left, right, delta, 0)

/** @copydoc ARC_UNIT_DOUBLE_NE */
#define ARC_ASSERT_DOUBLE_NE(left, right, delta) \
    ARC_UNIT_DOUBLE_NE(left, right, delta, 1)

/** @copydoc ARC_UNIT_DOUBLE_NE */
#define ARC_EXPECT_DOUBLE_NE(left, right, delta) \
    ARC_UNIT_DOUBLE_NE(left, right, delta, 0)

/** @copydoc ARC_UNIT_INT_LT */
#define ARC_ASSERT_INT_LT(left, right) \
    ARC_UNIT_INT_LT(left, right, 1)

/** @copydoc ARC_UNIT_INT_LT */
#define ARC_EXPECT_INT_LT(left, right) \
    ARC_UNIT_INT_LT(left, right, 0)

/** @copydoc ARC_UNIT_ULONG_LT */
#define ARC_ASSERT_ULONG_LT(left, right) \
    ARC_UNIT_ULONG_LT(left, right, 1)

/** @copydoc ARC_UNIT_ULONG_LT */
#define ARC_EXPECT_ULONG_LT(left, right) \
    ARC_UNIT_ULONG_LT(left, right, 0)

/** @copydoc ARC_UNIT_FLOAT_LT */
#define ARC_ASSERT_FLOAT_LT(left, right, delta) \
    ARC_UNIT_FLOAT_LT(left, right, delta, 1)

/** @copydoc ARC_UNIT_FLOAT_LT */
#define ARC_EXPECT_FLOAT_LT(left, right, delta) \
    ARC_UNIT_FLOAT_LT(left, right, delta, 0)

/** @copydoc ARC_UNIT_DOUBLE_LT */
#define ARC_ASSERT_DOUBLE_LT(left, right, delta) \
    ARC_UNIT_DOUBLE_LT(left, right, delta, 1)

/** @copydoc ARC_UNIT_DOUBLE_LT */
#define ARC_EXPECT_DOUBLE_LT(left, right, delta) \
    ARC_UNIT_DOUBLE_LT(left, right, delta, 0)

/** @copydoc ARC_UNIT_INT_LE */
#define ARC_ASSERT_INT_LE(left, right) \
    ARC_UNIT_INT_LE(left, right, 1)

/** @copydoc ARC_UNIT_INT_LE */
#define ARC_EXPECT_INT_LE(left, right) \
    ARC_UNIT_INT_LE(left, right, 0)

/** @copydoc ARC_UNIT_ULONG_LE */
#define ARC_ASSERT_ULONG_LE(left, right) \
    ARC_UNIT_ULONG_LE(left, right, 1)

/** @copydoc ARC_UNIT_ULONG_LE */
#define ARC_EXPECT_ULONG_LE(left, right) \
    ARC_UNIT_ULONG_LE(left, right, 0)

/** @copydoc ARC_UNIT_FLOAT_LE */
#define ARC_ASSERT_FLOAT_LE(left, right, delta) \
    ARC_UNIT_FLOAT_LE(left, right, delta, 1)

/** @copydoc ARC_UNIT_FLOAT_LE */
#define ARC_EXPECT_FLOAT_LE(left, right, delta) \
    ARC_UNIT_FLOAT_LE(left, right, delta, 0)

/** @copydoc ARC_UNIT_DOUBLE_LE */
#define ARC_ASSERT_DOUBLE_LE(left, right, delta) \
    ARC_UNIT_DOUBLE_LE(left, right, delta, 1)

/** @copydoc ARC_UNIT_DOUBLE_LE */
#define ARC_EXPECT_DOUBLE_LE(left, right, delta) \
    ARC_UNIT_DOUBLE_LE(left, right, delta, 0)

/** @copydoc ARC_UNIT_INT_GT */
#define ARC_ASSERT_INT_GT(left, right) \
    ARC_UNIT_INT_GT(left, right, 1)

/** @copydoc ARC_UNIT_INT_GT */
#define ARC_EXPECT_INT_GT(left, right) \
    ARC_UNIT_INT_GT(left, right, 0)

/** @copydoc ARC_UNIT_ULONG_GT */
#define ARC_ASSERT_ULONG_GT(left, right) \
    ARC_UNIT_ULONG_GT(left, right, 1)

/** @copydoc ARC_UNIT_ULONG_GT */
#define ARC_EXPECT_ULONG_GT(left, right) \
    ARC_UNIT_ULONG_GT(left, right, 0)

/** @copydoc ARC_UNIT_FLOAT_GT */
#define ARC_ASSERT_FLOAT_GT(left, right, delta) \
    ARC_UNIT_FLOAT_GT(left, right, delta, 1)

/** @copydoc ARC_UNIT_FLOAT_GT */
#define ARC_EXPECT_FLOAT_GT(left, right, delta) \
    ARC_UNIT_FLOAT_GT(left, right, delta, 0)

/** @copydoc ARC_UNIT_DOUBLE_GT */
#define ARC_ASSERT_DOUBLE_GT(left, right, delta) \
    ARC_UNIT_DOUBLE_GT(left, right, delta, 1)

/** @copydoc ARC_UNIT_DOUBLE_GT */
#define ARC_EXPECT_DOUBLE_GT(left, right, delta) \
    ARC_UNIT_DOUBLE_GT(left, right, delta, 0)

/** @copydoc ARC_UNIT_INT_GE */
#define ARC_ASSERT_INT_GE(left, right) \
    ARC_UNIT_INT_GE(left, right, 1)

/** @copydoc ARC_UNIT_INT_GE */
#define ARC_EXPECT_INT_GE(left, right) \
    ARC_UNIT_INT_GE(left, right, 0)

/** @copydoc ARC_UNIT_ULONG_GE */
#define ARC_ASSERT_ULONG_GE(left, right) \
    ARC_UNIT_ULONG_GE(left, right, 1)

/** @copydoc ARC_UNIT_ULONG_GE */
#define ARC_EXPECT_ULONG_GE(left, right) \
    ARC_UNIT_ULONG_GE(left, right, 0)

/** @copydoc ARC_UNIT_FLOAT_GE */
#define ARC_ASSERT_FLOAT_GE(left, right, delta) \
    ARC_UNIT_FLOAT_GE(left, right, delta, 1)

/** @copydoc ARC_UNIT_FLOAT_GE */
#define ARC_EXPECT_FLOAT_GE(left, right, delta) \
    ARC_UNIT_FLOAT_GE(left, right, delta, 0)

/** @copydoc ARC_UNIT_DOUBLE_GE */
#define ARC_ASSERT_DOUBLE_GE(left, right, delta) \
    ARC_UNIT_DOUBLE_GE(left, right, delta, 1)

/** @copydoc ARC_UNIT_DOUBLE_GE */
#define ARC_EXPECT_DOUBLE_GE(left, right, delta) \
    ARC_UNIT_DOUBLE_GE(left, right, delta, 0)

/** @copydoc ARC_UNIT_STRING_EQ */
#define ARC_ASSERT_STRING_EQ(left, right) \
    ARC_UNIT_STRING_EQ(left, right, 1)

/** @copydoc ARC_UNIT_STRING_EQ */
#define ARC_EXPECT_STRING_EQ(left, right) \
    ARC_UNIT_STRING_EQ(left, right, 0)

/** @copydoc ARC_UNIT_STRING_NE */
#define ARC_ASSERT_STRING_NE(left, right) \
    ARC_UNIT_STRING_NE(left, right, 1)

/** @copydoc ARC_UNIT_STRING_NE */
#define ARC_EXPECT_STRING_NE(left, right) \
    ARC_UNIT_STRING_NE(left, right, 0)

/** @copydoc ARC_UNIT_BIT_SET */
#define ARC_ASSERT_BIT_SET(num, bit) \
    ARC_UNIT_BIT_SET(num, bit, 1)

/** @copydoc ARC_UNIT_BIT_SET */
#define ARC_EXPECT_BIT_SET(num, bit) \
    ARC_UNIT_BIT_SET(num, bit, 0)

/** @copydoc ARC_UNIT_BIT_NOT_SET */
#define ARC_ASSERT_BIT_NOT_SET(num, bit) \
    ARC_UNIT_BIT_NOT_SET(num, bit, 1)

/** @copydoc ARC_UNIT_BIT_NOT_SET */
#define ARC_EXPECT_BIT_NOT_SET(num, bit) \
    ARC_UNIT_BIT_NOT_SET(num, bit, 0)

/** @copydoc ARC_UNIT_STRING_CONTAINS */
#define ARC_ASSERT_STRING_CONTAINS(str, c) \
    ARC_UNIT_STRING_CONTAINS(str, c, 1)

/** @copydoc ARC_UNIT_STRING_CONTAINS */
#define ARC_EXPECT_STRING_CONTAINS(str, c) \
    ARC_UNIT_STRING_CONTAINS(str, c, 0)

/** @copydoc ARC_UNIT_STRING_NOT_CONTAIN */
#define ARC_ASSERT_STRING_NOT_CONTAIN(str, c) \
    ARC_UNIT_STRING_NOT_CONTAIN(str, c, 1)

/** @copydoc ARC_UNIT_STRING_NOT_CONTAIN */
#define ARC_EXPECT_STRING_NOT_CONTAIN(str, c) \
    ARC_UNIT_STRING_NOT_CONTAIN(str, c, 0)

/** @copydoc ARC_UNIT_STRING_STARTS */
#define ARC_ASSERT_STRING_STARTS(str, c) \
    ARC_UNIT_STRING_STARTS(str, c, 1)

/** @copydoc ARC_UNIT_STRING_STARTS */
#define ARC_EXPECT_STRING_STARTS(str, c) \
    ARC_UNIT_STRING_STARTS(str, c, 0)

/** @copydoc ARC_UNIT_STRING_ENDS */
#define ARC_ASSERT_STRING_ENDS(str, c) \
    ARC_UNIT_STRING_ENDS(str, c, 1)

/** @copydoc ARC_UNIT_STRING_ENDS */
#define ARC_EXPECT_STRING_ENDS(str, c) \
    ARC_UNIT_STRING_ENDS(str, c, 0)
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

#ifdef __cplusplus
}
#endif

#endif