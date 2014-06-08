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

#include <arc/test/unit.h>

int arc_assert_true(int exp)
{
    return exp;
}

int arc_assert_false(int exp)
{
    return !exp;
}

int arc_assert_pointer_null(void * pointer)
{
    return (pointer == NULL);
}

int arc_assert_pointer_not_null(void * pointer)
{
    return (pointer != NULL);
}

int arc_assert_pointer_equal(void * left, void * right)
{
    return (left == right);
}

int arc_assert_int_equal(int left, int right)
{
    return (left == right);
}

int arc_assert_ulong_equal(unsigned long left, unsigned long right)
{
    return (left == right);
}

int arc_assert_string_equal(const char * left, const char * right)

{
    return (strcmp(left, right) == 0);
}

// int arc_assert_n_array_equal(int exp)
// {

// }

int arc_assert_bit_set(unsigned num, int bit)
{
    return ((num >> bit) & 1);
}

int arc_assert_bit_not_set(int num, int bit)
{
    return !((num >> bit) & 1);
}

// int arc_assert_bit_mask_matches(int exp)
// {
//     return ((num >> bit) & 1);
// }

// int arc_assert_fail(int exp)
// {

// }

int arc_assert_float_equal(float left, float right, float delta)
{
    return (fabsf(left - right) < delta);
}

int arc_assert_double_equal(double left, double right, double delta)
{
    return (fabs(left - right) < delta);
}

int arc_assert_string_contains(const char * str, char c)
{
    return (strchr(str, c) != NULL);
}

int arc_assert_string_doesnt_contain(const char * str, char c)
{
    return (strchr(str, c) == NULL);
}

int arc_assert_string_starts_with(const char * str, char c)
{
    return (str[0] == c);
}

int arc_assert_string_ends_with(const char * str, char c)
{
    return (str[strlen(str) - 1] == c);
}

