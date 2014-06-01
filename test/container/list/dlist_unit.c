#include <stdio.h>
#include <arc/container/list/dlist.h>

int main()
{
    int i;
    arc_dlist_t list;

    list = arc_dlist_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        arc_dlist_push_front(list, (void *)&i);
    }

    i = 19999;
    while(!arc_dlist_empty(list))
    {
        if (*((int *)arc_dlist_front(list)) != i--)
        {
            printf("Error on list element comparison \n");
        }
        arc_dlist_pop_front(list);
    }

    arc_dlist_destroy(list);

    list = arc_dlist_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        arc_dlist_push_back(list, (void *)&i);
    }

    i = 19999;
    while(!arc_dlist_empty(list))
    {
        if (*((int *)arc_dlist_back(list)) != i--)
        {
            printf("Error on list element comparison \n");
        }
        arc_dlist_pop_back(list);
    }

    arc_dlist_destroy(list);

    list = arc_dlist_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        arc_dlist_push_back(list, (void *)&i);
    }

    i = 0;
    while(!arc_dlist_empty(list))
    {
        if (*((int *)arc_dlist_front(list)) != i++)
        {
            printf("Error on list element comparison \n");
        }
        arc_dlist_pop_front(list);
    }

    arc_dlist_destroy(list);

    list = arc_dlist_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        arc_dlist_push_front(list, (void *)&i);
    }

    i = 0;
    while(!arc_dlist_empty(list))
    {
        if (*((int *)arc_dlist_back(list)) != i++)
        {
            printf("Error on list element comparison \n");
        }
        arc_dlist_pop_back(list);
    }

    arc_dlist_destroy(list);

    list = arc_dlist_create(sizeof(double));

    for (i = 0; i < 20000; i++)
    {
        double whatever = i + 1e6;
        arc_dlist_push_front(list, (void *)&whatever);
    }

    arc_dlist_destroy(list);

    return 0;
}