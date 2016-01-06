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
#include <arc/container/tree_def.h>
#include <arc/container/bstree_def.h>
#include <arc/container/iterator_def.h>

/******************************************************************************/

static void arc_bstree_remove_internal(struct arc_tree *tree,
                                       struct arc_tree_snode *snode);

/******************************************************************************/

static int arc_bstree_insert_internal(struct arc_tree *tree, void * data);

/******************************************************************************/

int arc_bstree_initialize(arc_bstree *tree,
                          size_t data_size,
                          arc_cmp_fn_t cmp_fn)
{
    size_t data_offset = ARC_OFFSETOF(struct arc_bstree_node, data);
    size_t node_size = sizeof(struct arc_bstree_node) - data_offset;
    node_size = (node_size > data_size ? 0 : data_size - node_size) +
                sizeof(struct arc_bstree_node);

    return arc_tree_initialize(tree,
                               data_size,
                               data_offset,
                               node_size, 
                               &arc_bstree_insert_internal,
                               &arc_bstree_remove_internal,
                               cmp_fn);
}

/******************************************************************************/

void arc_bstree_finalize(arc_bstree *tree)
{
    arc_tree_finalize(tree);
}

/******************************************************************************/

arc_bstree * arc_bstree_create(size_t data_size, arc_cmp_fn_t cmp_fn)
{
    size_t data_offset = ARC_OFFSETOF(struct arc_bstree_node, data);
    size_t node_size = sizeof(struct arc_bstree_node) - data_offset;
    node_size = (node_size > data_size ? 0 : data_size - node_size) +
                sizeof(struct arc_bstree_node);

    return (arc_bstree *)arc_tree_create(data_size,
                                         data_offset,
                                         node_size, 
                                         &arc_bstree_insert_internal,
                                         &arc_bstree_remove_internal,
                                         cmp_fn);
}

/******************************************************************************/

void arc_bstree_destroy(arc_bstree *bstree)
{
    arc_tree_destroy((struct arc_tree *)bstree);
}

/******************************************************************************/

static int arc_bstree_insert_internal(struct arc_tree *tree, void * data)
{
    arc_bstree *bstree = (arc_bstree *)tree;
    struct arc_bstree_node *parent = NULL;
    struct arc_bstree_node *node = (struct arc_bstree_node *)bstree->root;
    struct arc_bstree_node **node_ref = (struct arc_bstree_node **)&(bstree->root);

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

int arc_bstree_insert(arc_bstree *bstree, void * data)
{
    return arc_tree_insert((struct arc_tree *)bstree, data);
}

/******************************************************************************/

int arc_bstree_find(arc_bstree *bstree, void * data)
{
    return arc_tree_find((struct arc_tree *)bstree, data);
}

/******************************************************************************/
/**
 * @brief Removes a node from the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @param[in] data node node to be removed
 */
static void arc_bstree_remove_internal(struct arc_tree *tree,
                                       struct arc_tree_snode *snode)
{
    arc_bstree *bstree = (arc_bstree *)tree;
    struct arc_bstree_node *node= (struct arc_bstree_node *)snode;
    struct arc_bstree_node *successor, *parent, **node_ref;

    /*arc_bstree_print(bstree);*/
    if (node->parent == NULL)
    {
        node_ref = (struct arc_bstree_node **)&(bstree->root);
    }
    else
    {
        node_ref = (node == node->parent->left ? &(node->parent->left) :
                                                 &(node->parent->right));
    }

    successor = (struct arc_bstree_node *)arc_tree_successor((struct arc_tree_snode *)node);
    *node_ref = successor;

    if (successor != NULL)
    {
        parent = successor->parent;

        successor->parent = node->parent;

        if (parent == node)
        {
            if(node->right == successor && node->left != NULL)
            {
                successor->left = node->left;
                successor->left->parent = successor;
            }
        }
        else
        {
            if (parent != NULL)
            {
                parent->left = successor->right;

                if (parent->left != NULL)
                {
                    parent->left->parent = parent;
                }
            }

            successor->left = node->left;
            
            if (successor->left != NULL)
            {
                successor->left->parent = successor;
            }

            /* We know for a fact that the right is not NULL */
            successor->right = node->right;
            successor->right->parent = successor;
        }
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
            if (rest->left != NULL)
            {
                rest->left->parent = rest;
            }

            temp->right = rest;
            temp->right->parent = temp;

            rest = temp;
            tail->right = temp;
            tail->right->parent = tail;
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

    pseudo_root.right = (struct arc_bstree_node *)bstree->root;

    arc_bstree_tree_to_vine(&pseudo_root);

    arc_bstree_vine_to_tree(&pseudo_root, bstree->size);

    bstree->root = (struct arc_tree_snode *)pseudo_root.right;
    bstree->root->parent = NULL;
}

/******************************************************************************/

void arc_bstree_remove(arc_bstree *bstree, void * data)
{
    arc_tree_remove((struct arc_tree *)bstree, data);
}

/******************************************************************************/

int arc_bstree_empty(arc_bstree * bstree)
{
    return arc_tree_empty((struct arc_tree *)bstree);
}

/******************************************************************************/

size_t arc_bstree_size(arc_bstree * bstree)
{
    return arc_tree_size((struct arc_tree *)bstree);
}

/******************************************************************************/

void arc_bstree_clear(arc_bstree *bstree)
{
    arc_tree_clear((struct arc_tree *)bstree);
}

/******************************************************************************/

void arc_bstree_before_begin(struct arc_iterator * it)
{
    arc_tree_before_begin(it);
}

/******************************************************************************/

void arc_bstree_begin(struct arc_iterator * it)
{
    arc_tree_begin(it);
}

/******************************************************************************/

void arc_bstree_end(struct arc_iterator * it)
{
    arc_tree_end(it);
}

/******************************************************************************/

void arc_bstree_after_end(struct arc_iterator * it)
{
    arc_tree_after_end(it);
}

/******************************************************************************/

int arc_bstree_previous(struct arc_iterator * it)
{
    return arc_tree_previous(it);
}

/******************************************************************************/

int arc_bstree_next(struct arc_iterator * it)
{
    return arc_tree_next(it);
}

/******************************************************************************/

void * arc_bstree_data(struct arc_iterator * it)
{
    return arc_tree_data(it);
}

/******************************************************************************/

int arc_bstree_position(struct arc_iterator * it, void * data)
{
    return arc_tree_position(it, data);
}

/******************************************************************************/
void arc_bstree_erase(struct arc_iterator * it)
{
    arc_tree_erase(it);
}

/******************************************************************************/
