/*******************************************************************************
* Copyright (C) 2015 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
#ifndef ARC_avltree_DEF_H_
#define ARC_avltree_DEF_H_

#include <stdlib.h>

/* Sentinel node definition */
struct arc_avltree_snode
{
    struct arc_avltree_node * parent;
    struct arc_avltree_node * left;
    struct arc_avltree_node * right;
};

/* Standard node definition */
struct arc_avltree_node
{
    struct arc_avltree_node * parent;
    struct arc_avltree_node * left;
    struct arc_avltree_node * right;
    int balance_factor;
    char data[1];
};

/* Container definition */
struct arc_avltree
{
    struct arc_avltree_node *root;
    struct arc_avltree_snode front;
    struct arc_avltree_snode back;
    size_t size;
    size_t data_size;
    size_t node_size;
    arc_cmp_fn_t cmp_fn;
};
static void arc_avltree_rotate(struct arc_avltree *avltree,
                               struct arc_avltree_node *node);

/**
 * @brief Finds and returns a node in the avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 * @param[in] data Data element to be found
 * @return 0 If the element was not found
 * @retval 1 If the element was found
 */
static struct arc_avltree_node * arc_avltree_find_node(struct arc_avltree *avltree,
                                                     void * data);
/**
 * @brief Removes a node from the avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 * @param[in] data node node to be removed
 */
static void arc_avltree_remove_node(struct arc_avltree *avltree,
                                   struct arc_avltree_node *node);
/**
 * @brief Recursively frees a node of the avltree
 *
 * @param[in] data node node to be freed
 */
static void arc_avltree_free_node(struct arc_avltree_node *node);
/**
 * @brief Finds the minimum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
static struct arc_avltree_node *arc_avltree_min(struct arc_avltree_node *node);
/**
 * @brief Finds the maximum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
static struct arc_avltree_node *arc_avltree_max(struct arc_avltree_node *node);

#endif
