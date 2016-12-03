/*******************************************************************************
* Copyright (C) 2015 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
#ifndef ARC_TREE_DEF_H_
#define ARC_TREE_DEF_H_

#include <stdlib.h>
#include <arc/type/function.h>
#include <arc/container/iterator_def.h>

/* Sentinel node definition */
struct arc_tree_snode
{
    struct arc_tree_snode * parent;
    struct arc_tree_snode * left;
    struct arc_tree_snode * right;
};

struct arc_tree;
/**
 * @typedef arc_tree_getval_fn
 * @brief Function to get a value from a tree specific node
 */
typedef void * (*arc_tree_node_data_fn_t)(struct arc_tree_snode *);
typedef int (*arc_tree_insert_fn_t)(struct arc_tree *, const void *);
typedef void (*arc_tree_remove_fn_t)(struct arc_tree *, struct arc_tree_snode *);

/* Container definition */
struct arc_tree
{
    struct arc_tree_snode *root;
    struct arc_tree_snode front;
    struct arc_tree_snode back;
    size_t size;
    size_t data_size;
    size_t data_offset;
    size_t node_size;
    arc_cmp_fn_t cmp_fn;
    arc_tree_insert_fn_t insert_fn;
    arc_tree_remove_fn_t remove_fn;
};
/**
 * @struct arc_tree_iterator
 * @brief Iterator definition
 */
struct arc_tree_iterator
{
    void * container;
    void * node_ptr;
    unsigned long node_num;
    unsigned long node_idx;
};

int arc_tree_init(struct arc_tree *tree,
                  size_t data_size,
                  size_t data_offset,
                  size_t node_size, 
                  arc_tree_insert_fn_t insert_fn,
                  arc_tree_remove_fn_t remove_fn,
                  arc_cmp_fn_t cmp_fn);


void arc_tree_fini(struct arc_tree *tree);

struct arc_tree * arc_tree_create(size_t data_size,
                                  size_t data_offset,
                                  size_t node_size, 
                                  arc_tree_insert_fn_t insert_fn,
                                  arc_tree_remove_fn_t remove_fn,
                                  arc_cmp_fn_t cmp_fn);


void arc_tree_destroy(struct arc_tree *tree);

struct arc_tree_snode ** arc_tree_node_ref(struct arc_tree *tree,
                                           struct arc_tree_snode *node);

struct arc_tree_snode *arc_tree_successor(struct arc_tree_snode *node);
/**
 * @brief Finds the minimum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
struct arc_tree_snode *arc_tree_min(struct arc_tree_snode *node);

/**
 * @brief Finds the maximum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
struct arc_tree_snode *arc_tree_max(struct arc_tree_snode *node);

int arc_tree_insert(struct arc_tree *tree, const void * data);

void *arc_tree_retrieve(struct arc_tree *tree, const void * data);

void arc_tree_remove(struct arc_tree *tree, const void * data);

int arc_tree_empty(struct arc_tree * tree);

size_t arc_tree_size(struct arc_tree * tree);

void arc_tree_clear(struct arc_tree *tree);

struct arc_tree_iterator * arc_tree_iterator_create(struct arc_tree * tree);

void arc_tree_iterator_destroy(struct arc_tree_iterator * it);

int arc_tree_iterator_init(struct arc_tree_iterator *it,
                            struct arc_tree *list);
void arc_tree_iterator_fini(struct arc_tree_iterator *it);


void arc_tree_before_begin(struct arc_tree_iterator * it);

void arc_tree_begin(struct arc_tree_iterator * it);

void arc_tree_end(struct arc_tree_iterator * it);

void arc_tree_after_end(struct arc_tree_iterator * it);

int arc_tree_previous(struct arc_tree_iterator * it);

int arc_tree_next(struct arc_tree_iterator * it);

void * arc_tree_data(struct arc_tree_iterator * it);

int arc_tree_position(struct arc_tree_iterator * it, const void * data);

void arc_tree_erase(struct arc_tree_iterator * it);

#endif
