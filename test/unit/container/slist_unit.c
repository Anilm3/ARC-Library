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

ARC_UNIT_TEST(size)
{
    int i = 10;
    arc_slist_t list = arc_slist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    ARC_ASSERT_TRUE(arc_slist_empty(list));

    ARC_ASSERT_INT_EQ(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQ(arc_slist_size(list), 1);
    
    ARC_ASSERT_FALSE(arc_slist_empty(list));

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQ(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQ(arc_slist_size(list), 11);

    arc_slist_destroy(list);
}

ARC_UNIT_TEST(push_pop)
{
    int i;
    arc_slist_t list = arc_slist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQ(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_slist_empty(list))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_slist_front(list)), i--);

        arc_slist_pop_front(list);
    }

    arc_slist_destroy(list);
}

ARC_UNIT_TEST(iterators)
{
    int i;
    arc_slist_t list = arc_slist_create(sizeof(int));
    arc_slist_iterator_t it = arc_slist_iterator_create(list);

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQ(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;

    arc_slist_before_begin(it);

    while(arc_slist_next(it))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_slist_data(it)), i--);
    }

    arc_slist_iterator_destroy(it);
    arc_slist_destroy(list);
}

ARC_UNIT_TEST(destruction)
{
    int i;

    arc_slist_t list = arc_slist_create(sizeof(double));
    
    ARC_ASSERT_POINTER_NOT_NULL(list);
    
    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQ(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    arc_slist_destroy(list);
}

ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(size)
    ARC_UNIT_ADD_TEST(push_pop)
    ARC_UNIT_ADD_TEST(iterators)
    ARC_UNIT_ADD_TEST(destruction)
}

ARC_UNIT_RUN_TESTS()
