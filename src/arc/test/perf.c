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

static struct
{
    int argc;
    char **argv;
    int coverage;
    unsigned idx;
    unsigned length;
    unsigned max_length;
    size_t max_str_size;
    unsigned num_tests;
    arc_test_t * user_tests;
} 
info = {0, NULL, 0, 0, 0, 256, 0, 1, NULL};

/******************************************************************************/

const char * arc_get_param(const char * param)
{
    int i;
    for (i = 0; i < info.argc; i++)
    {
        if (strcmp(info.argv[i], param) == 0 && info.argc > (i + 1))
        {
            return info.argv[i + 1];
        }
    }

    return NULL;
}

/******************************************************************************/

void arc_perf_add_test(const char * name, void (*fn)(void))
{
    size_t name_size = strlen(name);
    arc_test_t test;

    test.name = name;
    test.function = fn;
    test.test_time = 0;
    test.test = 1;

    if (info.coverage)
    {
        test.all_times = malloc(sizeof(double)*info.num_tests);
    }
    else
    {
        test.all_times = NULL;
    }

    if (name_size > info.max_str_size)
    {
        info.max_str_size = name_size;
    }

    if (info.idx < info.max_length)
    {
        info.user_tests[info.idx++] = test;
    }
    else
    {
        arc_test_t * ptr;

        info.max_length += 256;
        ptr = realloc(info.user_tests, sizeof(arc_test_t)*info.max_length);

        assert(ptr != NULL);

        info.user_tests[info.idx++] = test;
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

    if (info.idx < info.max_length)
    {
        info.user_tests[info.idx++] = test;
    }
    else
    {
        arc_test_t * ptr;

        info.max_length += 256;
        ptr = realloc(info.user_tests, sizeof(arc_test_t)*info.max_length);

        assert(ptr != NULL);

        info.user_tests[info.idx++] = test;
    }
}

/******************************************************************************/

void arc_perf_set_system(int argc, char * argv[])
{
    int i;
    
    info.argc = argc;
    info.argv = argv;

    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-r") == 0 && argc > (i + 1))
        {
            info.num_tests = (unsigned)atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-c") == 0 && argc > (i + 1))
        {
            info.coverage = 1;
        }
    }
    info.user_tests = malloc(sizeof(arc_test_t)*info.max_length);

    assert(info.user_tests != NULL);
}

/******************************************************************************/

void arc_perf_run_fixture(void)
{
    unsigned tests;

    info.length = info.idx;

    for (tests = 0; tests < info.num_tests; tests++)
    {
        for (info.idx = 0; info.idx < info.length; info.idx++)
        {
            if (info.user_tests[info.idx].test)
            {
                double test_time;
                struct timespec start, end;
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
                info.user_tests[info.idx].function();
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

                test_time = (double)(end.tv_sec - start.tv_sec) + 
                            ((double)(end.tv_nsec - start.tv_nsec))/1e9;

                info.user_tests[info.idx].test_time += test_time;

                if (info.user_tests[info.idx].all_times != NULL)
                {
                    info.user_tests[info.idx].all_times[tests] = test_time;
                }
            }
            else
            {
                info.user_tests[info.idx].function();
            }
        }
    }
}

/******************************************************************************/

void arc_perf_print_report(void)
{
    unsigned tests;

    for (info.idx = 0; info.idx < info.length; info.idx++)
    {
        if (info.user_tests[info.idx].test)
        {
            double average_time = info.user_tests[info.idx].test_time / info.num_tests;

            printf("%-*s %0.9f %0.9f\n", (int)info.max_str_size,
                                         info.user_tests[info.idx].name, 
                                         average_time, 
                                         info.user_tests[info.idx].test_time);

            if (info.user_tests[info.idx].all_times != NULL)
            {
                for (tests = 0; tests < info.num_tests; tests++)
                {
                    printf(" %0.9f", info.user_tests[info.idx].all_times[tests]);
                }

                printf("\n");
            }

        }
    }
}

/******************************************************************************/

void arc_perf_cleanup(void)
{
    free(info.user_tests);
}

/******************************************************************************/