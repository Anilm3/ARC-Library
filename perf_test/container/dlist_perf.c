/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/dlist.h>
#include <arc/test/perf.h>
#include <arc/common/defines.h>

#include <string.h>

int num_elems = 20000;
unsigned block_size = 4; 
char * data_block = NULL;
arc_dlist_t dlist;

ARC_PERF_FUNCTION(set_up)
{
    const char * num_elems_str = arc_get_param("-n");
    const char * block_size_str = arc_get_param("-b");

    if (num_elems_str != NULL)
    {
        num_elems = atoi(num_elems_str);
    }

    if (block_size_str != NULL)
    {
        block_size = atoi(block_size_str);
    }

    data_block = malloc(block_size*sizeof(char));
}

ARC_PERF_FUNCTION(create_list)
{
    dlist = arc_dlist_create(block_size);
}

ARC_PERF_TEST(push_front)
{
    int i;
    for (i = 0; i < num_elems; i++)
    {
        arc_dlist_push_front(dlist, data_block);
    }
}

ARC_PERF_TEST(pop_front)
{
    while(!arc_dlist_empty(dlist))
    {
        arc_dlist_pop_front(dlist);
    }
}

ARC_PERF_TEST(push_back)
{
    int i;
    for (i = 0; i < num_elems; i++)
    {
        arc_dlist_push_back(dlist, data_block);
    }
}

ARC_PERF_TEST(pop_back)
{
    while(!arc_dlist_empty(dlist))
    {
        arc_dlist_pop_back(dlist);
    }
}

ARC_PERF_FUNCTION(destroy_list)
{
    arc_dlist_destroy(dlist);
}

ARC_PERF_FUNCTION(tear_down)
{
    free(data_block);
}

ARC_PERF_TEST_FIXTURE()
{
    ARC_PERF_ADD_FUNCTION(set_up)

    ARC_PERF_ADD_FUNCTION(create_list)
    ARC_PERF_ADD_TEST(push_front)
    ARC_PERF_ADD_TEST(pop_front)
    ARC_PERF_ADD_FUNCTION(destroy_list)

    ARC_PERF_ADD_FUNCTION(create_list)
    ARC_PERF_ADD_TEST(push_back)
    ARC_PERF_ADD_TEST(pop_back)
    ARC_PERF_ADD_FUNCTION(destroy_list)

    ARC_PERF_ADD_FUNCTION(tear_down)
}

ARC_PERF_RUN_TESTS()
