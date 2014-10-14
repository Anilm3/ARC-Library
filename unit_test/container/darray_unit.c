/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/darray.h>
#include <arc/container/iterator.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_UNIT_TEST(creation_test)
{
    arc_darray_t darray = arc_darray_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(empty_test)
{
    int i = 10;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    ARC_ASSERT_TRUE(arc_darray_empty(darray));

    ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_darray_empty(darray));

    arc_darray_pop_front(darray);

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(size_test)
{
    int i = 10;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_darray_size(darray), 1);
    
    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_darray_size(darray), 11);

    for (i = 0; i < 5; i++)
    {
        arc_darray_pop_front(darray);
    }

    ARC_ASSERT_INT_EQUAL(arc_darray_size(darray), 6);

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(push_pop_front_front)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_front(darray)), i--);

        arc_darray_pop_front(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(push_pop_back_back)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_back(darray)), i--);

        arc_darray_pop_back(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(push_pop_front_back)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_back(darray)), i++);

        arc_darray_pop_back(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(push_pop_back_front)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_front(darray)), i++);

        arc_darray_pop_front(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(mixed_push_front_back_test)
{
    int i;

    arc_darray_t darray = arc_darray_create(sizeof(unsigned));
    
    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_front(darray)), i++);

        arc_darray_pop_front(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(mixed_push_back_front_test)
{
    int i;

    arc_darray_t darray = arc_darray_create(sizeof(unsigned));
    
    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_front(darray)), i++);

        arc_darray_pop_front(darray);
    }

    arc_darray_destroy(darray);
}


ARC_UNIT_TEST(indexed_access_test)
{
    int i;

    arc_darray_t darray = arc_darray_create(sizeof(unsigned));
    
    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    for (i = 0; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_at(darray, (unsigned)i)), i);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(iterators_forward)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(darray);

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;

    arc_darray_before_begin(it);

    while(arc_darray_next(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_data(it)), i--);
    }

    arc_iterator_destroy(it);
    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(iterators_backward)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(darray);

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;

    arc_darray_after_end(it);

    while(arc_darray_previous(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_data(it)), i++);
    }

    arc_iterator_destroy(it);
    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(iterators_position)
{
    unsigned i = 0;
    arc_darray_t darray = arc_darray_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(darray);

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i),
                             ARC_SUCCESS);
    }

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_position(it, i), ARC_SUCCESS);
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_data(it)), i);
    }

    arc_iterator_destroy(it);
    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(iterators_insertion_front)
{
    int i = 0;
    arc_darray_t darray = arc_darray_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(darray);

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    arc_darray_before_begin(it);

    ARC_ASSERT_INT_EQUAL(arc_darray_insert_before(it, (void *)&i), ARC_ERROR);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_insert_after(it, (void *)&i), 
                             ARC_SUCCESS);
    }

    i = 19999;
    while(arc_darray_next(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_data(it)), i--);
    }

    ARC_ASSERT_INT_EQUAL(i, -1);

    arc_iterator_destroy(it);
    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(iterators_insertion_back)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(darray);

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    arc_darray_after_end(it);

    ARC_ASSERT_INT_EQUAL(arc_darray_insert_after(it, (void *)&i), ARC_ERROR);

    for (i = 0; i < 20000; i++)
    {
        arc_darray_after_end(it);
        ARC_ASSERT_INT_EQUAL(arc_darray_insert_before(it, (void *)&i), 
                             ARC_SUCCESS);
    }

    arc_darray_after_end(it);

    i = 19999;
    while(arc_darray_previous(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_data(it)), i--);
    }

    ARC_ASSERT_INT_EQUAL(i, -1);

    arc_iterator_destroy(it);
    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(iterators_insertion_middle)
{
    unsigned i;
    arc_darray_t darray = arc_darray_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(darray);

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    for (i = 0; i < 10; i+=2)
    {
        arc_darray_push_back(darray, (void *)&i);
    }

    /* 0 2 4 6 8 */
    i = 1;
    ARC_ASSERT_INT_EQUAL(arc_darray_position(it, 0), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_darray_insert_after(it, (void *)&i), ARC_SUCCESS);

    /* 0 1 2 4 6 8 */
    i = 3;
    ARC_ASSERT_INT_EQUAL(arc_darray_position(it, 3), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_darray_insert_before(it, (void *)&i), ARC_SUCCESS);

    /* 0 1 2 3 4 6 8 */
    i = 5;
    ARC_ASSERT_INT_EQUAL(arc_darray_position(it, 4), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_darray_insert_after(it, (void *)&i), ARC_SUCCESS);

    /* 0 1 2 3 4 5 6 8 */
    i = 7;
    ARC_ASSERT_INT_EQUAL(arc_darray_position(it, 7), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_darray_insert_before(it, (void *)&i), ARC_SUCCESS);

    /* 0 1 2 3 4 5 6 7 8 */
    i = 9;
    ARC_ASSERT_INT_EQUAL(arc_darray_position(it, 8), ARC_SUCCESS);
    ARC_ASSERT_INT_EQUAL(arc_darray_insert_after(it, (void *)&i), ARC_SUCCESS);

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_position(it, i), ARC_SUCCESS);
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_data(it)), i);
    }

    arc_darray_clear(darray);

    for (i = 1; i < 20000; i+=2)
    {
        arc_darray_push_back(darray, (void *)&i);
    }

    for (i = 0; i < 20000; i+=2)
    {
        arc_darray_position(it, i);
        ARC_ASSERT_INT_EQUAL(arc_darray_insert_before(it, (void *)&i), 
                                                     ARC_SUCCESS);
    }

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((unsigned *)arc_darray_at(darray, i)), i);
    }

    arc_darray_clear(darray);

    for (i = 0; i < 20000; i+=2)
    {
        arc_darray_push_back(darray, (void *)&i);
    }

    for (i = 1; i < 20000; i+=2)
    {
        arc_darray_position(it, i - 1);
        ARC_ASSERT_INT_EQUAL(arc_darray_insert_after(it, (void *)&i), 
                                                    ARC_SUCCESS);
    }

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((unsigned *)arc_darray_at(darray, i)), i);
    }

    arc_iterator_destroy(it);
    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(iterators_erase)
{
    unsigned i;
    arc_darray_t darray = arc_darray_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(darray);

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    for (i = 0; i < 20000; i++)
    {
        arc_darray_push_back(darray, (void *)&i);
    }

    for (i = 0; i < 10000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_position(it, 0), ARC_SUCCESS);
        arc_darray_erase(it);
    }

    for (i = 10000; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((unsigned *)arc_darray_at(darray, i - 10000)), i);
    }

    arc_darray_clear(darray);

    for (i = 0; i < 20000; i++)
    {
        arc_darray_push_back(darray, (void *)&i);
    }

    for (i = 0; i < 10000; i++)
    {
        unsigned end_idx = arc_darray_size(darray) - 1;
        ARC_ASSERT_INT_EQUAL(arc_darray_position(it, end_idx), ARC_SUCCESS);
        arc_darray_erase(it);
    }

    for (i = 0; i < 10000; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((unsigned *)arc_darray_at(darray, i)), i);
    }

    arc_darray_clear(darray);

    for (i = 0; i < 20000; i++)
    {
        arc_darray_push_back(darray, (void *)&i);
    }

    for (i = 20000; i > 0; i-=2)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_position(it, i - 1), ARC_SUCCESS);
        arc_darray_erase(it);
    }

    for (i = 0; i < 10000; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((unsigned *)arc_darray_at(darray, i)), i*2);
    }

    arc_iterator_destroy(it);
    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(destruction_test)
{
    int i;

    arc_darray_t darray = arc_darray_create(sizeof(double));
    
    for (i = 0; i < 20000; i++)
    {
        double data = i;
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&data), 
                             ARC_SUCCESS);
    }

    arc_darray_destroy(darray);
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
    ARC_UNIT_ADD_TEST(iterators_position)
    ARC_UNIT_ADD_TEST(iterators_insertion_front)
    ARC_UNIT_ADD_TEST(iterators_insertion_back)
    ARC_UNIT_ADD_TEST(iterators_insertion_middle)
    ARC_UNIT_ADD_TEST(iterators_erase)
    ARC_UNIT_ADD_TEST(destruction_test)
}

ARC_UNIT_RUN_TESTS()
