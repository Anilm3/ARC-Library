/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#ifndef ARC_STACK_MT_H_
#define ARC_STACK_MT_H_

/**
 * \struct stack_mt_node
 * \description Forward declaration of a stack node
 */
struct stack_mt_node;
/**
 * \struct stack_mt
 * \description Forward declaration of a stack
 */
struct stack_mt;

/**
 *
 * Allocates the required memory for a new stack
 */
struct stack_mt * stack_mt_create();
/**
 *
 * Deallocates the memory associated to the new stack
 */
void stack_mt_destroy(struct stack_mt *);
/**
 *
 * 
 */
void stack_mt_push(struct stack_mt *, void *);
/**
 *
 * 
 */
void * stack_mt_pop(struct stack_mt *);
/**
 *
 * 
 */
int stack_mt_empty(struct stack_mt *);
/**
 *
 * 
 */
int stack_mt_size(struct stack_mt *);
/**
 *
 * 
 */
void stack_mt_clear(struct stack_mt *);

#endif // ARC_STACK_MT_H_