#ifndef ARC_STACK_LOCK_FREE
#define ARC_STACK_LOCK_FREE

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

#endif // ARC_STACK_LOCK_FREE