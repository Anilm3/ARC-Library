/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/test/unit.h>

ARC_TEST(assert_true)
{
    ARC_ASSERT_TRUE(1)
}

ARC_TEST(assert_false)
{
    ARC_ASSERT_FALSE(0)
}

ARC_TEST(assert_pointer_null)
{
    ARC_ASSERT_POINTER_NULL(NULL)
}

ARC_TEST(assert_pointer_not_null)
{
    ARC_ASSERT_POINTER_NOT_NULL(1)
}

ARC_TEST(assert_pointer_equal)
{
    ARC_ASSERT_POINTER_EQUAL(1, 1)
}

ARC_TEST(assert_int_equal)
{
    ARC_ASSERT_INT_EQUAL(1, 1)
}

ARC_TEST(assert_ulong_equal)
{
    ARC_ASSERT_ULONG_EQUAL(11832193802UL, 11832193802UL)
}

ARC_TEST(assert_string_equal)
{
    ARC_ASSERT_STRING_EQUAL("HOLA", "HOLA")
}

ARC_TEST(assert_bit_set)
{
    ARC_ASSERT_BIT_SET(4321, 0)
}

ARC_TEST(assert_bit_not_set)
{
    ARC_ASSERT_BIT_NOT_SET(4320, 0)
}

ARC_TEST(assert_float_equal)
{
    ARC_ASSERT_FLOAT_EQUAL(191.2F, 191.2F, 0.001F)
}

ARC_TEST(assert_double_equal)
{
    ARC_ASSERT_DOUBLE_EQUAL(192.131, 192.131, 0.001)
}

ARC_TEST(assert_string_contains)
{
    ARC_ASSERT_STRING_CONTAINS("HOLA", 'O')
}

ARC_TEST(assert_string_doesnt_contain)
{
    ARC_ASSERT_STRING_DOESNT_CONTAIN("HOLA", 'B')
}

ARC_TEST(assert_string_starts_with)
{
    ARC_ASSERT_STRING_STARTS_WITH("HOLA", 'H')
}

ARC_TEST(assert_string_ends_with)
{
    ARC_ASSERT_STRING_ENDS_WITH("HOLA", 'A')
}

ARC_TEST_FIXTURE()
{
    ARC_ADD_TEST(assert_true)
    ARC_ADD_TEST(assert_false)
    ARC_ADD_TEST(assert_pointer_null)
    ARC_ADD_TEST(assert_pointer_not_null)
    ARC_ADD_TEST(assert_pointer_equal)
    ARC_ADD_TEST(assert_int_equal)
    ARC_ADD_TEST(assert_ulong_equal)
    ARC_ADD_TEST(assert_string_equal)
    ARC_ADD_TEST(assert_bit_set)
    ARC_ADD_TEST(assert_bit_not_set)
    ARC_ADD_TEST(assert_float_equal)
    ARC_ADD_TEST(assert_double_equal)
    ARC_ADD_TEST(assert_string_contains)
    ARC_ADD_TEST(assert_string_doesnt_contain)
    ARC_ADD_TEST(assert_string_starts_with)
    ARC_ADD_TEST(assert_string_ends_with)
}

ARC_RUN_TESTS()

