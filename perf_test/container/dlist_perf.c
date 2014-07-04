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

int n;
arc_dlist_t dlist;

ARC_PERF_FUNCTION(set_up)
{
    const char * num_elems = arc_get_param("-n");

    if (num_elems == NULL)
    {
        n = 20000;
    }
    else
    {
        n = atoi(num_elems);
    }

    dlist = arc_dlist_create(sizeof(int));
}

ARC_PERF_TEST(push_front)
{
    int i;
    for (i = 0; i < n; i++)
    {
        arc_dlist_push_front(dlist, (void *)&i);
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
    for (i = 0; i < n; i++)
    {
        arc_dlist_push_back(dlist, (void *)&i);
    }
}

ARC_PERF_TEST(pop_back)
{
    while(!arc_dlist_empty(dlist))
    {
        arc_dlist_pop_back(dlist);
    }
}


ARC_PERF_FUNCTION(tear_down)
{
    arc_dlist_destroy(dlist);
}

ARC_PERF_TEST_FIXTURE()
{
    ARC_PERF_ADD_FUNCTION(set_up)
    ARC_PERF_ADD_TEST(push_front)
    ARC_PERF_ADD_TEST(pop_front)
    ARC_PERF_ADD_FUNCTION(tear_down)

    ARC_PERF_ADD_FUNCTION(set_up)
    ARC_PERF_ADD_TEST(push_back)
    ARC_PERF_ADD_TEST(pop_back)
    ARC_PERF_ADD_FUNCTION(tear_down)
}

ARC_PERF_RUN_TESTS()
