/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/test/perf.h>
#include <vector>
#include <cstdlib>


std::vector<int> * vector;
int num_elems = 20000;


ARC_PERF_FUNCTION(set_up)
{
    const char * num_elems_str = arc_get_param("-n");

    if (num_elems_str != NULL)
    {
        num_elems = atoi(num_elems_str);
    }
}

ARC_PERF_FUNCTION(create_vector)
{
    vector = new std::vector<int>();
}

ARC_PERF_TEST(push_back)
{
    for (int i = 0; i < num_elems; i++)
    {
        vector->push_back(i);
    }
}

ARC_PERF_TEST(pop_back)
{
    while(!vector->empty())
    {
        vector->pop_back();
    }
}

ARC_PERF_FUNCTION(destroy_vector)
{
    delete vector;
}

ARC_PERF_FUNCTION(tear_down)
{

}

ARC_PERF_TEST_FIXTURE()
{
    ARC_PERF_ADD_FUNCTION(set_up)

    ARC_PERF_ADD_FUNCTION(create_vector)
    ARC_PERF_ADD_TEST(push_back)
    ARC_PERF_ADD_TEST(pop_back)
    ARC_PERF_ADD_FUNCTION(destroy_vector)

    ARC_PERF_ADD_FUNCTION(tear_down)
}

ARC_PERF_RUN_TESTS()
