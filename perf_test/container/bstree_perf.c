/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/test/perf.h>
#include <arc/container/bstree.h>
#include <stdlib.h>


arc_bstree_t tree;
int num_elems = 20000;


ARC_PERF_FUNCTION(set_up)
{
    const char * num_elems_str = arc_get_param("-n");

    if (num_elems_str != NULL)
    {
        num_elems = atoi(num_elems_str);
    }
}

ARC_PERF_FUNCTION(create)
{
    tree = arc_bstree_create(sizeof(int), arc_cmp_int);
}

ARC_PERF_TEST(insert)
{
    int i;
    for (i = 0; i < num_elems; i++)
    {
        arc_bstree_insert(tree, &i);
    }
}

ARC_PERF_FUNCTION(destroy)
{
    arc_bstree_destroy(tree);
}

ARC_PERF_FUNCTION(tear_down)
{

}

ARC_PERF_TEST_FIXTURE()
{
    ARC_PERF_ADD_FUNCTION(set_up)

    ARC_PERF_ADD_FUNCTION(create)
    ARC_PERF_ADD_TEST(insert)
    ARC_PERF_ADD_FUNCTION(destroy)

    ARC_PERF_ADD_FUNCTION(tear_down)
}

ARC_PERF_RUN_TESTS()
