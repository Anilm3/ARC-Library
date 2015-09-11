/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
#ifndef ARC_STACK_DEF_H_
#define ARC_STACK_DEF_H_

#include <string.h>
#include <stdlib.h>

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
    size_t size;
    size_t data_size;
    size_t node_size;
};

#endif
