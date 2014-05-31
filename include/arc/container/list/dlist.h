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
typedef struct arc_dlist_node * arc_dlist_iterator_t;

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

#endif