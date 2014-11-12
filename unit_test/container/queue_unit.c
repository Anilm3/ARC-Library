/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/queue.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_UNIT_TEST(creation_test)
{
    arc_queue_t queue = arc_queue_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(queue);

    arc_queue_destroy(queue);
}

ARC_UNIT_TEST(empty_test)
{
    int i = 10;
    arc_queue_t queue = arc_queue_create(sizeof(int));

    ARC_ASSERT_TRUE(arc_queue_empty(queue));

    ARC_ASSERT_INT_EQ(arc_queue_push(queue, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_queue_empty(queue));

    arc_queue_pop(queue);

    arc_queue_destroy(queue);
}

ARC_UNIT_TEST(size_test)
{
    int i = 10;
    arc_queue_t queue = arc_queue_create(sizeof(int));

    ARC_ASSERT_INT_EQ(arc_queue_push(queue, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQ(arc_queue_size(queue), 1);
    
    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQ(arc_queue_push(queue, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQ(arc_queue_size(queue), 11);

    for (i = 0; i < 5; i++)
    {
        arc_queue_pop(queue);
    }

    ARC_ASSERT_INT_EQ(arc_queue_size(queue), 6);

    arc_queue_destroy(queue);
}

ARC_UNIT_TEST(push_pop_test)
{
    int i;
    arc_queue_t queue = arc_queue_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQ(arc_queue_push(queue, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_queue_empty(queue))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_queue_front(queue)), i++);

        arc_queue_pop(queue);
    }

    arc_queue_destroy(queue);
}

ARC_UNIT_TEST(destruction_test)
{
    int i;

    arc_queue_t queue = arc_queue_create(sizeof(double));
    
    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQ(arc_queue_push(queue, (void *)&i), ARC_SUCCESS);
    }

    arc_queue_destroy(queue);
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
