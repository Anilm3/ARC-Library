/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/dlist.h>
#include <arc/container/iterator.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_UNIT_TEST(size_test)
{
    int i = 10;
    arc_dlist_t list = arc_dlist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    ARC_ASSERT_TRUE(arc_dlist_empty(list));

    ARC_ASSERT_INT_EQUAL(arc_dlist_push_front(list, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_dlist_size(list), 1);
    
    ARC_ASSERT_FALSE(arc_dlist_empty(list));

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_dlist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_dlist_size(list), 11);

    arc_dlist_destroy(list);
}

ARC_UNIT_TEST(push_pop_front_front)
{
    int i;
    arc_dlist_t list = arc_dlist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_dlist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_dlist_empty(list))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_dlist_front(list)), i--);

        arc_dlist_pop_front(list);
    }

    arc_dlist_destroy(list);
}

ARC_UNIT_TEST(push_pop_back_back)
{
    int i;
    arc_dlist_t list = arc_dlist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_dlist_push_back(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_dlist_empty(list))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_dlist_back(list)), i--);

        arc_dlist_pop_back(list);
    }

    arc_dlist_destroy(list);
}

ARC_UNIT_TEST(push_pop_back_front)
{
    int i;
    arc_dlist_t list = arc_dlist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 1; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_dlist_push_back(list, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_dlist_empty(list))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_dlist_front(list)), i++);

        arc_dlist_pop_front(list);
    }

    arc_dlist_destroy(list);
}

ARC_UNIT_TEST(push_pop_front_back)
{
    int i;
    arc_dlist_t list = arc_dlist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_dlist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_dlist_empty(list))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_dlist_back(list)), i++);

        arc_dlist_pop_back(list);
    }

    arc_dlist_destroy(list);
}

ARC_UNIT_TEST(iterators_forward)
{
    int i;
    arc_dlist_t list = arc_dlist_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(list);

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_dlist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;

    arc_dlist_before_begin(it);

    while(arc_dlist_next(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_dlist_data(it)), i--);
    }

    arc_iterator_destroy(it);
    arc_dlist_destroy(list);
}

ARC_UNIT_TEST(iterators_backward)
{
    int i;
    arc_dlist_t list = arc_dlist_create(sizeof(int));
    arc_iterator_t it = arc_iterator_create(list);

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_dlist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 0;

    arc_dlist_after_end(it);

    while(arc_dlist_previous(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_dlist_data(it)), i++);
    }

    arc_iterator_destroy(it);
    arc_dlist_destroy(list);
}


ARC_UNIT_TEST(destruction)
{
    int i;

    arc_dlist_t list = arc_dlist_create(sizeof(double));
    
    ARC_ASSERT_POINTER_NOT_NULL(list);
    
    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_dlist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    arc_dlist_destroy(list);
}

ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(size_test)
    ARC_UNIT_ADD_TEST(push_pop_front_front)
    ARC_UNIT_ADD_TEST(push_pop_back_back)
    ARC_UNIT_ADD_TEST(push_pop_back_front)
    ARC_UNIT_ADD_TEST(push_pop_front_back)
    ARC_UNIT_ADD_TEST(iterators_forward)
    ARC_UNIT_ADD_TEST(iterators_backward)
    ARC_UNIT_ADD_TEST(destruction)
}

ARC_UNIT_RUN_TESTS()
