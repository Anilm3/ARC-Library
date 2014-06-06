/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#ifndef ARC_STACK_H_
#define ARC_STACK_H_

#include <stdlib.h>

typedef struct arc_stack * arc_stack_t;

/**
 * Allocates the required memory for a new stack
 */
arc_stack_t arc_stack_create(size_t data_size);
/**
 * Deallocates the memory associated to the new stack
 */
void arc_stack_destroy(arc_stack_t stack);
/**
 *
 * 
 */
int arc_stack_push(arc_stack_t stack, void * data);
/**
 *
 * 
 */
void arc_stack_pop(arc_stack_t stack);
/**
 *
 * 
 */
void * arc_stack_top(arc_stack_t stack);
/**
 *
 * 
 */
int arc_stack_empty(arc_stack_t stack);
/**
 *
 * 
 */
int arc_stack_size(arc_stack_t stack);
/**
 *
 * 
 */
void arc_stack_clear(arc_stack_t stack);

#endif