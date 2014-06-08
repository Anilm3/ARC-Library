#include <arc/test/unit.h>

ARC_TEST(fail)
{
    ARC_ASSERT_FAIL()
}

ARC_TEST(assert_true)
{
    ARC_ASSERT_TRUE(0)
}

ARC_TEST(assert_false)
{
    ARC_ASSERT_FALSE(1)
}

ARC_TEST(assert_pointer_null)
{
    ARC_ASSERT_POINTER_NULL(1)
}

ARC_TEST(assert_pointer_not_null)
{
    ARC_ASSERT_POINTER_NOT_NULL(NULL)
}

ARC_TEST(assert_pointer_equal)
{
    ARC_ASSERT_POINTER_EQUAL(1, NULL)
}

ARC_TEST(assert_int_equal)
{
    ARC_ASSERT_INT_EQUAL(2, 1)
}

ARC_TEST(assert_ulong_equal)
{
    ARC_ASSERT_ULONG_EQUAL(11832193802UL, 1183219380UL)
}

ARC_TEST(assert_string_equal)
{
    ARC_ASSERT_STRING_EQUAL("HOLA", "ADIOS")
}

ARC_TEST(assert_bit_set)
{
    ARC_ASSERT_BIT_SET(4320, 0)
}

ARC_TEST(assert_bit_not_set)
{
    ARC_ASSERT_BIT_NOT_SET(4321, 0)
}

ARC_TEST(assert_float_equal)
{
    ARC_ASSERT_FLOAT_EQUAL(191.2F, 192.2F, 0.001F)
}

ARC_TEST(assert_double_equal)
{
    ARC_ASSERT_DOUBLE_EQUAL(192.131, 193.131, 0.001)
}

ARC_TEST(assert_string_contains)
{
    ARC_ASSERT_STRING_CONTAINS("HOLA", 'B')
}

ARC_TEST(assert_string_doesnt_contain)
{
    ARC_ASSERT_STRING_DOESNT_CONTAIN("HOLA", 'A')
}

ARC_TEST(assert_string_starts_with)
{
    ARC_ASSERT_STRING_STARTS_WITH("HOLA", 'O')
}

ARC_TEST(assert_string_ends_with)
{
    ARC_ASSERT_STRING_ENDS_WITH("HOLA", 'L')
}

ARC_TEST_FIXTURE()
{
    ARC_ADD_TEST(fail)
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

