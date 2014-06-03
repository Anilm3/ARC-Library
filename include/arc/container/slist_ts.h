/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#ifndef ARC_SLIST_TS_H_
#define ARC_SLIST_TS_H_

#include <stdlib.h> 

typedef struct arc_slist_ts * arc_slist_ts_t;
typedef struct arc_slist_ts_node * arc_slist_ts_node_t;

/**
 *
 */
arc_slist_ts_t arc_slist_ts_create(size_t data_size);
/**
 *
 */
void arc_slist_ts_destroy(arc_slist_ts_t list);
/**
 *
 */
int arc_slist_ts_size(arc_slist_ts_t list);
/**
 *
 */
int arc_slist_ts_empty(arc_slist_ts_t list);
/**
 *
 */
void arc_slist_ts_clear(arc_slist_ts_t list);
/**
 *
 */
void * arc_slist_ts_front(arc_slist_ts_t list);
/**
 *
 */
void arc_slist_ts_pop_front(arc_slist_ts_t list);
/**
 *
 */
int arc_slist_ts_push_front(arc_slist_ts_t list, void * data);
/**
 *
 */
arc_slist_ts_node_t arc_slist_ts_begin(arc_slist_ts_t list);
/**
 *
 */
int arc_slist_ts_insert_after(arc_slist_ts_t list, 
                         arc_slist_ts_node_t it, 
                         void * data);
/**
 *
 */
int arc_slist_ts_erase_after(arc_slist_ts_t list, arc_slist_ts_node_t it);
/**
 *
 */
void * arc_slist_ts_node_data(arc_slist_ts_node_t it);
/**
 *
 */
arc_slist_ts_node_t arc_slist_ts_node_next(arc_slist_ts_node_t it);

#endif