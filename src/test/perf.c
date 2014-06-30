/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include <arc/test/perf.h>

typedef struct
{
    const char * name;
    void (* function)(void);
    double test_time;
    double * all_times;
    int test;
} arc_test_t;

static int coverage = 0;
static unsigned idx = 0;
static unsigned length = 0;
static unsigned max_length = 256;
static size_t max_str_size = 0;
static unsigned num_tests = 1;
static arc_test_t * arc_user_tests;

/******************************************************************************/

void arc_perf_add_test(const char * name, void (*fn)(void))
{
    size_t name_size = strlen(name);
    arc_test_t test;

    test.name = name;
    test.function = fn;
    test.test_time = 0;
    test.test = 1;

    if (coverage)
    {
        test.all_times = malloc(sizeof(double)*num_tests);
    }
    else
    {
        test.all_times = NULL;
    }

    if (name_size > max_str_size)
    {
        max_str_size = name_size;
    }

    if (idx < max_length)
    {
        arc_user_tests[idx++] = test;
    }
    else
    {
        arc_test_t * ptr;

        max_length += 256;
        ptr = realloc(arc_user_tests, sizeof(arc_test_t)*max_length);

        assert(ptr != NULL);

        arc_user_tests[idx++] = test;
    }
}

/******************************************************************************/

void arc_perf_add_function(void (*fn)(void))
{
    arc_test_t test;

    test.name = "";
    test.function = fn;
    test.test_time = 0;
    test.test = 0;

    if (idx < max_length)
    {
        arc_user_tests[idx++] = test;
    }
    else
    {
        arc_test_t * ptr;

        max_length += 256;
        ptr = realloc(arc_user_tests, sizeof(arc_test_t)*max_length);

        assert(ptr != NULL);

        arc_user_tests[idx++] = test;
    }
}

/******************************************************************************/

void arc_perf_set_system(int argc, char * argv[])
{
    int i;
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0 && argc > (i + 1))
        {
            num_tests = (unsigned)atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-c") == 0 && argc > (i + 1))
        {
            coverage = 1;
        }
    }
    arc_user_tests = malloc(sizeof(arc_test_t)*max_length);

    assert(arc_user_tests != NULL);
}

/******************************************************************************/

void arc_perf_run_fixture(void)
{
    unsigned tests;

    length = idx;

    for (tests = 0; tests < num_tests; tests++)
    {
        for (idx = 0; idx < length; idx++)
        {
            if (arc_user_tests[idx].test)
            {
                double test_time;
                struct timespec start, end;
                clock_gettime(CLOCK_REALTIME, &start);
                arc_user_tests[idx].function();
                clock_gettime(CLOCK_REALTIME, &end);

                test_time = (double)(end.tv_sec - start.tv_sec) + 
                            ((double)(end.tv_nsec - start.tv_nsec))/1e9;

                arc_user_tests[idx].test_time += test_time;

                if (arc_user_tests[idx].all_times != NULL)
                {
                    arc_user_tests[idx].all_times[tests] = test_time;
                }
            }
            else
            {
                arc_user_tests[idx].function();
            }
        }
    }
}

/******************************************************************************/

void arc_perf_print_report(void)
{
    int tests;

    for (idx = 0; idx < length; idx++)
    {
        if (arc_user_tests[idx].test)
        {
            double average_time = arc_user_tests[idx].test_time / num_tests;

            sprintf(stderr, "%-*s %0.9f %0.9f\n", (int)max_str_size,
                                                  arc_user_tests[idx].name, 
                                                  average_time, 
                                                  arc_user_tests[idx].test_time);

            if (arc_user_tests[idx].all_times != NULL)
            {
                for (tests = 0; tests < num_tests; tests++)
                {
                    printf(" %0.9f", arc_user_tests[idx].all_times[tests]);
                }

                printf("\n");
            }

        }
    }
}

/******************************************************************************/

void arc_perf_cleanup(void)
{
    free(arc_user_tests);
}

/******************************************************************************/