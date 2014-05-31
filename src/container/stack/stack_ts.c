/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <arc/container/stack/stack_ts.h>

struct stack_ts_node
{
    void *data;
    struct stack_ts_node *next;
};
// __attribute__((packed)); ;


struct stack_ts
{
    int size;
    struct stack_ts_node *head;
    pthread_mutex_t mutex;
};
// __attribute__((packed)); ;


struct stack_ts * stack_ts_create()
{
    struct stack_ts * stack_p = (struct stack_ts *)malloc(sizeof(struct stack_ts));

    if (stack_p != NULL)
    {
        stack_p->size = 0;
        stack_p->head = NULL;

        pthread_mutex_init(&stack_p->mutex, NULL);
    }

    return stack_p;
}

void stack_ts_destroy(struct stack_ts *stack_p)
{
    pthread_mutex_destroy(&stack_p->mutex);

    stack_ts_clear(stack_p);

    free(stack_p);
}


int stack_ts_size(struct stack_ts *stack_p)
{
    return stack_p->size;
}

void stack_ts_clear(struct stack_ts *stack_p)
{
    struct stack_ts_node *aux_p, *node_p = stack_p->head;

    while (node_p != NULL)
    {
        aux_p = node_p;
        
        node_p = node_p->next;

        free(aux_p);
    }

    stack_p->head = NULL;
}

int stack_ts_empty(struct stack_ts *stack_p)
{
    pthread_mutex_lock(&stack_p->mutex);
    
    int retval = (stack_p->size == 0);

    pthread_mutex_unlock(&stack_p->mutex);

    return retval;
}

void stack_ts_push(struct stack_ts *stack_p, void *data_p)
{
    struct stack_ts_node *node_p = (struct stack_ts_node *)malloc(sizeof(struct stack_ts_node));
    
    node_p->data = data_p;

    pthread_mutex_lock(&stack_p->mutex);

    node_p->next = stack_p->head;

    stack_p->size++;
    stack_p->head = node_p;

    pthread_mutex_unlock(&stack_p->mutex);
}


void * stack_ts_pop(struct stack_ts *stack_p)
{
    void * data_p = NULL;

    struct stack_ts_node *node_p ;

    pthread_mutex_lock(&stack_p->mutex);

    if (stack_p->size == 0)
    {
        pthread_mutex_unlock(&stack_p->mutex);
        return NULL;
    }

    stack_p->size--;
    node_p = stack_p->head;
    stack_p->head = node_p->next;

    pthread_mutex_unlock(&stack_p->mutex);

    data_p = node_p->data;

    free(node_p);

    return data_p;
}
