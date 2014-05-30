#include <stdio.h>
#include "sl_list.h"

int main()
{
    int i;
    sl_list_t list = sl_list_create(sizeof(int));

    // printf("List created\n");

    for (i = 0; i < 20000; i++)
    {
        // printf("Pushing %d\n", i);
        sl_list_push_front(list, (void *)&i);
    }

    while(!sl_list_empty(list))
    {
        // int * data = (int *)sl_list_front(list);

        // printf("%d\n", *data);

        sl_list_pop_front(list);
    }

    sl_list_destroy(list);

    return 0;
}