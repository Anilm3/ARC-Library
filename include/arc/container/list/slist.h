/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#ifndef ARC_SLIST_H_
#define ARC_SLIST_H_

#include <stdlib.h> 

typedef struct arc_slist * arc_slist_t;
typedef struct arc_slist_node * arc_slist_iterator_t;

/**
 *
 */
arc_slist_t arc_slist_create(size_t data_size);
/**
 *
 */
void arc_slist_destroy(arc_slist_t list);
/**
 *
 */
int arc_slist_size(arc_slist_t list);
/**
 *
 */
int arc_slist_empty(arc_slist_t list);
/**
 *
 */
void arc_slist_clear(arc_slist_t list);
/**
 *
 */
void * arc_slist_front(arc_slist_t list);
/**
 *
 */
void arc_slist_pop_front(arc_slist_t list);
/**
 *
 */
int arc_slist_push_front(arc_slist_t list, void * data);
/**
 *
 */
arc_slist_iterator_t arc_slist_begin(arc_slist_t list);
/**
 *
 */
int arc_slist_insert_after(arc_slist_t list, 
                         arc_slist_iterator_t it, 
                         void * data);
/**
 *
 */
int arc_slist_erase_after(arc_slist_t list, arc_slist_iterator_t it);
/**
 *
 */
void * arc_slist_iterator_data(arc_slist_iterator_t it);
/**
 *
 */
arc_slist_iterator_t arc_slist_iterator_next(arc_slist_iterator_t it);

#endif