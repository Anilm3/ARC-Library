/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/test/perf.h>
#include <arc/container/avltree.h>
#include <stdlib.h>
#include <stdio.h>

arc_avltree_t tree;
int *values;
int num_elems = 20000;

ARC_PERF_FUNCTION(global_set_up)
{
    int i;
    const char * num_elems_str = arc_get_param("-n");

    if (num_elems_str != NULL)
    {
        num_elems = atoi(num_elems_str);
    }

    values = malloc(sizeof(int) * ((size_t)num_elems));

    for (i = 0; i < num_elems; i++)
    {
        values[i] = i;
    }
}

ARC_PERF_FUNCTION(global_tear_down)
{
    free(values);
}

ARC_PERF_FUNCTION(set_up)
{
    tree = arc_avltree_create(sizeof(int), arc_cmp_int);
}

ARC_PERF_TEST(insert)
{
    int i;
    for (i = 0; i < num_elems; i++)
    {
        arc_avltree_insert(tree, &i);
    }
}

ARC_PERF_TEST(find)
{
    int i;
    for (i = num_elems - 1; i >= 0; i--)
    {
        arc_avltree_find(tree, &i);
    }
}

ARC_PERF_TEST(random_insert)
{
    int i;

    srand(0);

    for (i = 0; i < num_elems; i++)
    {
        arc_avltree_insert(tree, &values[rand() % num_elems]);
    }
}


ARC_PERF_FUNCTION(tear_down)
{
    arc_avltree_destroy(tree);
}

ARC_PERF_TEST_FIXTURE()
{
    ARC_PERF_ADD_FUNCTION(global_set_up)

    ARC_PERF_ADD_FUNCTION(set_up)
    ARC_PERF_ADD_TEST(insert)
    ARC_PERF_ADD_TEST(find)
    ARC_PERF_ADD_FUNCTION(tear_down)

    ARC_PERF_ADD_FUNCTION(set_up)
    ARC_PERF_ADD_TEST(random_insert)
    ARC_PERF_ADD_TEST(find)
    ARC_PERF_ADD_FUNCTION(tear_down)

    ARC_PERF_ADD_FUNCTION(global_tear_down)
}

ARC_PERF_RUN_TESTS()
