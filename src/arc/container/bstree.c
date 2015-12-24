/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <arc/container/bstree.h>
#include <arc/common/defines.h>

#include <arc/container/bstree_def.h>
#include <arc/container/iterator_def.h>

/******************************************************************************/

struct arc_bstree * arc_bstree_create(size_t data_size, arc_cmp_fn_t cmp_fn)
{
    size_t aligned_size;
    struct arc_bstree * bstree = malloc(sizeof(struct arc_bstree));

    if (bstree == NULL)
    {
        return NULL;
    }

    /* The aligned size is the current size of the data block including the
       space occupied by the alignment */
    aligned_size = sizeof(struct arc_bstree_node) -
                   ARC_OFFSETOF(struct arc_bstree_node, data);

    aligned_size = (aligned_size > data_size ? 0 : data_size - aligned_size);

    bstree->root = NULL;
    bstree->size = 0;
    bstree->data_size = data_size;
    bstree->node_size = aligned_size + sizeof(struct arc_bstree_node);
    bstree->cmp_fn = cmp_fn;

    bstree->front.parent = NULL;
    bstree->front.left = NULL;
    bstree->front.right = NULL;

    bstree->back.parent = NULL;
    bstree->back.left = NULL;
    bstree->back.right = NULL;

    return bstree;
}

/******************************************************************************/
/**
 * @brief Recursively frees a node of the bstree
 *
 * @param[in] data node node to be freed
 */
static void arc_bstree_free_node(struct arc_bstree_node *node)
{
    if (node->left != NULL)
    {
        arc_bstree_free_node(node->left);
    }

    if (node->right != NULL)
    {
        arc_bstree_free_node(node->right);
    }

    free(node);
}

/******************************************************************************/

void arc_bstree_destroy(struct arc_bstree *bstree)
{
    if (bstree->root != NULL)
    {
        arc_bstree_free_node(bstree->root);
    }

    free(bstree);
}

/******************************************************************************/
/**
 * @brief Finds the minimum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
static struct arc_bstree_node *arc_bstree_min(struct arc_bstree_node *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

/******************************************************************************/
/**
 * @brief Finds the maximum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
static struct arc_bstree_node *arc_bstree_max(struct arc_bstree_node *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }

    return node;
}

/******************************************************************************/

int arc_bstree_insert(struct arc_bstree *bstree, void * data)
{
    struct arc_bstree_node *parent = NULL;
    struct arc_bstree_node *node = bstree->root;
    struct arc_bstree_node **node_ref = &(bstree->root);

    while (node != NULL)
    {
        int cmp_result = (*bstree->cmp_fn)(node->data, data);

        if (cmp_result == -1)
        {
            parent = node;
            node_ref = &(node->right);
            node = node->right;
        }
        else if (cmp_result == 1)
        {
            parent = node;
            node_ref = &(node->left);
            node = node->left;
        }
        else
        {
            return ARC_DUPLICATE;
        }
    }

    node = malloc(bstree->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->parent = parent;
    node->left   = NULL;
    node->right  = NULL;
    bstree->size++;

    memcpy(node->data, data, bstree->data_size);

    *node_ref = node;

    return ARC_SUCCESS;
}

/******************************************************************************/
/**
 * @brief Finds and returns a node in the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @param[in] data Data element to be found
 * @return 0 If the element was not found
 * @retval 1 If the element was found
 */
static struct arc_bstree_node * arc_bstree_find_node(struct arc_bstree *bstree,
                                                     void * data)
{
    struct arc_bstree_node *node = bstree->root;

    while (node != NULL)
    {
        int cmp_result = (*bstree->cmp_fn)((void *)node->data, data);
        if (cmp_result == -1)
        {
            node = node->right;
        }
        else if (cmp_result == 1)
        {
            node = node->left;
        }
        else
        {
            return node;
        }
    }

    return NULL;
}

/******************************************************************************/

int arc_bstree_find(struct arc_bstree *bstree, void * data)
{
    return (arc_bstree_find_node(bstree, data) != NULL);
}

/******************************************************************************/
/**
 * @brief Removes a node from the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @param[in] data node node to be removed
 */
static void arc_bstree_remove_node(struct arc_bstree *bstree,
                                   struct arc_bstree_node *node)
{
    struct arc_bstree_node **node_ref;

    if (node->parent == NULL)
    {
        node_ref = &(bstree->root);
    }
    else
    {
        node_ref = (node == node->parent->left ? &(node->parent->left) :
                                                 &(node->parent->right));
    }

    if (node->left == NULL || node->right == NULL)
    {
        if (node->right != NULL)
        {
            *node_ref = node->right;
            node->right->parent = node->parent;
        }
        else if (node->left != NULL)
        {
            *node_ref = node->left;
            node->left->parent = node->parent;
        }
        else
        {
            *node_ref = NULL;
        }
    }
    else
    {
        struct arc_bstree_node * successor = arc_bstree_min(node->right);
        if (successor->parent == node)
        {
            successor->parent = node->parent;
            successor->left = node->left;

            if (successor->left != NULL)
            {
                successor->left->parent = successor;
            }
        }
        else
        {
            successor->parent->left = successor->right;

            if (successor->right != NULL)
            {
                successor->right->parent = successor->parent;
            }

            successor->parent = node->parent;
            successor->right = node->right;
            successor->left = node->left;

            if (successor->right != NULL)
            {
                successor->right->parent = successor;
            }

            if (successor->left != NULL)
            {
                successor->left->parent = successor;
            }
        }

        *node_ref = successor;
    }

    free(node);
    bstree->size--;
}

/******************************************************************************/
/**
 * @brief Transform the tree into a vine and return size
 *
 * @see https://en.wikipedia.org/wiki/Day%E2%80%93Stout%E2%80%93Warren_algorithm
 *
 * @param[in] node (subtree) to apply the operation on
 */
static void arc_bstree_tree_to_vine(struct arc_bstree_node *node)
{
    struct arc_bstree_node *tail = node;
    struct arc_bstree_node *rest = tail->right;

    while (rest != NULL)
    {
        if (rest->left == NULL)
        {
            tail = rest;
            rest = rest->right;
        }
        else
        {
            struct arc_bstree_node *temp = rest->left;
            rest->left = temp->right;
            temp->right = rest;
            rest = temp;
            tail->right = temp;
        }
    }
}

/******************************************************************************/
/**
 * @brief Compress "count" spine nodes in the tree
 *
 * @see https://en.wikipedia.org/wiki/Day%E2%80%93Stout%E2%80%93Warren_algorithm
 *
 * @param[in] node (subtree) to apply the operation on
 */
static void arc_bstree_compress(struct arc_bstree_node *node, size_t count)
{
    size_t i;
    struct arc_bstree_node *scanner = node;

    for (i = 0; i < count; i++)
    {
        struct arc_bstree_node *child = scanner->right;
        /* Child should never be NULL as we're creating a vine on the right
           side of the tree and always checking for a tree bigger than one */
        scanner->right = child->right;
        if (child->right != NULL)
        {
            child->right->parent = scanner;
        }

        scanner = scanner->right;
        child->right = scanner->left;
        if (scanner->left != NULL)
        {
            scanner->left->parent = child;
        }

        scanner->left = child;
        child->parent = scanner;
    }
}

/******************************************************************************/
/**
 * @brief Convert the vine into a balanced tree
 *
 * @see https://en.wikipedia.org/wiki/Day%E2%80%93Stout%E2%80%93Warren_algorithm
 *
 * @param[in] node (subtree) to apply the operation on
 */
static void arc_bstree_vine_to_tree(struct arc_bstree_node *node, size_t size)
{
    size_t leaves = size + 1 - ((size_t)pow(2, floor(log2((double)size + 1))));

    arc_bstree_compress(node, leaves);

    size = size - leaves;

    while (size > 1)
    {
        arc_bstree_compress(node, (size_t)floor((double)size / 2.0));
        size = (size_t)floor((double)size / 2.0);
    }
}

/******************************************************************************/

void arc_bstree_rebalance(arc_bstree_t bstree)
{
    struct arc_bstree_node pseudo_root = {NULL, NULL, NULL, {0}};

    pseudo_root.right = bstree->root;

    arc_bstree_tree_to_vine(&pseudo_root);

    arc_bstree_vine_to_tree(&pseudo_root, bstree->size);

    bstree->root = pseudo_root.right;
    bstree->root->parent = NULL;
}

/******************************************************************************/

void arc_bstree_remove(struct arc_bstree *bstree, void * data)
{
    struct arc_bstree_node *node;

    node = arc_bstree_find_node(bstree, data);

    if (node == NULL)
    {
        return;
    }

    arc_bstree_remove_node(bstree, node);
}

/******************************************************************************/

int arc_bstree_empty(struct arc_bstree * bstree)
{
    return bstree->size == 0;
}

/******************************************************************************/

size_t arc_bstree_size(struct arc_bstree * bstree)
{
    return bstree->size;
}

/******************************************************************************/

void arc_bstree_clear(struct arc_bstree *bstree)
{
    arc_bstree_free_node(bstree->root);

    bstree->root = NULL;
    bstree->size = 0;
}

/******************************************************************************/

void arc_bstree_before_begin(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;

    bstree->front.parent = (bstree->root != NULL ?
                            arc_bstree_min(bstree->root) : NULL);

    it->node_ptr = &(bstree->front);
}

/******************************************************************************/

void arc_bstree_begin(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;

    bstree->front.parent = (bstree->root != NULL ?
                            arc_bstree_min(bstree->root) : NULL);

    it->node_ptr = bstree->front.parent;
}

/******************************************************************************/

void arc_bstree_end(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;

    bstree->back.parent = (bstree->root != NULL ?
                            arc_bstree_max(bstree->root) : NULL);

    it->node_ptr = bstree->back.parent;
}

/******************************************************************************/

void arc_bstree_after_end(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;

    bstree->back.parent = (bstree->root != NULL ?
                            arc_bstree_max(bstree->root) : NULL);

    it->node_ptr = &(bstree->back);
}

/******************************************************************************/

int arc_bstree_previous(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    struct arc_bstree_node * node = it->node_ptr;

    if (node == NULL)
    {
        return 0;
    }

    if (node->parent == NULL)
    {
        if (node->left == NULL)
        {
            it->node_ptr = &(bstree->front);
            return 0;
        }

        it->node_ptr = arc_bstree_max(node->left);
    }
    else
    {
        if (node->left != NULL)
        {
            it->node_ptr = arc_bstree_max(node->left);
        }
        else if (node == node->parent->left)
        {
            while (node->parent->parent != NULL)
            {
                if (node->parent == node->parent->parent->right)
                {
                    it->node_ptr = node->parent->parent;
                    return 1;
                }
                node = node->parent;
            }

            it->node_ptr = &(bstree->front);
            return 0;
        }
        else /*if (node == node->parent->right)*/
        {
            it->node_ptr = node->parent;
        }
    }

    return 1;
}

/******************************************************************************/

int arc_bstree_next(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    struct arc_bstree_node * node = it->node_ptr;

    if (node == NULL)
    {
        return 0;
    }

    if (node->parent == NULL)
    {
        if (node->right == NULL)
        {
            it->node_ptr = &(bstree->back);
            return 0;
        }

        it->node_ptr = arc_bstree_min(node->right);
    }
    else
    {
        if (node->right != NULL)
        {
            it->node_ptr = arc_bstree_min(node->right);
        }
        else if (node == node->parent->right)
        {
            while (node->parent->parent != NULL)
            {
                if (node->parent == node->parent->parent->left)
                {
                    it->node_ptr = node->parent->parent;
                    return 1;
                }
                node = node->parent;
            }

            it->node_ptr = &(bstree->back);
            return 0;
        }
        else /*if (node == node->parent->left)*/
        {
            it->node_ptr = node->parent;
        }
    }

    return 1;
}

/******************************************************************************/

void * arc_bstree_data(struct arc_iterator * it)
{
    struct arc_bstree_node * current = it->node_ptr;

    return &(current->data);
}

/******************************************************************************/

int arc_bstree_position(struct arc_iterator * it, void * data)
{
    struct arc_bstree * bstree = it->container;
    struct arc_bstree_node * node = arc_bstree_find_node(bstree, data);

    it->node_ptr = node;

    return (node != NULL);
}

/******************************************************************************/
void arc_bstree_erase(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    struct arc_bstree_node * current = it->node_ptr;

    if (it->node_ptr != (struct arc_bstree_node *)&(bstree->front) &&
        it->node_ptr != (struct arc_bstree_node *)&(bstree->back))
    {
        arc_bstree_remove_node(bstree, current);
    }
}

/******************************************************************************/
