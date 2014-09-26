/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <arc/container/darray.h>
#include <arc/container/iterator.h>
#include <arc/test/unit.h>
#include <arc/common/defines.h>

#include <string.h>

ARC_UNIT_TEST(creation_test)
{
    arc_darray_t darray = arc_darray_create(sizeof(int));

    ARC_ASSERT_POINTER_NOT_NULL(darray);

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(empty_test)
{
    int i = 10;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    ARC_ASSERT_TRUE(arc_darray_empty(darray));

    ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_FALSE(arc_darray_empty(darray));

    arc_darray_pop_front(darray);

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(size_test)
{
    int i = 10;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);

    ARC_ASSERT_INT_EQUAL(arc_darray_size(darray), 1);
    
    for (i = 0; i < 10; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    ARC_ASSERT_INT_EQUAL(arc_darray_size(darray), 11);

    for (i = 0; i < 5; i++)
    {
        arc_darray_pop_front(darray);
    }

    ARC_ASSERT_INT_EQUAL(arc_darray_size(darray), 6);

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(push_pop_front_front)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_front(darray)), i--);

        arc_darray_pop_front(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(push_pop_back_back)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 19999;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_back(darray)), i--);

        arc_darray_pop_back(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(push_pop_front_back)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_back(darray)), i++);

        arc_darray_pop_back(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(push_pop_back_front)
{
    int i;
    arc_darray_t darray = arc_darray_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_front(darray)), i++);

        arc_darray_pop_front(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(mixed_push_front_back_test)
{
    int i;

    arc_darray_t darray = arc_darray_create(sizeof(unsigned));
    
    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_front(darray)), i++);

        arc_darray_pop_front(darray);
    }

    arc_darray_destroy(darray);
}

ARC_UNIT_TEST(mixed_push_back_front_test)
{
    int i;

    arc_darray_t darray = arc_darray_create(sizeof(unsigned));
    
    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    i = 0;
    while(!arc_darray_empty(darray))
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_front(darray)), i++);

        arc_darray_pop_front(darray);
    }

    arc_darray_destroy(darray);
}


ARC_UNIT_TEST(indexed_access_test)
{
    int i;

    arc_darray_t darray = arc_darray_create(sizeof(unsigned));
    
    for (i = 100; i >= 0; i--)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_front(darray, (void *)&i), ARC_SUCCESS);
    }

    for (i = 101; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(arc_darray_push_back(darray, (void *)&i), ARC_SUCCESS);
    }

    for (i = 0; i < 200; i++)
    {
        ARC_ASSERT_INT_EQUAL(*((int *)arc_darray_at(darray, (unsigned)i)), i);
    }

    arc_darray_destroy(darray);
}
ARC_UNIT_TEST_FIXTURE()
{
    ARC_UNIT_ADD_TEST(creation_test)
    ARC_UNIT_ADD_TEST(empty_test)
    ARC_UNIT_ADD_TEST(size_test)
    ARC_UNIT_ADD_TEST(push_pop_front_front)
    ARC_UNIT_ADD_TEST(push_pop_back_back)
    ARC_UNIT_ADD_TEST(push_pop_front_back)
    ARC_UNIT_ADD_TEST(push_pop_back_front)
    ARC_UNIT_ADD_TEST(mixed_push_front_back_test)
    ARC_UNIT_ADD_TEST(mixed_push_back_front_test)
    ARC_UNIT_ADD_TEST(indexed_access_test)
}

ARC_UNIT_RUN_TESTS()
