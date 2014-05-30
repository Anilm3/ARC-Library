/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/
#ifndef ARC_SL_LIST
#define ARC_SL_LIST

#include <stdlib.h> 

typedef struct sl_list * sl_list_t;
typedef struct sl_list_node * sl_list_iterator_t;

/**
 *
 */
sl_list_t sl_list_create(size_t data_size);
/**
 *
 */
void sl_list_destroy(sl_list_t list);
/**
 *
 */
int sl_list_size(sl_list_t list);
/**
 *
 */
int sl_list_empty(sl_list_t list);
/**
 *
 */
void sl_list_clear(sl_list_t list);
/**
 *
 */
void *sl_list_front(sl_list_t list);
/**
 *
 */
void sl_list_pop_front(sl_list_t list);
/**
 *
 */
int sl_list_push_front(sl_list_t list, 
                       void * data);
/**
 *
 */
sl_list_iterator_t sl_list_begin(sl_list_t list);
/**
 *
 */
int sl_list_insert_after(sl_list_t list, 
                         sl_list_iterator_t it, 
                         void * data);
/**
 *
 */
int sl_list_erase_after(sl_list_t list, 
                        sl_list_iterator_t it);
/**
 *
 */
void * sl_list_iterator_data(sl_list_iterator_t it);
/**
 *
 */
sl_list_iterator_t sl_list_iterator_next(sl_list_iterator_t it);

#endif