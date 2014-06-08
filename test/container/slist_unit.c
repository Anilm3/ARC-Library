#include <stdio.h>
#include <arc/container/slist.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

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
    arc_slist_t list = arc_slist_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(list);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_slist_push_front(list, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    arc_slist_node_t it;

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
    ARC_ADD_TEST(push_pop)
    ARC_ADD_TEST(iterators)
    ARC_ADD_TEST(destruction)
}

ARC_RUN_TESTS()