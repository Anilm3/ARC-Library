/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#include <string.h>
#include <arc/container/stack.h>
#include <arc/common/defines.h>

struct arc_stack_node
{
    struct arc_stack_node * next;
    void *data;
};

struct arc_stack
{
    struct arc_stack_node * top;
    int size;
    size_t data_size;
    size_t node_size;
};

/******************************************************************************/

struct arc_stack * arc_stack_create(size_t data_size)
{
    struct arc_stack * stack = malloc(sizeof(struct arc_stack));

    if (stack == NULL)
    {
        return NULL;
    }

    // Initialise the list
    stack->size = 0;
    stack->top = NULL;
    stack->data_size = data_size;
    stack->node_size = data_size + sizeof(struct arc_stack_node);

    return stack;
}

/******************************************************************************/

void arc_stack_destroy(struct arc_stack * stack)
{
    arc_stack_clear(stack);
    
    free(stack);
}

/******************************************************************************/

int arc_stack_push(struct arc_stack * stack, void * data)
{
    struct arc_stack_node * node = malloc(stack->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->data = (void *)(((char *)&node->data) + sizeof(void*));
    memcpy(node->data, data, stack->data_size);

    node->next = stack->top;
    stack->top = node;

    stack->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_stack_pop(struct arc_stack * stack)
{
    if (stack->top != NULL)
    {
        struct arc_stack_node * node = stack->top;
        
        stack->top = node->next;

        stack->size--;

        free(node);
    }
}

/******************************************************************************/

void * arc_stack_top(struct arc_stack * stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }

    return stack->top->data;
}

/******************************************************************************/

int arc_stack_empty(struct arc_stack * stack)
{
    return (stack->size == 0);
}

/******************************************************************************/

int arc_stack_size(struct arc_stack * stack)
{
    return stack->size;
}

/******************************************************************************/

void arc_stack_clear(struct arc_stack * stack)
{
    while (stack->top != NULL)
    {
        arc_stack_pop(stack);
    }
}

/******************************************************************************/
