/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/slist.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_TEST(size_test)
{
    int i = 10;
    arc_slist_t list = arc_slist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    ARC_ASSERT_TRUE(arc_slist_empty(list));

    ARC_ASSERT_INT_EQUAL(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_slist_size(list), 1);
    
    ARC_ASSERT_FALSE(arc_slist_empty(list));

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_slist_size(list), 11);

    arc_slist_destroy(list);
}

ARC_TEST(push_pop)
{
    int i;
    arc_slist_t list = arc_slist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_slist_empty(list))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_slist_front(list)), i--);

        arc_slist_pop_front(list);
    }

    arc_slist_destroy(list);
}

ARC_TEST(iterators)
{
    int i;
    arc_slist_node_t it;
    arc_slist_t list = arc_slist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;

    for (it = arc_slist_begin(list);
         it != arc_slist_after_end(list); 
         it = arc_slist_node_next(it))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_slist_node_data(it)), i--);
    }

    arc_slist_destroy(list);
}

ARC_TEST(destruction)
{
    int i;

    arc_slist_t list = arc_slist_create(sizeof(double));
    
    ARC_ASSERT_POINTER_NOT_NULL(list);
    
    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    arc_slist_destroy(list);
}

ARC_TEST_FIXTURE()
{
    ARC_ADD_TEST(size_test)
    ARC_ADD_TEST(push_pop)
    ARC_ADD_TEST(iterators)
    ARC_ADD_TEST(destruction)
}

ARC_RUN_TESTS()
