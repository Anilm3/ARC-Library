/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#ifndef ARC_STACK_TR_H_
#define ARC_STACK_TR_H_

/**
 * \struct stack_tr_node
 * \description Forward declaration of a stack node
 */
struct stack_tr_node;
/**
 * \struct stack_tr
 * \description Forward declaration of a stack
 */
struct stack_tr;

/**
 *
 * Allocates the required memory for a new stack
 */
struct stack_tr * stack_tr_create();
/**
 *
 * Deallocates the memory associated to the new stack
 */
void stack_tr_destroy(struct stack_tr *);
/**
 *
 * 
 */
void stack_tr_push(struct stack_tr *, void *);
/**
 *
 * 
 */
void * stack_tr_pop(struct stack_tr *);
/**
 *
 * 
 */
int stack_tr_empty(struct stack_tr *);
/**
 *
 * 
 */
int stack_tr_size(struct stack_tr *);
/**
 *
 * 
 */
void stack_tr_clear(struct stack_tr *);

#endif // ARC_STACK_TR_H_