/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file perf.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Performance test framework
 */

#ifndef ARC_PERF_H_
#define ARC_PERF_H_

#include <stdio.h>
/**
 * @brief Creates a test
 *
 * @param[in] name Name of the test
 */
#define ARC_PERF_TEST(name) void name ## _ ## test(void)
/**
 * @brief Creates a function
 *
 * @param[in] name Name of the test
 */
#define ARC_PERF_FUNCTION(name) void name ## _ ## function(void)
/**
 * @brief Creates the test fixture
 */
#define ARC_PERF_TEST_FIXTURE() void arc_perf_set_tests(void)
/**
 * @brief Adds a test to the fixture
 *
 * @param[in] name Name of the test
 */
#define ARC_PERF_ADD_TEST(name) arc_perf_add_test(#name, name ## _ ## test);
/**
 * @brief Adds a function to the fixture
 *
 * @param[in] name Name of the function
 */
#define ARC_PERF_ADD_FUNCTION(name) arc_perf_add_function(name ## _ ## function);
/**
 * @brief Runs the test fixture and prints a report
 */
#define ARC_PERF_RUN_TESTS() \
int main(int argc, char * argv[]) \
{ \
    arc_perf_set_system(argc, argv); \
    arc_perf_set_tests(); \
    arc_perf_run_fixture(); \
    arc_perf_print_report(); \
    arc_perf_cleanup(); \
    return 0; \
}

/* Internal test fixture functions */
void arc_perf_add_test(const char * name, void (*fn)(void));
void arc_perf_add_function(void (*fn)(void));

void arc_perf_set_system(int argc, char * argv[]);
void arc_perf_set_tests(void);
void arc_perf_run_fixture(void);
void arc_perf_print_report(void);
void arc_perf_cleanup(void);

#endif