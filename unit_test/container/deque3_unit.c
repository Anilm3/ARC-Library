/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/deque3.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_UNIT_TEST(creation_test)
{
    arc_deque3_t deque = arc_deque3_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(empty_test)
{
    int i = 10;
    arc_deque3_t deque = arc_deque3_create(sizeof(int));

    ARC_ASSERT_TRUE(arc_deque3_empty(deque));

    ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_deque3_empty(deque));

    arc_deque3_pop_front(deque);

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(size_test)
{
    int i = 10;
    arc_deque3_t deque = arc_deque3_create(sizeof(int));

    ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_deque3_size(deque), 1);
    
    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_deque3_size(deque), 11);

    for (i = 0; i < 5; i++)
    {
        arc_deque3_pop_front(deque);
    }

    ARC_ASSERT_INT_EQUAL(arc_deque3_size(deque), 6);

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(push_pop_front_front)
{
    int i;
    arc_deque3_t deque = arc_deque3_create(sizeof(int));

    for (i = 0; i < 2000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 1999;
    while(!arc_deque3_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque3_front(deque)), i--);

        arc_deque3_pop_front(deque);
    }

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(push_pop_back_back)
{
    int i;
    arc_deque3_t deque = arc_deque3_create(sizeof(int));

    for (i = 0; i < 120; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 119;
    while(!arc_deque3_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque3_back(deque)), i--);

        arc_deque3_pop_back(deque);
    }

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(push_pop_front_back)
{
    int i;
    arc_deque3_t deque = arc_deque3_create(sizeof(int));

    for (i = 0; i < 100; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_deque3_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque3_back(deque)), i++);

        arc_deque3_pop_back(deque);
    }

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(push_pop_back_front)
{
    int i;
    arc_deque3_t deque = arc_deque3_create(sizeof(int));

    for (i = 0; i < 100; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_deque3_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque3_front(deque)), i++);

        arc_deque3_pop_front(deque);
    }

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(mixed_push_front_back_test)
{
    int i;

    arc_deque3_t deque = arc_deque3_create(sizeof(unsigned));
    
    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_deque3_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque3_front(deque)), i++);

        arc_deque3_pop_front(deque);
    }

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(mixed_push_back_front_test)
{
    int i;

    arc_deque3_t deque = arc_deque3_create(sizeof(unsigned));
    
    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_deque3_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque3_front(deque)), i++);

        arc_deque3_pop_front(deque);
    }

    arc_deque3_destroy(deque);
}


ARC_UNIT_TEST(indexed_access_test)
{
    int i;

    arc_deque3_t deque = arc_deque3_create(sizeof(unsigned));
    
    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    for (i = 0; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque3_at(deque, (unsigned)i)), i);
    }

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST(destruction_test)
{
    int i;

    arc_deque3_t deque = arc_deque3_create(sizeof(double));
    
    for (i = 0; i < 100; i++)
    {
        double data = i;
        ARC_ASSERT_INT_EQUAL(arc_deque3_push_front(deque, (void *)&data), ARC_SUCCESS);
    }

    arc_deque3_destroy(deque);
}

ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(creation_test)
    ARC_UNIT_ADD_TEST(empty_test)
    ARC_UNIT_ADD_TEST(size_test)
    ARC_UNIT_ADD_TEST(push_pop_front_front)
    ARC_UNIT_ADD_TEST(push_pop_back_back)
    ARC_UNIT_ADD_TEST(push_pop_front_back)
    ARC_UNIT_ADD_TEST(push_pop_back_front)
    ARC_UNIT_ADD_TEST(mixed_push_front_back_test)
    ARC_UNIT_ADD_TEST(mixed_push_back_front_test)
    ARC_UNIT_ADD_TEST(indexed_access_test)
    ARC_UNIT_ADD_TEST(destruction_test)
}

ARC_UNIT_RUN_TESTS()
