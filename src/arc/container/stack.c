/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/stack.h>
#include <arc/common/defines.h>

/* Stack node definition, the data array is a placerholder for the first byte of
   the user memory, which will be allocated as extra space for the node */
struct arc_stack_node
{
    struct arc_stack_node * next;
    char data[1];
};

/* The stack structure contains a pointer to the top of the stack, the current
   number of elements (size), the size of the user data and finally the size of
   the stack node to avoid recomputations */
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
    size_t aligned_size;

    struct arc_stack * stack = malloc(sizeof(struct arc_stack));

    if (stack == NULL)
    {
        return NULL;
    }

    /* The aligned size is the current size of the data block including the 
       space occupied by the alignment */
    aligned_size = sizeof(struct arc_stack_node) - 
                   ARC_OFFSETOF(struct arc_stack_node, data);

    /* The aligment is taken into account to optimize the memory usage */
    aligned_size = (aligned_size > data_size ? 0 : data_size - aligned_size);

    /* Initialise the stack */
    stack->size = 0;
    stack->top = NULL;
    stack->data_size = data_size;
    stack->node_size = aligned_size + sizeof(struct arc_stack_node);

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
    while (stack->size > 0)
    {
        arc_stack_pop(stack);
    }
}

/******************************************************************************/
