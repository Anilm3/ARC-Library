/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/test/perf.h>
#include <deque>

std::deque<int> * deque;

ARC_PERF_FUNCTION(set_up)
{
    deque = new std::deque<int>();
}

ARC_PERF_TEST(push_front)
{
    for (int i = 0; i < 20000; i++)
    {
        deque->push_front(i);
    }
}

ARC_PERF_TEST(pop_front)
{
    while(!deque->empty())
    {
        deque->pop_front();
    }
}

ARC_PERF_TEST(push_back)
{

    for (int i = 0; i < 20000; i++)
    {
        deque->push_back(i);
    }
}

ARC_PERF_TEST(pop_back)
{
    while(!deque->empty())
    {
        deque->pop_back();
    }
}


ARC_PERF_FUNCTION(tear_down)
{
    delete deque;
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
