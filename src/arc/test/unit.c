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

#include <arc/test/unit.h>

#define ARC_UNIT_BLOCK_SIZE 32

typedef struct
{
    const char * name;
    void (* function)(void);
    int failed;
    int test;
} arc_test_t;

static struct
{
    unsigned idx;
    unsigned length;
    unsigned max_length;
    int passed;
    int failed;
    arc_test_t * user_tests;
    int just_print_tests;
    int argc;
    char **argv;
}
info = {0, 0, ARC_UNIT_BLOCK_SIZE, 0, 0, NULL, 0, 0, NULL};

/******************************************************************************/

void arc_unit_print_report(void);
void arc_unit_cleanup(void);
void arc_unit_set_test_passed(void);

/******************************************************************************/

void arc_unit_add_test(const char * name, void (*fn)(void))
{
    arc_test_t test;

    test.name = name;
    test.function = fn;
    test.failed = 0;
    test.test = 1;

    if (info.idx < info.max_length)
    {
        info.user_tests[info.idx++] = test;
    }
    else
    {
        arc_test_t * ptr;

        info.max_length += ARC_UNIT_BLOCK_SIZE;
        ptr = realloc(info.user_tests, sizeof(arc_test_t)*info.max_length);

        if (ptr != NULL)
        {
            info.user_tests = ptr;
            info.user_tests[info.idx++] = test;
        }
        else
        {
            /* Crash like hell I said */
            exit(EXIT_FAILURE);
        }
    }
}

/******************************************************************************/

void arc_unit_add_function(void (*fn)(void))
{
    arc_test_t test;

    test.name = "";
    test.function = fn;
    test.failed = 0;
    test.test = 0;

    if (info.idx < info.max_length)
    {
        info.user_tests[info.idx++] = test;
    }
    else
    {
        arc_test_t * ptr;

        info.max_length += ARC_UNIT_BLOCK_SIZE;
        ptr = realloc(info.user_tests, sizeof(arc_test_t)*info.max_length);

        if (ptr != NULL)
        {
            info.user_tests = ptr;
            info.user_tests[info.idx++] = test;
        }
        else
        {
            /* Crash like hell I said */
            exit(EXIT_FAILURE);
        }
    }
}

/******************************************************************************/

void arc_unit_init(int argc, char *argv[])
{
    int i;

    info.argc = argc;
    info.argv = argv;

    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            info.just_print_tests = 1;
        }
    }

    info.user_tests = malloc(sizeof(arc_test_t)*info.max_length);

    assert(info.user_tests != NULL);
}

/******************************************************************************/

int arc_unit_run(void)
{
    int retval = 0;

    info.length = info.idx;

    for (info.idx = 0; info.idx < info.length; info.idx++)
    {

        if (info.user_tests[info.idx].test)
        {
            if (info.just_print_tests)
            {
                printf("%s\n", info.user_tests[info.idx].name);
                continue;
            }

            printf("Running test : %s", info.user_tests[info.idx].name);

            info.user_tests[info.idx].function();

            if (!info.user_tests[info.idx].failed)
            {
                printf(" : OK\n");
                info.passed++;
            }
            else
            {
                info.failed++;
            }
        }
        else
        {
            info.user_tests[info.idx].function();
        }
    }

    retval = (info.failed > 0);

    if (!info.just_print_tests)
    {
        arc_unit_print_report();
    }

    arc_unit_cleanup();

    return retval;
}

/******************************************************************************/

void arc_unit_print_report(void)
{
    if (info.failed > 0)
    {
        printf("Tests failed : ");

        for (info.idx = 0; info.idx < info.length; info.idx++)
        {
            if (info.user_tests[info.idx].failed)
            {
                printf("%s ", info.user_tests[info.idx].name);
            }
        }
        printf("\n");
    }

    printf("Test result : %d/%d : %s\n",
           info.passed,
           info.passed + info.failed,
           (info.failed > 0 ? "Failure" :"OK"));

}

/******************************************************************************/

void arc_unit_cleanup(void)
{
    free(info.user_tests);
}

/******************************************************************************/

void arc_unit_set_test_failed(void)
{
    info.user_tests[info.idx].failed = 1;
}

/******************************************************************************/

int arc_unit_true(const int expression)
{
    return expression;
}

/******************************************************************************/

int arc_unit_false(const int expression)
{
    return !expression;
}

/******************************************************************************/

int arc_unit_pointer_null(const void * pointer)
{
    return (pointer == NULL);
}

/******************************************************************************/

int arc_unit_pointer_not_null(const void * pointer)
{
    return (pointer != NULL);
}

/******************************************************************************/

int arc_unit_pointer_eq(const void * left, const void * right)
{
    return (left == right);
}

/******************************************************************************/

int arc_unit_int_eq(const int left, const int right)
{
    return (left == right);
}

/******************************************************************************/

int arc_unit_ulong_eq(const unsigned long left, const unsigned long right)
{
    return (left == right);
}

/******************************************************************************/

int arc_unit_float_eq(const float left, const float right, const double delta)
{
    return (fabsf(left - right) < delta);
}

/******************************************************************************/

int arc_unit_double_eq(const double left, const double right, const double delta)
{
    return (fabs(left - right) < delta);
}


/******************************************************************************/

int arc_unit_int_ne(const int left, const int right)
{
    return (left != right);
}

/******************************************************************************/

int arc_unit_ulong_ne(const unsigned long left, const unsigned long right)
{
    return (left != right);
}

/******************************************************************************/

int arc_unit_float_ne(const float left, const float right, const double delta)
{
    return (fabsf(left - right) > delta);
}

/******************************************************************************/

int arc_unit_double_ne(const double left, const double right, const double delta)
{
    return (fabs(left - right) > delta);
}

/******************************************************************************/

int arc_unit_int_lt(const int left, const int right)
{
    return (left < right);
}

/******************************************************************************/

int arc_unit_ulong_lt(const unsigned long left, const unsigned long right)
{
    return (left < right);
}

/******************************************************************************/

int arc_unit_float_lt(const float left, const float right, const double delta)
{
    return(fabsf(left - right) > delta) && (left < right);
}

/******************************************************************************/

int arc_unit_double_lt(const double left, const double right, const double delta)
{
    return(fabs(left - right) > delta) && (left < right);
}

/******************************************************************************/

int arc_unit_int_le(const int left, const int right)
{
    return (left <= right);
}

/******************************************************************************/

int arc_unit_ulong_le(const unsigned long left, const unsigned long right)
{
    return (left <= right);
}

/******************************************************************************/

int arc_unit_float_le(const float left, const float right, const double delta)
{
    return(fabsf(left - right) < delta) || (left < right);
}

/******************************************************************************/

int arc_unit_double_le(const double left, const double right, const double delta)
{
    return(fabs(left - right) < delta) || (left < right);
}

/******************************************************************************/

int arc_unit_int_gt(const int left, const int right)
{
    return (left > right);
}

/******************************************************************************/

int arc_unit_ulong_gt(const unsigned long left, const unsigned long right)
{
    return (left > right);
}

/******************************************************************************/

int arc_unit_float_gt(const float left, const float right, const double delta)
{
    return(fabsf(left - right) > delta) && (left > right);
}

/******************************************************************************/

int arc_unit_double_gt(const double left, const double right, const double delta)
{
    return(fabs(left - right) > delta) && (left > right);
}

/******************************************************************************/

int arc_unit_int_ge(const int left, const int right)
{
    return (left >= right);
}

/******************************************************************************/

int arc_unit_ulong_ge(const unsigned long left, const unsigned long right)
{
    return (left >= right);
}

/******************************************************************************/

int arc_unit_float_ge(const float left, const float right, const double delta)
{
    return(fabsf(left - right) < delta) || (left >= right);
}

/******************************************************************************/

int arc_unit_double_ge(const double left, const double right, const double delta)
{
    return(fabs(left - right) < delta) || (left >= right);
}

/******************************************************************************/

int arc_unit_bit_set(const unsigned long num, const int bit)
{
    return ((num >> bit) & 1);
}

/******************************************************************************/

int arc_unit_bit_not_set(const unsigned long num, const int bit)
{
    return !((num >> bit) & 1);
}

/******************************************************************************/

int arc_unit_string_eq(const char * left, const char * right)
{
    return (strcmp(left, right) == 0);
}

/******************************************************************************/

int arc_unit_string_ne(const char * left, const char * right)
{
    return (strcmp(left, right) != 0);
}

/******************************************************************************/

int arc_unit_string_contains(const char * str, const char c)
{
    return (strchr(str, c) != NULL);
}

/******************************************************************************/

int arc_unit_string_not_contain(const char * str, const char c)
{
    return (strchr(str, c) == NULL);
}

/******************************************************************************/

int arc_unit_string_starts(const char * str, const char c)
{
    return (str[0] == c);
}

/******************************************************************************/

int arc_unit_string_ends(const char * str, const char c)
{
    return (str[strlen(str) - 1] == c);
}

/******************************************************************************/
