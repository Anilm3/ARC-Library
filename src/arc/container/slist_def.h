/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#ifndef ARC_SLIST_DEF_H_
#define ARC_SLIST_DEF_H_

#include <stdlib.h>

/* Sentinel node definition */
struct arc_slist_snode
{
    struct arc_slist_node * next;
};
/* Standard node definition */
struct arc_slist_node
{
    struct arc_slist_node * next;
    char data[1];
};
/* Container definition */
struct arc_slist
{
    struct arc_slist_snode front;
    struct arc_slist_snode back;
    size_t size;
    size_t data_size;
    size_t node_size;
};
/**
 * @struct arc_slist_iterator
 * @brief Iterator definition
 */
struct arc_slist_iterator
{
    void * container;
    void * node_ptr;
};


int arc_slist_init(struct arc_slist *list, size_t data_size);
void arc_slist_fini(struct arc_slist *list);
int arc_slist_iterator_init(struct arc_slist_iterator *it,
                            struct arc_slist *list);
void arc_slist_iterator_fini(struct arc_slist_iterator *it);
#endif
