/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/stack.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_UNIT_TEST(creation_test)
{
    arc_stack_t stack = arc_stack_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(stack);

    arc_stack_destroy(stack);
}

ARC_UNIT_TEST(empty_test)
{
    int i = 10;
    arc_stack_t stack = arc_stack_create(sizeof(int));

    ARC_ASSERT_TRUE(arc_stack_empty(stack));

    ARC_ASSERT_INT_EQUAL(arc_stack_push(stack, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_stack_empty(stack));

    arc_stack_pop(stack);

    arc_stack_destroy(stack);
}

ARC_UNIT_TEST(size_test)
{
    int i = 10;
    arc_stack_t stack = arc_stack_create(sizeof(int));

    ARC_ASSERT_INT_EQUAL(arc_stack_push(stack, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_stack_size(stack), 1);
    
    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_stack_push(stack, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_stack_size(stack), 11);

    for (i = 0; i < 5; i++)
    {
        arc_stack_pop(stack);
    }

    ARC_ASSERT_INT_EQUAL(arc_stack_size(stack), 6);

    arc_stack_destroy(stack);
}

ARC_UNIT_TEST(push_pop_test)
{
    int i;
    arc_stack_t stack = arc_stack_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_stack_push(stack, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_stack_empty(stack))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_stack_top(stack)), i--);

        arc_stack_pop(stack);
    }

    arc_stack_destroy(stack);
}

ARC_UNIT_TEST(destruction_test)
{
    int i;

    arc_stack_t stack = arc_stack_create(sizeof(double));
    
    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_stack_push(stack, (void *)&i), ARC_SUCCESS);
    }

    arc_stack_destroy(stack);
}

ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(creation_test)
    ARC_UNIT_ADD_TEST(empty_test)
    ARC_UNIT_ADD_TEST(size_test)
    ARC_UNIT_ADD_TEST(push_pop_test)
    ARC_UNIT_ADD_TEST(destruction_test)
}

ARC_UNIT_RUN_TESTS()
