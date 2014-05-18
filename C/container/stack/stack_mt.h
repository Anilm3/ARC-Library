/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#ifndef ARC_STACK_LOCK_FREE
#define ARC_STACK_LOCK_FREE

struct stack_mt_node;

struct stack_mt;

// creates a new stack
struct stack_mt * stack_mt_create();
// deletes nodes but not data
void stack_mt_destroy(struct stack_mt *);

void stack_mt_push(struct stack_mt *, void *);
void * stack_mt_pop(struct stack_mt *);

int stack_mt_empty(struct stack_mt *);
int stack_mt_size(struct stack_mt *);

void stack_mt_clear(struct stack_mt *);

#endif // ARC_STACK_LOCK_FREE