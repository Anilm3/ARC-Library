/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#ifndef ARC_DLIST_DEF_H_
#define ARC_DLIST_DEF_H_

#include <stdlib.h>

/* Sentinel node definition */
struct arc_dlist_snode
{
    struct arc_dlist_node * next;
    struct arc_dlist_node * prev;
};

/* Standard node definition */
struct arc_dlist_node
{
    struct arc_dlist_node * next;
    struct arc_dlist_node * prev;
    char data[1];
};

/* Container definition */
struct arc_dlist
{
    struct arc_dlist_snode front;
    struct arc_dlist_snode back;
    size_t size;
    size_t data_size;
    size_t node_size;
};

int arc_dlist_initialize(struct arc_dlist *list, size_t data_size);
void arc_dlist_finalize(struct arc_dlist *list);

#endif
