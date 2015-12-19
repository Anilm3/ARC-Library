/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/avltree.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
/*
                               16
               08                              24
       04              12              20              28
   02      06      10      14      18      22      26      30
 01  03  05  07  09  11  13  15  17  19  21  23  25  27  29  31
*/
static unsigned tree_data[] = {16,  8, 24,  4, 12, 20, 28,  2,
                                6, 10, 14, 18, 22, 26, 30,  1,
                                3,  5,  7,  9, 11, 13, 15, 17,
                               19, 21, 23, 25, 27, 29, 31};

ARC_UNIT_TEST(random)
{
    int i;
    struct timeval tv;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);
    gettimeofday(&tv, NULL);
    srand((unsigned)tv.tv_usec);
    for (i = 0; i < 50; i++)
    {
        int value = rand() % 50;
        arc_avltree_insert(avltree, (void *)&value);
    }
}
ARC_UNIT_TEST(creation)
{
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);

    ARC_ASSERT_POINTER_NOT_NULL(avltree);

    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(empty)
{
    int i = 10;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);

    ARC_ASSERT_TRUE(arc_avltree_empty(avltree));

    ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_avltree_empty(avltree));

    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(size)
{
    int i = 10;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);

    ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQ(arc_avltree_size(avltree), 1);

    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQ(arc_avltree_size(avltree), 11);

    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(insertion)
{
    unsigned i;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(avltree);

    ARC_ASSERT_POINTER_NOT_NULL(avltree);

    for (i = 0; i < sizeof(tree_data)/sizeof(unsigned); i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&tree_data[i]),
                          ARC_SUCCESS);
    }

    arc_avltree_before_begin(it);

    i = 1;
    while(arc_avltree_next(it))
    {
        ARC_ASSERT_INT_EQ(*((unsigned *)arc_avltree_data(it)), i);
        i++;
    }

    arc_iterator_destroy(it);
    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(find)
{
    unsigned i;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);

    ARC_ASSERT_POINTER_NOT_NULL(avltree);

    for (i = 0; i < sizeof(tree_data)/sizeof(unsigned); i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&tree_data[i]),
                          ARC_SUCCESS);
    }

    for (i = 1; i < 32; i++)
    {
        ARC_ASSERT_TRUE(arc_avltree_find(avltree, (void *)&i));
    }

    for (i = 32; i < 64; i++)
    {
        ARC_ASSERT_FALSE(arc_avltree_find(avltree, (void *)&i));
    }

    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(remove)
{
    unsigned i, val;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(avltree);
    unsigned result[] = { 3,  4,  5,  8,  9, 11, 13, 14, 15, 17, 18,
                         19, 21, 22, 23, 24, 25, 26, 27, 29, 30, 31};

    for (i = 0; i < sizeof(tree_data)/sizeof(unsigned); i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&tree_data[i]),
                          ARC_SUCCESS);
    }

    /* Remove leaf */
    val = 1;
    arc_avltree_remove(avltree, (void *)&val);

    val = 7;
    arc_avltree_remove(avltree, (void *)&val);

    /* Remove intermediate node with two leafs */
    val = 10;
    arc_avltree_remove(avltree, (void *)&val);

    /* Remove intermediate node with left leaf */
    val = 2;
    arc_avltree_remove(avltree, (void *)&val);

    /* Remove intermediate node with right leaf */
    val = 6;
    arc_avltree_remove(avltree, (void *)&val);

    /* Remove intermediate node with two intermediate nodes */
    val = 12;
    arc_avltree_remove(avltree, (void *)&val);

    /* Remove intermediate node with left intermediate node */
    val = 20;
    arc_avltree_remove(avltree, (void *)&val);

    /* Remove intermediate node with right intermediate node */
    val = 28;
    arc_avltree_remove(avltree, (void *)&val);

    /* Remove root */
    val = 16;
    arc_avltree_remove(avltree, (void *)&val);


    arc_avltree_before_begin(it);

    i = 0;
    while(arc_avltree_next(it))
    {
        ARC_ASSERT_INT_EQ(*((unsigned *)arc_avltree_data(it)), result[i]);
        i++;
    }

    arc_iterator_destroy(it);
    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(iterators_forward)
{
    /* this test generates the equivalent of a list, so we need to be smarter */
    unsigned i;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(avltree);

    ARC_ASSERT_POINTER_NOT_NULL(avltree);

    for (i = 0; i < sizeof(tree_data)/sizeof(unsigned); i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&tree_data[i]),
                          ARC_SUCCESS);
    }

    i = 1;

    arc_avltree_before_begin(it);

    while(arc_avltree_next(it))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_avltree_data(it)), i);
        i++;
    }

    ARC_ASSERT_INT_EQ(i, 32);

    arc_iterator_destroy(it);
    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(iterators_backward)
{
    /* this test generates the equivalent of a list, so we need to be smarter */
    unsigned i;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(avltree);

    ARC_ASSERT_POINTER_NOT_NULL(avltree);

    for (i = 0; i < sizeof(tree_data)/sizeof(unsigned); i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&tree_data[i]),
                          ARC_SUCCESS);
    }

    i = 31;

    arc_avltree_after_end(it);

    while(arc_avltree_previous(it))
    {
        ARC_ASSERT_INT_EQ(*((int *)arc_avltree_data(it)), i);
        i--;
    }

    ARC_ASSERT_INT_EQ(i, 0);

    arc_iterator_destroy(it);
    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(iterators_position)
{
    /* this test generates the equivalent of a list, so we need to be smarter */
    unsigned i;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(avltree);

    ARC_ASSERT_POINTER_NOT_NULL(avltree);

    for (i = 0; i < sizeof(tree_data)/sizeof(unsigned); i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&tree_data[i]),
                          ARC_SUCCESS);
    }

    for (i = 1; i < 32;  i++)
    {
        ARC_ASSERT_TRUE(arc_avltree_position(it, (void *)&i));
        ARC_ASSERT_INT_EQ(*((int *)arc_avltree_data(it)), i);
    }

    for (i = 32; i < 64;  i++)
    {
        ARC_ASSERT_FALSE(arc_avltree_position(it, (void *)&i));
    }

    arc_iterator_destroy(it);
    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(iterators_remove)
{
    unsigned i, val;
    arc_avltree_t avltree = arc_avltree_create(sizeof(int), arc_cmp_int);
    arc_iterator_t it = arc_iterator_create(avltree);
    unsigned result[] = { 3,  4,  5,  8,  9, 11, 13, 14, 15, 17, 18,
                         19, 21, 22, 23, 24, 25, 26, 27, 29, 30, 31};

    for (i = 0; i < sizeof(tree_data)/sizeof(unsigned); i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&tree_data[i]),
                          ARC_SUCCESS);
    }

    /* Remove leaf */
    val = 1;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);

    val = 7;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);

    /* Remove intermediate node with two leafs */
    val = 10;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);

    /* Remove intermediate node with left leaf */
    val = 2;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);

    /* Remove intermediate node with right leaf */
    val = 6;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);

    /* Remove intermediate node with two intermediate nodes */
    val = 12;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);

    /* Remove intermediate node with left intermediate node */
    val = 20;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);

    /* Remove intermediate node with right intermediate node */
    val = 28;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);

    /* Remove root */
    val = 16;
    arc_avltree_position(it, (void *)&val);
    arc_avltree_erase(it);


    arc_avltree_before_begin(it);

    i = 0;
    while(arc_avltree_next(it))
    {
        ARC_ASSERT_INT_EQ(*((unsigned *)arc_avltree_data(it)), result[i]);
        i++;
    }


    arc_iterator_destroy(it);
    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST(destruction)
{
    unsigned i;

    arc_avltree_t avltree = arc_avltree_create(sizeof(double), arc_cmp_double);

    for (i = 0; i < sizeof(tree_data)/sizeof(unsigned); i++)
    {
        ARC_ASSERT_INT_EQ(arc_avltree_insert(avltree, (void *)&tree_data[i]),
                          ARC_SUCCESS);
    }

    arc_avltree_destroy(avltree);
}

ARC_UNIT_TEST_FIXTURE()
{
    /*ARC_UNIT_ADD_TEST(random)*/
    ARC_UNIT_ADD_TEST(creation)
    ARC_UNIT_ADD_TEST(empty)
    ARC_UNIT_ADD_TEST(size)
    ARC_UNIT_ADD_TEST(insertion)
    ARC_UNIT_ADD_TEST(find)
    ARC_UNIT_ADD_TEST(remove)
    ARC_UNIT_ADD_TEST(iterators_forward)
    ARC_UNIT_ADD_TEST(iterators_backward)
    ARC_UNIT_ADD_TEST(iterators_position)
    ARC_UNIT_ADD_TEST(iterators_remove)
    ARC_UNIT_ADD_TEST(destruction)
}

ARC_UNIT_RUN_TESTS()
