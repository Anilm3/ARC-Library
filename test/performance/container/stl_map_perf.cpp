/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/test/perf.h>
#include <cstdlib>
#include <cstdio>
#include <map>

std::map<int,int> * tree;
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

    values = (int *)malloc(sizeof(int) * ((size_t)num_elems));

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
    tree = new std::map<int,int>;
}

ARC_PERF_TEST(insert)
{
    int i;
    for (i = 0; i < num_elems; i++)
    {
        tree->insert ( std::pair<int,int>(i, 1) );
    }
}

ARC_PERF_TEST(find)
{
    int i;
    for (i = num_elems - 1; i >= 0; i--)
    {
        tree->find(i);
    }
}

ARC_PERF_TEST(random_insert)
{
    int i;

    srand(0);

    for (i = 0; i < num_elems; i++)
    {
        tree->insert(std::pair<int,int>(values[rand() % num_elems], 1));
    }
}


ARC_PERF_FUNCTION(tear_down)
{
    delete tree;
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
