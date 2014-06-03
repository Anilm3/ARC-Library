/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#ifndef ARC_STACK_TS_H_
#define ARC_STACK_TS_H_

/**
 * \struct stack_ts_node
 * \description Forward declaration of a stack node
 */
struct stack_ts_node;
/**
 * \struct stack_ts
 * \description Forward declaration of a stack
 */
struct stack_ts;

/**
 *
 * Allocates the required memory for a new stack
 */
struct stack_ts * stack_ts_create();
/**
 *
 * Deallocates the memory associated to the new stack
 */
void stack_ts_destroy(struct stack_ts *);
/**
 *
 * 
 */
void stack_ts_push(struct stack_ts *, void *);
/**
 *
 * 
 */
void * stack_ts_pop(struct stack_ts *);
/**
 *
 * 
 */
int stack_ts_empty(struct stack_ts *);
/**
 *
 * 
 */
int stack_ts_size(struct stack_ts *);
/**
 *
 * 
 */
void stack_ts_clear(struct stack_ts *);

#endif // ARC_STACK_TS_H_