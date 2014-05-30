#include <iostream>
#include <forward_list>

int main ()
{
    int i;
    std::forward_list<int> list;

    for (i = 0; i < 20000; i++)
    {
        // printf("Pushing %d\n", i);
        list.push_front(i);
    }

    while(!list.empty())
    {
        // int * data = (int *)sl_list_front(list);

        // printf("%d\n", *data);

        list.pop_front();
    }

  return 0;
}