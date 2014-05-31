#include <stdio.h>
#include <arc/container/list/sl_list.h>

int main()
{
    int i;
    sl_list_t list = sl_list_create(sizeof(int));

    for (i = 0; i < 20; i++)
    {
        sl_list_push_front(list, (void *)&i);
    }

    i = 19;
    while(!sl_list_empty(list))
    {
        if (*((int *)sl_list_front(list)) != i--)
        {
            printf("Error on list element comparison \n");
        }
        sl_list_pop_front(list);
    }

    sl_list_destroy(list);

    list = sl_list_create(sizeof(double));

    for (i = 0; i < 20000; i++)
    {
        double whatever = i + 1e6;
        sl_list_push_front(list, (void *)&whatever);
    }

    sl_list_destroy(list);

    return 0;
}