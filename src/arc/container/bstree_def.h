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
 * @brief Finds and returns a node in the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @param[in] data Data element to be found
 * @return 0 If the element was not found
 * @retval 1 If the element was found
 */
static struct arc_bstree_node * arc_bstree_find_node(struct arc_bstree *bstree,
                                                     void * data);
/**
 * @brief Removes a node from the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @param[in] data node node to be removed
 */
static void arc_bstree_remove_node(struct arc_bstree *bstree,
                                   struct arc_bstree_node *node);
/**
 * @brief Recursively frees a node of the bstree
 *
 * @param[in] data node node to be freed
 */
static void arc_bstree_free_node(struct arc_bstree_node *node);
/**
 * @brief Finds the minimum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
static struct arc_bstree_node *arc_bstree_min(struct arc_bstree_node *node);
/**
 * @brief Finds the maximum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
static struct arc_bstree_node *arc_bstree_max(struct arc_bstree_node *node);