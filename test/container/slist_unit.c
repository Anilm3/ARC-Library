#include <stdio.h>
#include <arc/container/slist.h>

int main(void)
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

    list = arc_slist_create(sizeof(int));

    for (i = 0; i < 20000; i++)
    {
        arc_slist_push_front(list, (void *)&i);
    }

    i = 19999;
    arc_slist_node_t it;

    for (it = arc_slist_begin(list);
         it != arc_slist_after_end(list); 
         it = arc_slist_node_next(it))
    {
        if (*((int *)arc_slist_node_data(it)) != i--)
        {
            printf("Error on list element comparison \n");
        }
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