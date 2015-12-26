/*******************************************************************************
* Copyright (C) 2015 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
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
#include <arc/container/avltree.h>
#include <arc/common/defines.h>
#include <arc/container/tree_def.h>
#include <arc/container/avltree_def.h>
#include <arc/container/iterator_def.h>

static void arc_avltree_remove_internal(struct arc_tree *tree,
                                       struct arc_tree_snode *snode);

static int arc_avltree_insert_internal(struct arc_tree *tree, void * data);

static void * arc_avltree_node_data(struct arc_tree_snode *snode)
{
    return (void *)(((struct arc_avltree_node *)snode)->data);
}

/******************************************************************************/

struct arc_avltree * arc_avltree_create(size_t data_size, arc_cmp_fn_t cmp_fn)
{
    size_t node_size = sizeof(struct arc_avltree_node) -
                       ARC_OFFSETOF(struct arc_avltree_node, data);

    node_size = (node_size > data_size ? 0 : data_size - node_size) +
                sizeof(struct arc_avltree_node);

    return (struct arc_avltree *)arc_tree_create(data_size, node_size, 
                                                &arc_avltree_node_data,
                                                &arc_avltree_insert_internal,
                                                &arc_avltree_remove_internal,
                                                cmp_fn);
}

/******************************************************************************/

void arc_avltree_destroy(struct arc_avltree *avltree)
{
    arc_tree_destroy((struct arc_tree *)avltree);
}

/******************************************************************************/

static struct arc_avltree_node ** arc_avltree_node_ref(struct arc_avltree *avltree,
                                                       struct arc_avltree_node *node)
{
    if (node->parent == NULL)
    {
        return &(avltree->root);
    }
    else
    {
        return (node->parent->left == node ? &(node->parent->left) :
                                             &(node->parent->right));
    }
}

/******************************************************************************/
/**
 *
 */
static void arc_avltree_rotate_left(struct arc_avltree_node *node,
                                     struct arc_avltree_node **node_ref)
{
    struct arc_avltree_node * child = node->right;
    child->parent = node->parent;
    node->right = child->left;
    if (node->right)
    {
        node->right->parent = node;
    }

    child->left = node;
    node->parent = child;

    if (child->balance_factor == 1)
    {
        node->balance_factor = 0;
        child->balance_factor = 0;
    }
    else
    {
        node->balance_factor = 1;
        child->balance_factor = -1;
    }

    *node_ref = child;
}

/******************************************************************************/
/**
 *
 */
static void arc_avltree_rotate_right_left(struct arc_avltree_node *node,
                                          struct arc_avltree_node **node_ref)
{
    struct arc_avltree_node * child = node->right;
    struct arc_avltree_node * grandchild = child->left;

    grandchild->parent = node->parent;
    child->parent = grandchild;
    node->parent = grandchild;

    node->right = grandchild->left;
    if (node->right)
    {
        node->right->parent = node;
    }

    child->left = grandchild->right;
    if (child->left)
    {
        child->left->parent = child;
    }

    grandchild->left = node;
    grandchild->right = child;

    if (grandchild->balance_factor != 0)
    {
        node->balance_factor = (grandchild->balance_factor == 1 ? -1 : 0);
        child->balance_factor =  (grandchild->balance_factor == 1 ? 0 : 1);
    }
    else
    {
        node->balance_factor = 0;
        child->balance_factor = 0;
    }

    grandchild->balance_factor = 0;

    *node_ref = grandchild;
}

/******************************************************************************/
/**
 *
 */
static void arc_avltree_rotate_right(struct arc_avltree_node *node,
                                     struct arc_avltree_node **node_ref)
{
    struct arc_avltree_node * child = node->left;
    child->parent = node->parent;

    node->left = child->right;
    if (node->left)
    {
        node->left->parent = node;
    }

    child->right = node;
    node->parent = child;
    if (child->balance_factor == -1)
    {
        node->balance_factor = 0;
        child->balance_factor = 0;
    }
    else
    {
        node->balance_factor = -1;
        child->balance_factor = 1;
    }

    *node_ref = child;
}

/******************************************************************************/
/**
 *
 */
static void arc_avltree_rotate_left_right(struct arc_avltree_node *node,
                                         struct arc_avltree_node **node_ref)
{
    struct arc_avltree_node * child = node->left;
    struct arc_avltree_node * grandchild = child->right;

    grandchild->parent = node->parent;
    child->parent = grandchild;
    node->parent = grandchild;

    node->left = grandchild->right;

    if (node->left)
    {
        node->left->parent = node;
    }

    child->right = grandchild->left;

    if (child->right)
    {
        child->right->parent = child;
    }

    grandchild->left = child;
    grandchild->right = node;

    if (grandchild->balance_factor != 0)
    {
        node->balance_factor = (grandchild->balance_factor == 1 ? 0 : 1);
        child->balance_factor =  (grandchild->balance_factor == 1 ? -1 : 0);
    }
    else
    {
        node->balance_factor = 0;
        child->balance_factor = 0;
    }

    grandchild->balance_factor = 0;

    *node_ref = grandchild;
}

/******************************************************************************/
/**
 *
 */
static void arc_avltree_rotate(struct arc_avltree_node *node,
                               struct arc_avltree_node **node_ref)
{

    if (node->balance_factor == 1)
    {
        struct arc_avltree_node * child = node->right;

        if (child->balance_factor == -1)
        {
            arc_avltree_rotate_right_left(node, node_ref);
        }
        else
        {
            arc_avltree_rotate_left(node, node_ref);
        }
    }
    else
    {
        struct arc_avltree_node * child = node->left;
        
        if (child->balance_factor == 1)
        {
            arc_avltree_rotate_left_right(node, node_ref);
        }
        else
        {
            arc_avltree_rotate_right(node, node_ref);
        }
    }
}

/******************************************************************************/

static int arc_avltree_insert_internal(struct arc_tree *tree, void * data)
{
    struct arc_avltree *avltree = (struct arc_avltree *)tree;
    struct arc_avltree_node *parent = NULL;
    struct arc_avltree_node *node = avltree->root;
    struct arc_avltree_node **node_ref = &(avltree->root);

    while (node != NULL)
    {
        int cmp_result = (*avltree->cmp_fn)(node->data, data);
        
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

    node = malloc(avltree->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->parent = parent;
    node->left   = NULL;
    node->right  = NULL;
    node->balance_factor = 0;
    avltree->size++;

    memcpy(node->data, data, avltree->data_size);
    *node_ref = node;

    /* Backtrack and update balance factors */
    while (parent != NULL)
    {
        int factor = (parent->right == node ? 1 : -1);
        if (abs(parent->balance_factor + factor) == 2)
        {
            arc_avltree_rotate(parent, arc_avltree_node_ref(avltree, parent));
            break;
        }
        parent->balance_factor += factor;

        if (parent->balance_factor == 0)
        {
            break;
        }
        node = parent;
        parent = parent->parent;
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_avltree_insert(struct arc_avltree *avltree, void * data)
{
    return arc_tree_insert((struct arc_tree *)avltree, data);
}

/******************************************************************************/

int arc_avltree_find(struct arc_avltree *avltree, void * data)
{
    return arc_tree_find((struct arc_tree *)avltree, data);
}

/******************************************************************************/
/**
 * @brief Removes a node from the avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 * @param[in] data node node to be removed
 */
static void arc_avltree_remove_internal(struct arc_tree *tree,
                                        struct arc_tree_snode *snode)
{
    int factor;
    struct arc_avltree *avltree = (struct arc_avltree *)tree;
    struct arc_avltree_node *node = (struct arc_avltree_node *)snode;
    struct arc_avltree_node *parent, *child;
    struct arc_avltree_node **node_ref = arc_avltree_node_ref(avltree, node);

    if (node->left == NULL || node->right == NULL)
    {
        parent = node->parent;

        if (parent != NULL)
        {
            factor = (node == parent->left ? 1 : -1);
        }

        if (node->right != NULL)
        {
            *node_ref = node->right;
            node->right->parent = node->parent;
            child = node->right;
        }
        else if (node->left != NULL)
        {
            *node_ref = node->left;
            node->left->parent = node->parent;
            child = node->left;
        }
        else
        {
            *node_ref = NULL;
            child = NULL;
        }
    }
    else
    {
        struct arc_avltree_node * successor;
        successor = (struct arc_avltree_node * )
                    arc_tree_min((struct arc_tree_snode *)node->right);

        if (successor->parent == node)
        {
            parent = successor;
            child = NULL;
            factor = -1;

            successor->parent = node->parent;
            successor->left = node->left;
            successor->balance_factor = node->balance_factor;

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

            parent = successor->parent;
            child = successor->parent->left;
            factor = 1;

            successor->parent = node->parent;
            successor->right = node->right;
            successor->left = node->left;
            successor->balance_factor = node->balance_factor;

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

    while (parent != NULL)
    {
        if (abs(parent->balance_factor + factor) == 2)
        {
            node_ref = arc_avltree_node_ref(avltree, parent);
            arc_avltree_rotate(parent, node_ref);
            parent = *node_ref;
        }
        else
        {
            parent->balance_factor += factor;
        }

        if (abs(parent->balance_factor) == 1)
        {
            break;
        }

        child = parent;
        parent = parent->parent;

        if (parent == NULL) 
        {
            break;
        }

        factor = (parent->right == child ? -1 : 1);
    }


    free(node);
    avltree->size--;
}


/******************************************************************************/

void arc_avltree_remove(struct arc_avltree *avltree, void * data)
{
    arc_tree_remove((struct arc_tree *)avltree, data);
}

/******************************************************************************/

int arc_avltree_empty(struct arc_avltree * avltree)
{
    return arc_tree_empty((struct arc_tree *)avltree);
}

/******************************************************************************/

size_t arc_avltree_size(struct arc_avltree * avltree)
{
    return arc_tree_size((struct arc_tree *)avltree);
}

/******************************************************************************/

void arc_avltree_clear(struct arc_avltree *avltree)
{
    arc_tree_clear((struct arc_tree *)avltree);
}

/******************************************************************************/

void arc_avltree_before_begin(struct arc_iterator * it)
{
    arc_tree_before_begin(it);
}

/******************************************************************************/

void arc_avltree_begin(struct arc_iterator * it)
{
    arc_tree_begin(it);
}

/******************************************************************************/

void arc_avltree_end(struct arc_iterator * it)
{
    arc_tree_end(it);
}

/******************************************************************************/

void arc_avltree_after_end(struct arc_iterator * it)
{
    arc_tree_after_end(it);
}

/******************************************************************************/

int arc_avltree_previous(struct arc_iterator * it)
{
    return arc_tree_previous(it);
}

/******************************************************************************/

int arc_avltree_next(struct arc_iterator * it)
{
    return arc_tree_next(it);
}

/******************************************************************************/

void * arc_avltree_data(struct arc_iterator * it)
{
    return arc_tree_data(it);
}

/******************************************************************************/

int arc_avltree_position(struct arc_iterator * it, void * data)
{
    return arc_tree_position(it, data);
}

/******************************************************************************/
void arc_avltree_erase(struct arc_iterator * it)
{
    arc_tree_erase(it);
}

/******************************************************************************/

