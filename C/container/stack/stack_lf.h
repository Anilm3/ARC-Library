/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#ifndef ARC_STACK_LF_H_
#define ARC_STACK_LF_H_

struct stack_lf_node;

struct stack_lf;

// creates a new stack
struct stack_lf * stack_lf_create();
// deletes nodes but not data
void stack_lf_destroy(struct stack_lf *);
// deletes nodes and data
void stack_lf_destroy_data(struct stack_lf *);

void stack_lf_push(struct stack_lf *, void *);
void * stack_lf_pop(struct stack_lf *);

int stack_lf_empty(struct stack_lf *);
int stack_lf_size(struct stack_lf *);

void stack_lf_clear(struct stack_lf *);
void stack_lf_clear_data(struct stack_lf *);

#endif // ARC_STACK_LF_H_