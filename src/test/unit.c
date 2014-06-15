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

typedef struct
{
    const char * name;
    void (* function)(void);
    int failed;
    int test;
} arc_test_t;

unsigned idx = 0;
unsigned length = 0;
unsigned max_length = 256;
int passed = 0;
int failed = 0;

arc_test_t * arc_user_tests;

/******************************************************************************/

void arc_add_test(const char * name, void (*fn)(void))
{
    arc_test_t test;

    test.name = name;
    test.function = fn;
    test.failed = 0;
    test.test = 1;

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

void arc_add_function(void (*fn)(void))
{
    arc_test_t test;

    test.name = "";
    test.function = fn;
    test.failed = 0;
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

void arc_set_system(void)
{
    arc_user_tests = malloc(sizeof(arc_test_t)*max_length);

    assert(arc_user_tests != NULL);
}

/******************************************************************************/

void arc_run_fixture(void)
{
    length = idx;

    for (idx = 0; idx < length; idx++)
    {
        if (arc_user_tests[idx].test)
        {
            printf("Running test : %s", arc_user_tests[idx].name);

            arc_user_tests[idx].function();

            if (!arc_user_tests[idx].failed)
            {
                printf(" : OK\n");
                passed++;
            }
            else
            {
                failed++;
            }
        }
        else
        {
            arc_user_tests[idx].function();
        }
    }
}

/******************************************************************************/

void arc_print_report(void)
{
    if (failed)
    {
        printf("Tests failed : ");

        for (idx = 0; idx < length; idx++)
        {
            printf("%s, ", arc_user_tests[idx].name);
        }
        printf("\n");
    }

    printf("Test result : %d/%d : %s\n", 
           passed, passed + failed, (failed ? "Failure" :"OK"));

}

/******************************************************************************/

void arc_cleanup(void)
{
    free(arc_user_tests);
}

/******************************************************************************/

void arc_set_test_failed(void)
{
    arc_user_tests[idx].failed = 1;
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

int arc_assert_pointer_equal(void * left, void * right)
{
    return (left == right);
}

/******************************************************************************/

int arc_assert_int_equal(int left, int right)
{
    return (left == right);
}

/******************************************************************************/

int arc_assert_ulong_equal(unsigned long left, unsigned long right)
{
    return (left == right);
}

/******************************************************************************/

int arc_assert_string_equal(const char * left, const char * right)
{
    return (strcmp(left, right) == 0);
}

/******************************************************************************/

int arc_assert_bit_set(unsigned num, int bit)
{
    return ((num >> bit) & 1);
}

/******************************************************************************/

int arc_assert_bit_not_set(int num, int bit)
{
    return !((num >> bit) & 1);
}

/******************************************************************************/

int arc_assert_float_equal(float left, float right, float delta)
{
    return (fabs(left - right) < delta);
}

/******************************************************************************/

int arc_assert_double_equal(double left, double right, double delta)
{
    return (fabs(left - right) < delta);
}

/******************************************************************************/

int arc_assert_string_contains(const char * str, char c)
{
    return (strchr(str, c) != NULL);
}

/******************************************************************************/

int arc_assert_string_doesnt_contain(const char * str, char c)
{
    return (strchr(str, c) == NULL);
}

/******************************************************************************/

int arc_assert_string_starts_with(const char * str, char c)
{
    return (str[0] == c);
}

/******************************************************************************/

int arc_assert_string_ends_with(const char * str, char c)
{
    return (str[strlen(str) - 1] == c);
}

/******************************************************************************/
