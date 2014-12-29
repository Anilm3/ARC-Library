/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/bstree.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

ARC_UNIT_TEST(creation)
{
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), arc_cmp_int);

    ARC_ASSERT_POINTER_NOT_NULL(bstree);

    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(empty)
{
    int i = 10;
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), arc_cmp_int);

    ARC_ASSERT_TRUE(arc_bstree_empty(bstree));

    ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_bstree_empty(bstree));

    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(size)
{
    int i = 10;
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), arc_cmp_int);

    ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQ(arc_bstree_size(bstree), 1);

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQ(arc_bstree_size(bstree), 11);

/*
    for (i = 0; i < 5; i++)
    {
        arc_bstree_pop_front(bstree);
    }

    ARC_ASSERT_INT_EQ(arc_bstree_size(bstree), 6);
*/
    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(pseudorandom_insertions)
{
    unsigned i, data;
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(bstree);

    /* 0 for repeatable random sequence */
    srand(0);

    ARC_ASSERT_POINTER_NOT_NULL(bstree);

    for (i = 0; i < 20000; i++)
    {
        do
        {
            data = (unsigned)rand();
        }
        while (arc_bstree_insert(bstree, (void *)&data) == ARC_DUPLICATE);
    }

    i = 0;

    arc_bstree_before_begin(it);

    data = 0;
    while(arc_bstree_next(it))
    {
        ARC_ASSERT_INT_GE(*((unsigned *)arc_bstree_data(it)), data);
        data = *((unsigned *)arc_bstree_data(it));
        i++;
    }
    ARC_ASSERT_INT_EQ(i, 20000);

    arc_bstree_clear(bstree);

    /* 1729 for repeatable random sequence */
    srand(1729);

    ARC_ASSERT_POINTER_NOT_NULL(bstree);

    for (i = 0; i < 20000; i++)
    {
        do
        {
            data = (unsigned)rand();
        }
        while (arc_bstree_insert(bstree, (void *)&data) == ARC_DUPLICATE);
    }

    i = 0;

    arc_bstree_before_begin(it);

    data = 0;
    while(arc_bstree_next(it))
    {
        ARC_ASSERT_INT_GE(*((unsigned *)arc_bstree_data(it)), data);
        data = *((unsigned *)arc_bstree_data(it));
        i++;
    }
    ARC_ASSERT_INT_EQ(i, 20000);

    arc_iterator_destroy(it);
    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(find)
{
    int i;
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), arc_cmp_int);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&i), ARC_SUCCESS);
    }

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_TRUE(arc_bstree_find(bstree, (void *)&i));
    }

    for (i = 20000; i < 20100; i++)
    {
        ARC_ASSERT_FALSE(arc_bstree_find(bstree, (void *)&i));
    }

    arc_bstree_destroy(bstree);
}

#define ARCSIZE 20000
ARC_UNIT_TEST(remove)
{
    unsigned i, val;
    unsigned visited[20000];
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(bstree);

    srand(0);

    memset(visited, 0, sizeof(unsigned)*20000);

    for (i = 0; i < 20000; i++)
    {
        while(1)
        {
            val = (unsigned)(rand() % 20000);
            if (!visited[val])
            {
                ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&val),
                                  ARC_SUCCESS);
                visited[val] = 1;
                break;
            }
        }
    }

    memset(visited, 0, sizeof(unsigned)*20000);

    for (i = 0; i < 10000; i++)
    {
        while(1)
        {
            val = (unsigned)(rand() % 10000);
            if (!visited[val])
            {
                arc_bstree_remove(bstree, (void *)&val);
                visited[val] = 1;
                break;
            }
        }
    }

    i = 19999;

    arc_bstree_after_end(it);

    while(arc_bstree_previous(it))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_bstree_data(it)), i--);
    }

    ARC_ASSERT_INT_EQ(i, 9999);

    i = 10000;

    arc_bstree_before_begin(it);

    while(arc_bstree_next(it))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_bstree_data(it)), i++);
    }

    ARC_ASSERT_INT_EQ(i, 20000);

    for (i = 0; i < 10000; i++)
    {
        ARC_ASSERT_FALSE(arc_bstree_find(bstree, (void *)&i));
    }

    for (i = 10000; i < 20000; i++)
    {
        ARC_ASSERT_TRUE(arc_bstree_find(bstree, (void *)&i));
    }

    arc_iterator_destroy(it);
    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(iterators_forward)
{
    /* this test generates the equivalent of a list, so we need to be smarter */
    int i;
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(bstree);

    ARC_ASSERT_POINTER_NOT_NULL(bstree);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&i), ARC_SUCCESS);
    }

    i = 0;

    arc_bstree_before_begin(it);

    while(arc_bstree_next(it))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_bstree_data(it)), i++);
    }

    ARC_ASSERT_INT_EQ(i, 20000);

    arc_iterator_destroy(it);
    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(iterators_backward)
{
    /* this test generates the equivalent of a list, so we need to be smarter */
    int i;
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(bstree);

    ARC_ASSERT_POINTER_NOT_NULL(bstree);

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;

    arc_bstree_after_end(it);

    while(arc_bstree_previous(it))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_bstree_data(it)), i--);
    }

    ARC_ASSERT_INT_EQ(i, -1);

    arc_iterator_destroy(it);
    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(destruction)
{
    int i;

    arc_bstree_t bstree = arc_bstree_create(sizeof(double), arc_cmp_double);

    for (i = 0; i < 20000; i++)
    {
        double data = i;
        ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&data),
                             ARC_SUCCESS);
    }

    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(creation)
    ARC_UNIT_ADD_TEST(empty)
    ARC_UNIT_ADD_TEST(size)
    ARC_UNIT_ADD_TEST(pseudorandom_insertions)
    ARC_UNIT_ADD_TEST(find)
    ARC_UNIT_ADD_TEST(remove)
    ARC_UNIT_ADD_TEST(iterators_forward)
    ARC_UNIT_ADD_TEST(iterators_backward)
    ARC_UNIT_ADD_TEST(destruction)
}

ARC_UNIT_RUN_TESTS()
