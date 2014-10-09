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

ARC_UNIT_TEST(creation_test)
{
    arc_deque_t deque = arc_deque_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    arc_deque_destroy(deque);
}

ARC_UNIT_TEST(empty_test)
{
    int i = 10;
    arc_deque_t deque = arc_deque_create(sizeof(int));

    ARC_ASSERT_TRUE(arc_deque_empty(deque));

    ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_deque_empty(deque));

    arc_deque_pop_front(deque);

    arc_deque_destroy(deque);
}

ARC_UNIT_TEST(size_test)
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

ARC_UNIT_TEST(push_pop_front_front)
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

ARC_UNIT_TEST(push_pop_back_back)
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

ARC_UNIT_TEST(push_pop_front_back)
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

ARC_UNIT_TEST(push_pop_back_front)
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

ARC_UNIT_TEST(mixed_push_front_back_test)
{
    int i;

    arc_deque_t deque = arc_deque_create(sizeof(unsigned));
    
    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    for (i = 101; i < 200; i++)
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

ARC_UNIT_TEST(mixed_push_back_front_test)
{
    int i;

    arc_deque_t deque = arc_deque_create(sizeof(unsigned));
    
    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_deque_empty(deque))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_front(deque)), i++);

        arc_deque_pop_front(deque);
    }

    arc_deque_destroy(deque);
}


ARC_UNIT_TEST(indexed_access_test)
{
    int i;

    arc_deque_t deque = arc_deque_create(sizeof(unsigned));
    
    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_back(deque, (void *)&i), ARC_SUCCESS);
    }

    for (i = 0; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_at(deque, (unsigned)i)), i);
    }

    arc_deque_destroy(deque);
}

ARC_UNIT_TEST(iterators_forward)
{
    int i;
    arc_deque_t deque = arc_deque_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(deque);

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;

    arc_deque_before_begin(it);

    while(arc_deque_next(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_data(it)), i--);
    }

    arc_iterator_destroy(it);
    arc_deque_destroy(deque);
}

ARC_UNIT_TEST(iterators_backward)
{
    int i;
    arc_deque_t deque = arc_deque_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(deque);

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_push_front(deque, (void *)&i), ARC_SUCCESS);
    }

    i = 0;

    arc_deque_after_end(it);

    while(arc_deque_previous(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_data(it)), i++);
    }

    arc_iterator_destroy(it);
    arc_deque_destroy(deque);
}

ARC_UNIT_TEST(iterators_insertion_front)
{
    int i = 0;
    arc_deque_t deque = arc_deque_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(deque);

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    arc_deque_before_begin(it);
    ARC_ASSERT_INT_EQUAL(arc_deque_insert_before(it, (void *)&i), ARC_ERROR);

    for (i = 0; i < 20; i++)
    {
        arc_deque_before_begin(it);
        ARC_ASSERT_INT_EQUAL(arc_deque_insert_after(it, (void *)&i), 
                             ARC_SUCCESS);
    }


    arc_deque_before_begin(it);

    i = 19;
    while(arc_deque_next(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_data(it)), i);
        i--;
    }

    ARC_ASSERT_INT_EQUAL(i, -1);

    arc_iterator_destroy(it);
    arc_deque_destroy(deque);
}

ARC_UNIT_TEST(iterators_insertion_back)
{
    int i;
    arc_deque_t deque = arc_deque_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(deque);

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    arc_deque_after_end(it);

    ARC_ASSERT_INT_EQUAL(arc_deque_insert_after(it, (void *)&i), ARC_ERROR);

    for (i = 0; i < 20; i++)
    {
        arc_deque_after_end(it);
        ARC_ASSERT_INT_EQUAL(arc_deque_insert_before(it, (void *)&i), 
                             ARC_SUCCESS);
    }

    arc_deque_after_end(it);

    i = 19;
    while(arc_deque_previous(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_data(it)), i);
        i--;
    }

    ARC_ASSERT_INT_EQUAL(i, -1);

    arc_iterator_destroy(it);
    arc_deque_destroy(deque);
}

ARC_UNIT_TEST(iterators_insertion_middle)
{
    unsigned i;
    arc_deque_t deque = arc_deque_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(deque);

    ARC_ASSERT_POINTER_NOT_NULL(deque);

    for (i = 0; i < 10; i+=2)
    {
        arc_deque_push_back(deque, (void *)&i);
    }

    /* 0 2 4 6 8 */
    i = 1;
    ARC_ASSERT_INT_EQUAL(arc_deque_position(it, 0), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_deque_insert_after(it, (void *)&i), ARC_SUCCESS);

    /* 0 1 2 4 6 8 */
    i = 3;
    ARC_ASSERT_INT_EQUAL(arc_deque_position(it, 3), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_deque_insert_before(it, (void *)&i), ARC_SUCCESS);

    /* 0 1 2 3 4 6 8 */
    i = 5;
    ARC_ASSERT_INT_EQUAL(arc_deque_position(it, 4), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_deque_insert_after(it, (void *)&i), ARC_SUCCESS);

    /* 0 1 2 3 4 5 6 8 */
    i = 7;
    ARC_ASSERT_INT_EQUAL(arc_deque_position(it, 7), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_deque_insert_before(it, (void *)&i), ARC_SUCCESS);

    /* 0 1 2 3 4 5 6 7 8 */
    i = 9;
    ARC_ASSERT_INT_EQUAL(arc_deque_position(it, 8), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_deque_insert_after(it, (void *)&i), ARC_SUCCESS);

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_deque_position(it, i), ARC_SUCCESS);
        ARC_ASSERT_INT_EQUAL(*((int *)arc_deque_data(it)), i);
    }

    arc_iterator_destroy(it);
    arc_deque_destroy(deque);
}

ARC_UNIT_TEST(destruction_test)
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
    ARC_UNIT_ADD_TEST(iterators_forward)
    ARC_UNIT_ADD_TEST(iterators_backward)
    ARC_UNIT_ADD_TEST(iterators_insertion_front)
    ARC_UNIT_ADD_TEST(iterators_insertion_back)
    ARC_UNIT_ADD_TEST(iterators_insertion_middle)
    ARC_UNIT_ADD_TEST(destruction_test)
}

ARC_UNIT_RUN_TESTS()
