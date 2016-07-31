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

/******************************************************************************/

static void arc_avltree_remove_internal(struct arc_tree *tree,
                                       struct arc_tree_snode *snode);

/******************************************************************************/

static int arc_avltree_insert_internal(struct arc_tree *tree, const void * data);

/******************************************************************************/

int arc_avltree_initialize(struct arc_tree *tree, 
                           size_t data_size,
                           arc_cmp_fn_t cmp_fn)
{
    size_t data_offset = ARC_OFFSETOF(struct arc_avltree_node, data);
    size_t node_size = sizeof(struct arc_avltree_node) - data_offset;
    node_size = (node_size > data_size ? 0 : data_size - node_size) +
                sizeof(struct arc_avltree_node);

    return arc_tree_initialize(tree,
                               data_size,
                               data_offset,
                               node_size, 
                               &arc_avltree_insert_internal,
                               &arc_avltree_remove_internal,
                               cmp_fn);
}

/******************************************************************************/

void arc_avltree_finalize(struct arc_tree *tree)
{
    arc_tree_finalize(tree);
}

/******************************************************************************/

struct arc_tree * arc_avltree_create(size_t data_size, arc_cmp_fn_t cmp_fn)
{
    size_t data_offset = ARC_OFFSETOF(struct arc_avltree_node, data);
    size_t node_size = sizeof(struct arc_avltree_node) - data_offset;
    node_size = (node_size > data_size ? 0 : data_size - node_size) +
                sizeof(struct arc_avltree_node);

    return (struct arc_tree *)arc_tree_create(data_size,
                                                 data_offset,
                                                 node_size, 
                                                 &arc_avltree_insert_internal,
                                                 &arc_avltree_remove_internal,
                                                 cmp_fn);
}

/******************************************************************************/

void arc_avltree_destroy(struct arc_tree *avltree)
{
    arc_tree_destroy((struct arc_tree *)avltree);
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

static int arc_avltree_insert_internal(struct arc_tree *tree, const void * data)
{
    struct arc_tree *avltree = (struct arc_tree *)tree;
    struct arc_avltree_node *parent = NULL;
    struct arc_avltree_node *node = (struct arc_avltree_node *)avltree->root;
    struct arc_avltree_node **node_ref = (struct arc_avltree_node **)&(avltree->root);

    while (node != NULL)
    {
        int cmp_result;
       
        if (avltree->cmp_fn == NULL) {
            cmp_result = memcmp(node->data, data, avltree->data_size);
        } else {
            cmp_result = (*avltree->cmp_fn)(node->data, data);
        }

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
            node_ref = (struct arc_avltree_node **)
                        arc_tree_node_ref(avltree,
                                          (struct arc_tree_snode *)parent);
            arc_avltree_rotate(parent, node_ref);
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

int arc_avltree_insert(struct arc_tree *avltree, const void * data)
{
    return arc_tree_insert((struct arc_tree *)avltree, data);
}

/******************************************************************************/

void *arc_avltree_retrieve(struct arc_tree *avltree, const void * data)
{
    return arc_tree_retrieve((struct arc_tree *)avltree, data);
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
    struct arc_tree *avltree = (struct arc_tree *)tree;
    struct arc_avltree_node *node = (struct arc_avltree_node *)snode;
    struct arc_avltree_node *parent, *child, *successor, **node_ref;

    node_ref = (struct arc_avltree_node **)arc_tree_node_ref(avltree, snode);

    successor = (struct arc_avltree_node *)
                arc_tree_successor((struct arc_tree_snode *)node);

    if (successor == NULL)
    {
        parent = node->parent;
        if (parent != NULL)
        {
            factor = (parent->left == node ? 1 : -1);
        }
    }
    else
    {
        parent = successor->parent;

        successor->parent = node->parent;

        if (parent == node)
        {
            factor = (parent->left == successor ? 1 : -1);
            successor->balance_factor = parent->balance_factor;
            parent = successor;

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

            factor = 1;
            successor->balance_factor = node->balance_factor;
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

    *node_ref = successor;

    while (parent != NULL)
    {
        if (abs(parent->balance_factor + factor) == 2)
        {
            node_ref = (struct arc_avltree_node **)
                       arc_tree_node_ref(avltree,
                                         (struct arc_tree_snode *)parent);
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

void arc_avltree_remove(struct arc_tree *avltree, const void * data)
{
    arc_tree_remove((struct arc_tree *)avltree, data);
}

/******************************************************************************/

int arc_avltree_empty(struct arc_tree * avltree)
{
    return arc_tree_empty((struct arc_tree *)avltree);
}

/******************************************************************************/

size_t arc_avltree_size(struct arc_tree * avltree)
{
    return arc_tree_size((struct arc_tree *)avltree);
}

/******************************************************************************/

void arc_avltree_clear(struct arc_tree *avltree)
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

int arc_avltree_position(struct arc_iterator * it, const void * data)
{
    return arc_tree_position(it, data);
}

/******************************************************************************/
void arc_avltree_erase(struct arc_iterator * it)
{
    arc_tree_erase(it);
}

/******************************************************************************/

