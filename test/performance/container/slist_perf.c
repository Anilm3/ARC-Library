/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/slist.h>
#include <arc/test/perf.h>
#include <arc/common/defines.h>

#include <string.h>

arc_slist_t slist;

ARC_PERF_FUNCTION(set_up)
{
    slist = arc_slist_create(sizeof(int));
}

ARC_PERF_TEST(push_front)
{
    int i;
    for (i = 0; i < 20000; i++)
    {
        arc_slist_push_front(slist, (void *)&i);
    }
}

ARC_PERF_TEST(pop_front)
{
    while(!arc_slist_empty(slist))
    {
        arc_slist_pop_front(slist);
    }
}

ARC_PERF_FUNCTION(tear_down)
{
    arc_slist_destroy(slist);
}

ARC_PERF_TEST_FIXTURE()
{
    ARC_PERF_ADD_FUNCTION(set_up)
    ARC_PERF_ADD_TEST(push_front)
    ARC_PERF_ADD_TEST(pop_front)
    ARC_PERF_ADD_FUNCTION(tear_down)
}

ARC_PERF_RUN_TESTS()
