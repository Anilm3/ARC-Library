#include <stdio.h>
#include <arc/container/list/slist_ts.h>

int main()
{
    int i;
    arc_slist_ts_t list = arc_slist_ts_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        arc_slist_ts_push_front(list, (void *)&i);
    }

    i = 19999;
    while(!arc_slist_ts_empty(list))
    {
        if (*((int *)arc_slist_ts_front(list)) != i--)
        {
            printf("Error on list element comparison \n");
        }
        arc_slist_ts_pop_front(list);
    }

    arc_slist_ts_destroy(list);

    list = arc_slist_ts_create(sizeof(double));

    for (i = 0; i < 20000; i++)
    {
        double whatever = i + 1e6;
        arc_slist_ts_push_front(list, (void *)&whatever);
    }

    arc_slist_ts_destroy(list);

    return 0;
}