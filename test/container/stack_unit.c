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

ARC_TEST(size_test)
{
    int i = 10;
    arc_stack_t list = arc_stack_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    ARC_ASSERT_TRUE(arc_stack_empty(list));

    ARC_ASSERT_INT_EQUAL(arc_stack_push(list, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_stack_size(list), 1);
    
    ARC_ASSERT_FALSE(arc_stack_empty(list));

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_stack_push(list, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_stack_size(list), 11);

    arc_stack_destroy(list);
}

ARC_TEST(push_pop)
{
    int i;
    arc_stack_t list = arc_stack_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_stack_push(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_stack_empty(list))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_stack_top(list)), i--);

        arc_stack_pop(list);
    }

    arc_stack_destroy(list);
}

ARC_TEST(destruction)
{
    int i;

    arc_stack_t list = arc_stack_create(sizeof(double));
    
    ARC_ASSERT_POINTER_NOT_NULL(list);
    
    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_stack_push(list, (void *)&i), ARC_SUCCESS);
    }

    arc_stack_destroy(list);
}

ARC_TEST_FIXTURE()
{
    ARC_ADD_TEST(size_test)
    ARC_ADD_TEST(push_pop)
    ARC_ADD_TEST(destruction)
}

ARC_RUN_TESTS()
