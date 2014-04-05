/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/


#include "stack_lf.h"
#include "stdlib.h"
#include "stdio.h"

struct stack_lf_node
{
    void *data;
    struct stack_lf_node *next;
};// __attribute__((packed)); ;


struct stack_lf
{
    int size;
    struct stack_lf_node *head;
};// __attribute__((packed)); ;

struct stack_lf * stack_lf_create()
{
    struct stack_lf * stack_p = malloc(sizeof(struct stack_lf));

    if (stack_p != NULL)
    {
        stack_p->size = 0;
        stack_p->head = NULL;
    }
    // printf("SIZE : %lu %lu %lu\n", sizeof(struct stack_lf), sizeof(int), sizeof(struct stack_lf_node *));
    return stack_p;
}

void stack_lf_destroy(struct stack_lf *stack_p)
{
    stack_lf_clear(stack_p);

    free(stack_p);
}
/*
void stack_lf_push(struct stack_lf *stack_p, void *data_p)
{
    struct stack_lf_node *node_p = malloc(sizeof(struct stack_lf_node));
    
    node_p->next = stack_p->head;
    node_p->data = data_p;

    stack_p->head = node_p;
    stack_p->size++;
}

void * stack_lf_pop(struct stack_lf *stack_p)
{
    void * data_p = NULL;
    struct stack_lf_node *node_p = stack_p->head;

    if (node_p != NULL)
    {
        data_p = node_p->data;

        stack_p->head = node_p->next;
        stack_p->size--;

        free(node_p);
    }

    return data_p;
}

int stack_lf_empty(struct stack_lf *stack_p)
{
    return (stack_p->size == 0);
}
*/

int stack_lf_size(struct stack_lf *stack_p)
{
    return stack_p->size;
}

void stack_lf_clear(struct stack_lf *stack_p)
{
    struct stack_lf_node *aux_p, *node_p = stack_p->head;

    while (node_p != NULL)
    {
        aux_p = node_p;
        
        node_p = node_p->next;

        free(aux_p);
    }

    stack_p->head = NULL;
}

void stack_lf_clear_data(struct stack_lf *stack_p)
{
    struct stack_lf_node *aux_p, *node_p = stack_p->head;

    while (node_p != NULL)
    {
        aux_p = node_p;
        
        node_p = node_p->next;

        free(aux_p->data);
        free(aux_p);
    }

    stack_p->head = NULL;
}

int stack_lf_empty(struct stack_lf *stack_p)
{
    return __sync_bool_compare_and_swap(&(stack_p->size), 0, 0);
}

void stack_lf_push(struct stack_lf *stack_p, void *data_p)
{
    int stack_size;
    struct stack_lf_node *old_head;
    struct stack_lf_node *node_p = malloc(sizeof(struct stack_lf_node));
    
    node_p->data = data_p;
    node_p->next = stack_p->head;

    do
    {
        old_head = stack_p->head;
    }
    while(!__sync_bool_compare_and_swap(&(stack_p->head), old_head, node_p));


    do
    {
        stack_size = stack_p->size;
    }
    while(!__sync_bool_compare_and_swap(&(stack_p->size), stack_size, stack_size + 1));
}


void * stack_lf_pop(struct stack_lf *stack_p)
{
    int stack_size;
    struct stack_lf_node *old_head;
    void * data_p = NULL;

    do
    {
        stack_size = stack_p->size;

        if (stack_size == 0) 
        {
            return NULL;
        }
    }
    while(!__sync_bool_compare_and_swap(&(stack_p->size), stack_size, stack_size - 1));

    do
    {
        old_head = stack_p->head;
    }
    while(!__sync_bool_compare_and_swap(&(stack_p->head), old_head, old_head->next));

    data_p = old_head->data;

    free(old_head);

    return data_p;
}
