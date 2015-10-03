/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <arc/common/defines.h>
#include <arc/test/perf.h>
#include <arc/container/htable.h>
#include <arc/container/htable_def.h>
#include <stdlib.h>
#include <stdio.h>

arc_htable_t htable;
int num_elems = 20000;

arc_hkey_t hash_function(const void *key, size_t size)
{
    ARC_UNUSED(size);
    return (arc_hkey_t)*((const int *)key);;
}

ARC_PERF_FUNCTION(global_set_up)
{
    const char * num_elems_str = arc_get_param("-n");

    if (num_elems_str != NULL)
    {
        num_elems = atoi(num_elems_str);
    }
}

ARC_PERF_FUNCTION(global_tear_down)
{

}

ARC_PERF_FUNCTION(set_up)
{
    htable = arc_htable_create(100, sizeof(int), sizeof(int), hash_function);
}

ARC_PERF_TEST(insert)
{
    int i;
    for (i = 0; i < num_elems; i++)
    {
        arc_htable_insert(htable, &i, &i);
    }
}

ARC_PERF_TEST(rehash)
{
/*
    printf("%lf\n", arc_htable_variance(htable));
    printf("%u\n", arc_htable_max(htable));
*/
    arc_htable_rehash(htable, (size_t)num_elems);
/*
    printf("%lf\n", arc_htable_variance(htable));
    printf("%u\n", arc_htable_max(htable));
*/
}

ARC_PERF_TEST(retrieve)
{
    int i;
    for (i = 0; i < num_elems; i++)
    {
        arc_htable_retrieve(htable, &i);
    }
}

ARC_PERF_FUNCTION(tear_down)
{
    arc_htable_destroy(htable);
}

ARC_PERF_TEST_FIXTURE()
{
    ARC_PERF_ADD_FUNCTION(global_set_up)

    ARC_PERF_ADD_FUNCTION(set_up)
    ARC_PERF_ADD_TEST(insert)
    ARC_PERF_ADD_TEST(retrieve)
    ARC_PERF_ADD_FUNCTION(tear_down)

    ARC_PERF_ADD_FUNCTION(set_up)
    ARC_PERF_ADD_TEST(insert)
    ARC_PERF_ADD_TEST(rehash)
    ARC_PERF_ADD_TEST(retrieve)
    ARC_PERF_ADD_FUNCTION(tear_down)

    ARC_PERF_ADD_FUNCTION(global_tear_down)
}

ARC_PERF_RUN_TESTS()
