/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/deque.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_TEST(creation_test)
{
    arc_deque_t deque = arc_deque_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    arc_deque_destroy(deque);
}

ARC_TEST(empty_test)
{
    int i = 10;
    arc_deque_t deque = arc_deque_create(sizeof(int));

    ARC_ASSERT_TRUE(arc_deque_empty(deque));

    ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_deque_empty(deque));

    arc_deque_pop_front(deque);

    arc_deque_destroy(deque);
}

ARC_TEST(size_test)
{
    int i = 10;
    arc_deque_t deque = arc_deque_create(sizeof(int));

    ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_deque_size(deque), 1);
    
    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_deque_size(deque), 11);

    for (i = 0; i < 5; i++)
    {
        arc_deque_pop_front(deque);
    }

    ARC_ASSERT_INT_EQUAL(arc_deque_size(deque), 6);

    arc_deque_destroy(deque);
}

ARC_TEST(push_pop_front_front)
{
    int i;
    arc_deque_t deque = arc_deque_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_deque_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_front(deque)), i--);

        arc_deque_pop_front(deque);
    }

    arc_deque_destroy(deque);
}

ARC_TEST(push_pop_back_back)
{
    int i;
    arc_deque_t deque = arc_deque_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_deque_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_back(deque)), i--);

        arc_deque_pop_back(deque);
    }

    arc_deque_destroy(deque);
}

ARC_TEST(push_pop_front_back)
{
    int i;
    arc_deque_t deque = arc_deque_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_deque_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_back(deque)), i++);

        arc_deque_pop_back(deque);
    }

    arc_deque_destroy(deque);
}

ARC_TEST(push_pop_back_front)
{
    int i;
    arc_deque_t deque = arc_deque_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_deque_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_front(deque)), i++);

        arc_deque_pop_front(deque);
    }

    arc_deque_destroy(deque);
}

ARC_TEST(destruction_test)
{
    int i;

    arc_deque_t deque = arc_deque_create(sizeof(double));
    
    for (i = 0; i < 20000; i++)
    {
        double data = i;
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&data), ARC_SUCCESS);
    }

    arc_deque_destroy(deque);
}

ARC_TEST_FIXTURE()
{
    ARC_ADD_TEST(creation_test)
    ARC_ADD_TEST(empty_test)
    ARC_ADD_TEST(size_test)
    ARC_ADD_TEST(push_pop_front_front)
    ARC_ADD_TEST(push_pop_back_back)
    ARC_ADD_TEST(push_pop_front_back)
    ARC_ADD_TEST(push_pop_back_front)
    ARC_ADD_TEST(destruction_test)
}

ARC_RUN_TESTS()
