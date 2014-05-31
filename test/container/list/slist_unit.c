#include <stdio.h>
#include <arc/container/list/slist.h>

int main()
{
    int i;
    arc_slist_t list = arc_slist_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        arc_slist_push_front(list, (void *)&i);
    }

    i = 19999;
    while(!arc_slist_empty(list))
    {
        if (*((int *)arc_slist_front(list)) != i--)
        {
            printf("Error on list element comparison \n");
        }
        arc_slist_pop_front(list);
    }

    arc_slist_destroy(list);

    list = arc_slist_create(sizeof(double));

    for (i = 0; i < 20000; i++)
    {
        double whatever = i + 1e6;
        arc_slist_push_front(list, (void *)&whatever);
    }

    arc_slist_destroy(list);

    return 0;
}