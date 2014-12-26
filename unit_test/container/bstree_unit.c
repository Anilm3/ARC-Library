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

#include <string.h>

int int_cmp_fn(void * a, void * b)
{
    int *a_ = a;
    int *b_ = b;

    return *a_ < *b_;
}
int double_cmp_fn(void * a, void * b)
{
    double *a_ = a;
    double *b_ = b;

    return *a_ < *b_;
}
ARC_UNIT_TEST(creation)
{
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), int_cmp_fn);

    ARC_ASSERT_POINTER_NOT_NULL(bstree);

    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(empty)
{
    int i = 10;
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), int_cmp_fn);

    ARC_ASSERT_TRUE(arc_bstree_empty(bstree));

    ARC_ASSERT_INT_EQ(arc_bstree_insert(bstree, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_bstree_empty(bstree));

    arc_bstree_destroy(bstree);
}

ARC_UNIT_TEST(size)
{
    int i = 10;
    arc_bstree_t bstree = arc_bstree_create(sizeof(int), int_cmp_fn);

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

ARC_UNIT_TEST(destruction)
{
    int i;

    arc_bstree_t bstree = arc_bstree_create(sizeof(int), double_cmp_fn);
    
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
    ARC_UNIT_ADD_TEST(destruction)
}

ARC_UNIT_RUN_TESTS()
