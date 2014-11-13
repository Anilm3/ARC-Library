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

int arc_assert_true(int expression)
{
    return expression;
}

/******************************************************************************/

int arc_assert_false(int expression)
{
    return !expression;
}

/******************************************************************************/

int arc_assert_pointer_null(void * pointer)
{
    return (pointer == NULL);
}

/******************************************************************************/

int arc_assert_pointer_not_null(void * pointer)
{
    return (pointer != NULL);
}

/******************************************************************************/

int arc_assert_pointer_eq(void * left, void * right)
{
    return (left == right);
}

/******************************************************************************/

int arc_assert_int_eq(int left, int right)
{
    return (left == right);
}

/******************************************************************************/

int arc_assert_ulong_eq(unsigned long left, unsigned long right)
{
    return (left == right);
}

/******************************************************************************/

int arc_assert_float_eq(float left, float right, double delta)
{
    return (fabsf(left - right) < delta);
}

/******************************************************************************/

int arc_assert_double_eq(double left, double right, double delta)
{
    return (fabs(left - right) < delta);
}


/******************************************************************************/

int arc_assert_int_ne(int left, int right)
{
    return (left != right);
}

/******************************************************************************/

int arc_assert_ulong_ne(unsigned long left, unsigned long right)
{
    return (left != right);
}

/******************************************************************************/

int arc_assert_float_ne(float left, float right, double delta)
{
    return (fabsf(left - right) > delta);
}

/******************************************************************************/

int arc_assert_double_ne(double left, double right, double delta)
{
    return (fabs(left - right) > delta);
}

/******************************************************************************/

int arc_assert_int_lt(int left, int right)
{
    return (left < right);
}

/******************************************************************************/

int arc_assert_ulong_lt(unsigned long left, unsigned long right)
{
    return (left < right);
}

/******************************************************************************/

int arc_assert_float_lt(float left, float right, double delta)
{
    return(fabsf(left - right) > delta) && (left < right);
}

/******************************************************************************/

int arc_assert_double_lt(double left, double right, double delta)
{
    return(fabs(left - right) > delta) && (left < right);
}

/******************************************************************************/

int arc_assert_int_le(int left, int right)
{
    return (left <= right);
}

/******************************************************************************/

int arc_assert_ulong_le(unsigned long left, unsigned long right)
{
    return (left <= right);
}

/******************************************************************************/

int arc_assert_float_le(float left, float right, double delta)
{
    return(fabsf(left - right) < delta) || (left < right);
}

/******************************************************************************/

int arc_assert_double_le(double left, double right, double delta)
{
    return(fabs(left - right) < delta) || (left < right);
}

/******************************************************************************/

int arc_assert_int_gt(int left, int right)
{
    return (left > right);
}

/******************************************************************************/

int arc_assert_ulong_gt(unsigned long left, unsigned long right)
{
    return (left > right);
}

/******************************************************************************/

int arc_assert_float_gt(float left, float right, double delta)
{
    return(fabsf(left - right) > delta) && (left > right);
}

/******************************************************************************/

int arc_assert_double_gt(double left, double right, double delta)
{
    return(fabs(left - right) > delta) && (left > right);
}

/******************************************************************************/

int arc_assert_int_ge(int left, int right)
{
    return (left >= right);
}

/******************************************************************************/

int arc_assert_ulong_ge(unsigned long left, unsigned long right)
{
    return (left >= right);
}

/******************************************************************************/

int arc_assert_float_ge(float left, float right, double delta)
{
    return(fabsf(left - right) < delta) || (left >= right);
}

/******************************************************************************/

int arc_assert_double_ge(double left, double right, double delta)
{
    return(fabs(left - right) < delta) || (left >= right);
}

/******************************************************************************/

int arc_assert_bit_set(unsigned long num, int bit)
{
    return ((num >> bit) & 1);
}

/******************************************************************************/

int arc_assert_bit_not_set(unsigned long num, int bit)
{
    return !((num >> bit) & 1);
}

/******************************************************************************/

int arc_assert_string_eq(const char * left, const char * right)
{
    return (strcmp(left, right) == 0);
}

/******************************************************************************/

int arc_assert_string_ne(const char * left, const char * right)
{
    return (strcmp(left, right) != 0);
}

/******************************************************************************/

int arc_assert_string_contains(const char * str, char c)
{
    return (strchr(str, c) != NULL);
}

/******************************************************************************/

int arc_assert_string_not_contain(const char * str, char c)
{
    return (strchr(str, c) == NULL);
}

/******************************************************************************/

int arc_assert_string_starts(const char * str, char c)
{
    return (str[0] == c);
}

/******************************************************************************/

int arc_assert_string_ends(const char * str, char c)
{
    return (str[strlen(str) - 1] == c);
}

/******************************************************************************/
