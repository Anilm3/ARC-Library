/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#ifndef ARC_DL_LIST_H_
#define ARC_DL_LIST_H_

#include <stdlib.h> 

typedef struct dl_list * dl_list_t;
typedef struct dl_list_node * dl_list_iterator_t;

/**
 *
 */
dl_list_t dl_list_create(size_t data_size);
/**
 *
 */
void dl_list_destroy(dl_list_t list);
/**
 *
 */
int dl_list_size(dl_list_t list);
/**
 *
 */
int dl_list_empty(dl_list_t list);

#endif