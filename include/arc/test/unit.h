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
#include <arc/test/unit_assert.h>
#include <arc/test/unit_expect.h>

#ifdef __cplusplus
extern "C"{
#endif 

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