/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/deque2.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_UNIT_TEST(creation_test)
{
    arc_deque2_t deque = arc_deque2_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    arc_deque2_destroy(deque);
}

ARC_UNIT_TEST(empty_test)
{
    int i = 10;
    arc_deque2_t deque = arc_deque2_create(sizeof(int));

    ARC_ASSERT_TRUE(arc_deque2_empty(deque));

    ARC_ASSERT_INT_EQUAL(arc_deque2_push_front(deque, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_deque2_empty(deque));

    arc_deque2_pop_front(deque);

    arc_deque2_destroy(deque);
}

ARC_UNIT_TEST(size_test)
{
    int i = 10;
    arc_deque2_t deque = arc_deque2_create(sizeof(int));

    ARC_ASSERT_INT_EQUAL(arc_deque2_push_front(deque, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_deque2_size(deque), 1);
    
    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque2_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_deque2_size(deque), 11);

    for (i = 0; i < 5; i++)
    {
        arc_deque2_pop_front(deque);
    }

    ARC_ASSERT_INT_EQUAL(arc_deque2_size(deque), 6);

    arc_deque2_destroy(deque);
}

ARC_UNIT_TEST(push_pop_front_front)
{
    int i;
    arc_deque2_t deque = arc_deque2_create(sizeof(int));

    for (i = 0; i < 150; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque2_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 149;
    while(!arc_deque2_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque2_front(deque)), i--);

        arc_deque2_pop_front(deque);
    }

    arc_deque2_destroy(deque);
}

ARC_UNIT_TEST(destruction_test)
{
    int i;

    arc_deque2_t deque = arc_deque2_create(sizeof(double));
    
    for (i = 0; i < 150; i++)
    {
        double data = i;
        ARC_ASSERT_INT_EQUAL(arc_deque2_push_front(deque, (void *)&data), ARC_SUCCESS);
    }

    arc_deque2_destroy(deque);
}

ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(creation_test)
    ARC_UNIT_ADD_TEST(empty_test)
    ARC_UNIT_ADD_TEST(size_test)
    ARC_UNIT_ADD_TEST(push_pop_front_front)
    ARC_UNIT_ADD_TEST(destruction_test)
}

ARC_UNIT_RUN_TESTS()
