/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdlib.h>

/* Sentinel node definition */
struct arc_bstree_snode
{
    struct arc_bstree_node * parent;
    struct arc_bstree_node * left;
    struct arc_bstree_node * right;
};

/* Standard node definition */
struct arc_bstree_node
{
    struct arc_bstree_node * parent;
    struct arc_bstree_node * left;
    struct arc_bstree_node * right;
    char data[1];
};

/* Container definition */
struct arc_bstree
{
    struct arc_bstree_node *root;
    struct arc_bstree_snode front;
    struct arc_bstree_snode back;
    size_t size;
    size_t data_size;
    size_t node_size;
    arc_cmp_fn_t cmp_fn;
};
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
static struct arc_bstree_node * arc_bstree_find_node(struct arc_bstree *bstree,
                                                     void * data);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
static void arc_bstree_free_node(struct arc_bstree_node *node);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
static struct arc_bstree_node *arc_bstree_min(struct arc_bstree_node *node);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
static struct arc_bstree_node *arc_bstree_max(struct arc_bstree_node *node);