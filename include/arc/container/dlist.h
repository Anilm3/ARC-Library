/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#ifndef ARC_DLIST_H_
#define ARC_DLIST_H_

#include <stdlib.h> 

typedef struct arc_dlist * arc_dlist_t;
typedef struct arc_dlist_iterator * arc_dlist_iterator_t;

/**
 *
 */
arc_dlist_t arc_dlist_create(size_t data_size);
/**
 *
 */
void arc_dlist_destroy(arc_dlist_t list);
/**
 *
 */
int arc_dlist_size(arc_dlist_t list);
/**
 *
 */
int arc_dlist_empty(arc_dlist_t list);
/**
 *
 */
void arc_dlist_clear(arc_dlist_t list);
/**
 *
 */
void * arc_dlist_front(arc_dlist_t list);
/**
 *
 */
void arc_dlist_pop_front(arc_dlist_t list);
/**
 *
 */
int arc_dlist_push_front(arc_dlist_t list, void * data);
/**
 *
 */
void * arc_dlist_back(arc_dlist_t list);
/**
 *
 */
void arc_dlist_pop_back(arc_dlist_t list);
/**
 *
 */
int arc_dlist_push_back(arc_dlist_t list, void * data);

/**
 *
 */
arc_dlist_iterator_t arc_dlist_begin(arc_dlist_t list);
/**
 *
 */
arc_dlist_iterator_t arc_dlist_end(arc_dlist_t list);
/**
 *
 */
int arc_dlist_insert_before(arc_dlist_iterator_t it, void * data);
/**
 *
 */
int arc_dlist_insert_after(arc_dlist_iterator_t it, void * data);
/**
 *
 */
int arc_dlist_erase(arc_dlist_iterator_t it);
/**
 *
 */
int arc_dlist_iterator_valid(arc_dlist_iterator_t it);
/**
 *
 */
void * arc_dlist_iterator_data(arc_dlist_iterator_t it);
/**
 *
 */
int arc_dlist_iterator_next(arc_dlist_iterator_t it);
/**
 *
 */
int arc_dlist_iterator_previous(arc_dlist_iterator_t it);
/**
 *
 */
void arc_dlist_iterator_destroy(arc_dlist_iterator_t it);

#endif