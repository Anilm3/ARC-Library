/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
#ifndef ARC_QUEUE_DEF_H_
#define ARC_QUEUE_DEF_H_

#include <string.h>
#include <stdlib.h>

/* Queue node definition, the data array is a placerholder for the first byte of
   the user memory, which will be allocated as extra space for the node */
struct arc_queue_node
{
    struct arc_queue_node * next;
    char data[1];
};

/* The queue structure contains a pointer to the front and the back of the 
   stack, the current number of elements (size), the size of the user data and 
   finally the size of the stack node to avoid recomputations */
struct arc_queue
{
    struct arc_queue_node * front;
    struct arc_queue_node * back;
    int size;
    size_t data_size;
    size_t node_size;
};

#endif
