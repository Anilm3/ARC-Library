/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/deque2.h>
#include <arc/test/perf.h>
#include <arc/common/defines.h>

#include <string.h>

arc_deque2_t deque;

ARC_PERF_FUNCTION(set_up)
{
    deque = arc_deque2_create(sizeof(int));
}

ARC_PERF_TEST(push_front)
{
    int i;
    for (i = 0; i < 20000; i++)
    {
        arc_deque2_push_front(deque, (void *)&i);
    }
}

ARC_PERF_TEST(pop_front)
{
    while(!arc_deque2_empty(deque))
    {
        arc_deque2_pop_front(deque);
    }
}

ARC_PERF_TEST(push_back)
{
    int i;
    for (i = 0; i < 20000; i++)
    {
        arc_deque2_push_back(deque, (void *)&i);
    }
}

ARC_PERF_TEST(pop_back)
{
    while(!arc_deque2_empty(deque))
    {
        arc_deque2_pop_back(deque);
    }
}

ARC_PERF_TEST(pop_back2)
{
    int i;
    for (i = 0; i < 20000; i++)
    {
        arc_deque2_pop_back(deque);
    }
}

ARC_PERF_FUNCTION(tear_down)
{
    arc_deque2_destroy(deque);
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

    ARC_PERF_ADD_FUNCTION(set_up)
    ARC_PERF_ADD_TEST(push_back)
    ARC_PERF_ADD_TEST(pop_back2)
    ARC_PERF_ADD_FUNCTION(tear_down)
}

ARC_PERF_RUN_TESTS()
