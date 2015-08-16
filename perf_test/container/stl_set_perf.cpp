/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/test/perf.h>
#include <set>
#include <cstdlib>


std::set<int> * set;
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
    set = new std::set<int>();
}

ARC_PERF_TEST(insert)
{
    for (int i = 0; i < num_elems; i++)
    {
        set->insert(i);
    }
}

ARC_PERF_FUNCTION(destroy)
{
    delete set;
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
