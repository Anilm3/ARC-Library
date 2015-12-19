/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/test/unit.h>

ARC_UNIT_TEST(assert_true)
{
    ARC_ASSERT_TRUE(1)
    ARC_EXPECT_TRUE(1)
}

ARC_UNIT_TEST(assert_false)
{
    ARC_ASSERT_FALSE(0)
    ARC_EXPECT_FALSE(0)
}

ARC_UNIT_TEST(assert_pointer_null)
{
    ARC_ASSERT_POINTER_NULL(NULL)
    ARC_EXPECT_POINTER_NULL(NULL)
}

ARC_UNIT_TEST(assert_pointer_not_null)
{
    ARC_ASSERT_POINTER_NOT_NULL(1)
    ARC_EXPECT_POINTER_NOT_NULL(1)
}

ARC_UNIT_TEST(assert_pointer_eq)
{
    ARC_ASSERT_POINTER_EQ(1, 1)
    ARC_EXPECT_POINTER_EQ(1, 1)
}

ARC_UNIT_TEST(assert_int_eq)
{
    ARC_ASSERT_INT_EQ(1, 1)
    ARC_EXPECT_INT_EQ(1, 1)
}

ARC_UNIT_TEST(assert_ulong_eq)
{
    ARC_ASSERT_ULONG_EQ(1183219UL, 1183219UL)
    ARC_EXPECT_ULONG_EQ(1183219UL, 1183219UL)
}

ARC_UNIT_TEST(assert_float_eq)
{
    ARC_ASSERT_FLOAT_EQ(191.2F, 191.2F, 0.001F)
    ARC_EXPECT_FLOAT_EQ(191.2F, 191.2F, 0.001F)
}

ARC_UNIT_TEST(assert_double_eq)
{
    ARC_ASSERT_DOUBLE_EQ(192.131, 192.131, 0.001)
    ARC_EXPECT_DOUBLE_EQ(192.131, 192.131, 0.001)
}

ARC_UNIT_TEST(assert_int_ne)
{
    ARC_ASSERT_INT_NE(1, 0)
    ARC_EXPECT_INT_NE(1, 0)
}

ARC_UNIT_TEST(assert_ulong_ne)
{
    ARC_ASSERT_ULONG_NE(1183219UL, 118321UL)
    ARC_EXPECT_ULONG_NE(1183219UL, 118321UL)
}

ARC_UNIT_TEST(assert_float_ne)
{
    ARC_ASSERT_FLOAT_NE(191.2F, 191.3F, 0.001F)
    ARC_EXPECT_FLOAT_NE(191.2F, 191.3F, 0.001F)
}

ARC_UNIT_TEST(assert_double_ne)
{
    ARC_ASSERT_DOUBLE_NE(192.131, 192.231, 0.001)
    ARC_EXPECT_DOUBLE_NE(192.131, 192.231, 0.001)
}

ARC_UNIT_TEST(assert_int_lt)
{
    ARC_ASSERT_INT_LT(0, 10)
    ARC_EXPECT_INT_LT(0, 10)
}

ARC_UNIT_TEST(assert_ulong_lt)
{
    ARC_ASSERT_ULONG_LT(118321UL, 1183219UL)
    ARC_EXPECT_ULONG_LT(118321UL, 1183219UL)
}

ARC_UNIT_TEST(assert_float_lt)
{
    ARC_ASSERT_FLOAT_LT(191.2F, 191.3F, 0.001F)
    ARC_EXPECT_FLOAT_LT(191.2F, 191.3F, 0.001F)
}

ARC_UNIT_TEST(assert_double_lt)
{
    ARC_ASSERT_DOUBLE_LT(192.131, 192.231, 0.001)
    ARC_EXPECT_DOUBLE_LT(192.131, 192.231, 0.001)
}

ARC_UNIT_TEST(assert_int_le)
{
    ARC_ASSERT_INT_LE(0, 10)
    ARC_EXPECT_INT_LE(0, 10)
}

ARC_UNIT_TEST(assert_ulong_le)
{
    ARC_ASSERT_ULONG_LE(118321UL, 1183219UL)
    ARC_EXPECT_ULONG_LE(118321UL, 1183219UL)
}

ARC_UNIT_TEST(assert_float_le)
{
    ARC_ASSERT_FLOAT_LE(191.2F, 191.3F, 0.001F)
    ARC_EXPECT_FLOAT_LE(191.2F, 191.3F, 0.001F)
}

ARC_UNIT_TEST(assert_double_le)
{
    ARC_ASSERT_DOUBLE_LE(192.131, 192.231, 0.001)
    ARC_EXPECT_DOUBLE_LE(192.131, 192.231, 0.001)
}

ARC_UNIT_TEST(assert_int_gt)
{
    ARC_ASSERT_INT_GT(10, 0)
    ARC_EXPECT_INT_GT(10, 0)
}

ARC_UNIT_TEST(assert_ulong_gt)
{
    ARC_ASSERT_ULONG_GT(1183219UL, 118321UL)
    ARC_EXPECT_ULONG_GT(1183219UL, 118321UL)
}

ARC_UNIT_TEST(assert_float_gt)
{
    ARC_ASSERT_FLOAT_GT(191.4F, 191.3F, 0.001F)
    ARC_EXPECT_FLOAT_GT(191.4F, 191.3F, 0.001F)
}

ARC_UNIT_TEST(assert_double_gt)
{
    ARC_ASSERT_DOUBLE_GT(192.431, 192.231, 0.001)
    ARC_EXPECT_DOUBLE_GT(192.431, 192.231, 0.001)
}

ARC_UNIT_TEST(assert_int_ge)
{
    ARC_ASSERT_INT_GE(10, 0)
    ARC_EXPECT_INT_GE(10, 0)
}

ARC_UNIT_TEST(assert_ulong_ge)
{
    ARC_ASSERT_ULONG_GE(1183219UL, 118321UL)
    ARC_EXPECT_ULONG_GE(1183219UL, 118321UL)
}

ARC_UNIT_TEST(assert_float_ge)
{
    ARC_ASSERT_FLOAT_GE(191.2F, 191.1F, 0.001F)
    ARC_EXPECT_FLOAT_GE(191.2F, 191.1F, 0.001F)
}

ARC_UNIT_TEST(assert_double_ge)
{
    ARC_ASSERT_DOUBLE_GE(192.131, 192.031, 0.001)
    ARC_EXPECT_DOUBLE_GE(192.131, 192.031, 0.001)
}

ARC_UNIT_TEST(assert_bit_set)
{
    ARC_ASSERT_BIT_SET(4321, 0)
    ARC_EXPECT_BIT_SET(4321, 0)
}

ARC_UNIT_TEST(assert_bit_not_set)
{
    ARC_ASSERT_BIT_NOT_SET(4320, 0)
    ARC_EXPECT_BIT_NOT_SET(4320, 0)
}

ARC_UNIT_TEST(assert_string_eq)
{
    ARC_ASSERT_STRING_EQ("HOLA", "HOLA")
    ARC_EXPECT_STRING_EQ("HOLA", "HOLA")
}

ARC_UNIT_TEST(assert_string_ne)
{
    ARC_ASSERT_STRING_NE("HOLA", "ADIOS")
    ARC_EXPECT_STRING_NE("HOLA", "ADIOS")
}

ARC_UNIT_TEST(assert_string_contains)
{
    ARC_ASSERT_STRING_CONTAINS("HOLA", 'O')
    ARC_EXPECT_STRING_CONTAINS("HOLA", 'O')
}

ARC_UNIT_TEST(assert_string_doesnt_contain)
{
    ARC_ASSERT_STRING_NOT_CONTAIN("HOLA", 'B')
    ARC_EXPECT_STRING_NOT_CONTAIN("HOLA", 'B')
}

ARC_UNIT_TEST(assert_string_starts_with)
{
    ARC_ASSERT_STRING_STARTS("HOLA", 'H')
    ARC_EXPECT_STRING_STARTS("HOLA", 'H')
}

ARC_UNIT_TEST(assert_string_ends_with)
{
    ARC_ASSERT_STRING_ENDS("HOLA", 'A')
    ARC_EXPECT_STRING_ENDS("HOLA", 'A')
}

ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(assert_true)
    ARC_UNIT_ADD_TEST(assert_false)

    ARC_UNIT_ADD_TEST(assert_pointer_null)
    ARC_UNIT_ADD_TEST(assert_pointer_not_null)
    ARC_UNIT_ADD_TEST(assert_pointer_eq)

    ARC_UNIT_ADD_TEST(assert_int_eq)
    ARC_UNIT_ADD_TEST(assert_ulong_eq)
    ARC_UNIT_ADD_TEST(assert_float_eq)
    ARC_UNIT_ADD_TEST(assert_double_eq)

    ARC_UNIT_ADD_TEST(assert_int_ne)
    ARC_UNIT_ADD_TEST(assert_ulong_ne)
    ARC_UNIT_ADD_TEST(assert_float_ne)
    ARC_UNIT_ADD_TEST(assert_double_ne)

    ARC_UNIT_ADD_TEST(assert_int_lt)
    ARC_UNIT_ADD_TEST(assert_ulong_lt)
    ARC_UNIT_ADD_TEST(assert_float_lt)
    ARC_UNIT_ADD_TEST(assert_double_lt)

    ARC_UNIT_ADD_TEST(assert_int_le)
    ARC_UNIT_ADD_TEST(assert_ulong_le)
    ARC_UNIT_ADD_TEST(assert_float_le)
    ARC_UNIT_ADD_TEST(assert_double_le)

    ARC_UNIT_ADD_TEST(assert_int_gt)
    ARC_UNIT_ADD_TEST(assert_ulong_gt)
    ARC_UNIT_ADD_TEST(assert_float_gt)
    ARC_UNIT_ADD_TEST(assert_double_gt)

    ARC_UNIT_ADD_TEST(assert_int_ge)
    ARC_UNIT_ADD_TEST(assert_ulong_ge)
    ARC_UNIT_ADD_TEST(assert_float_ge)
    ARC_UNIT_ADD_TEST(assert_double_ge)

    ARC_UNIT_ADD_TEST(assert_bit_set)
    ARC_UNIT_ADD_TEST(assert_bit_not_set)

    ARC_UNIT_ADD_TEST(assert_string_eq)
    ARC_UNIT_ADD_TEST(assert_string_ne)
    
    ARC_UNIT_ADD_TEST(assert_string_contains)
    ARC_UNIT_ADD_TEST(assert_string_doesnt_contain)
    ARC_UNIT_ADD_TEST(assert_string_starts_with)
    ARC_UNIT_ADD_TEST(assert_string_ends_with)
}

ARC_UNIT_RUN_TESTS()

