/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/htable.h>
#include <arc/test/unit.h>
#include <arc/type/hash.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_UNIT_TEST(size)
{
    int i = 10;
    arc_htable_t htable = arc_htable_create(32,
                                            sizeof(int),
                                            arc_cmp_int,
                                            arc_hash_pearson);

    ARC_ASSERT_POINTER_NOT_NULL(htable);

    ARC_ASSERT_TRUE(arc_htable_empty(htable));

    ARC_ASSERT_INT_EQ(arc_htable_insert(htable, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQ(arc_htable_size(htable), 1);

    ARC_ASSERT_FALSE(arc_htable_empty(htable));

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQ(arc_htable_insert(htable, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQ(arc_htable_size(htable), 11);

    arc_htable_destroy(htable);
}

ARC_UNIT_TEST(retrieval)
{
    int i = 10;
    arc_htable_t htable = arc_htable_create(32,
                                            sizeof(int),
                                            arc_cmp_int,
                                            arc_hash_pearson);

    ARC_ASSERT_POINTER_NOT_NULL(htable);

    ARC_ASSERT_TRUE(arc_htable_empty(htable));

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQ(arc_htable_insert(htable, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQ(arc_htable_size(htable), 10);

    for (i = 0; i < 10; i++)
    {
        int *data = arc_htable_retrieve(htable, (void *)&i);
        ARC_ASSERT_INT_EQ(*data, i);
    }

    arc_htable_destroy(htable);
}

ARC_UNIT_TEST(removal)
{
    int i = 10;
    arc_htable_t htable = arc_htable_create(32,
                                            sizeof(int),
                                            arc_cmp_int,
                                            arc_hash_pearson);

    ARC_ASSERT_POINTER_NOT_NULL(htable);

    ARC_ASSERT_TRUE(arc_htable_empty(htable));

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQ(arc_htable_insert(htable, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQ(arc_htable_size(htable), 10);

    for (i = 0; i < 10; i++)
    {
        arc_htable_remove(htable, (void *)&i);

        ARC_ASSERT_POINTER_NULL(arc_htable_retrieve(htable, (void *)&i));
    }

    arc_htable_destroy(htable);
}

/* TODO: Add rehashing unit test to which doesn't lead to perfect hash */
/*ARC_UNIT_TEST(rehash)*/
/*{*/
    /*int i = 10;*/
    /*arc_htable_t htable = arc_htable_create(32,*/
                                            /*sizeof(int),*/
                                            /*arc_cmp_int,*/
                                            /*arc_hash_pearson);*/

    /*ARC_ASSERT_POINTER_NOT_NULL(htable);*/

    /*ARC_ASSERT_TRUE(arc_htable_empty(htable));*/

    /*for (i = 0; i < 100; i++)*/
    /*{*/
        /*ARC_ASSERT_INT_EQ(arc_htable_insert(htable, (void *)&i), ARC_SUCCESS);*/
    /*}*/

    /*ARC_ASSERT_INT_EQ(arc_htable_size(htable), 100);*/

    /*ARC_ASSERT_INT_EQ(arc_htable_rehash(htable, 100), ARC_SUCCESS);*/

    /*for (i = 0; i < 100; i++)*/
    /*{*/
        /*int *data = arc_htable_retrieve(htable, (void *)&i);*/
        /*ARC_ASSERT_INT_EQ(*data, i);*/
    /*}*/

    /*arc_htable_destroy(htable);*/
/*}*/

ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(size)
    ARC_UNIT_ADD_TEST(retrieval)
    ARC_UNIT_ADD_TEST(removal)
    /*ARC_UNIT_ADD_TEST(rehash)*/
}

ARC_UNIT_RUN_TESTS()
