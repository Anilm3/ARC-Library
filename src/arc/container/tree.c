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
#include <arc/common/defines.h>

#include <arc/container/tree_def.h>

/******************************************************************************/
int arc_tree_init(struct arc_tree *tree,
                  size_t data_size,
                  size_t data_offset,
                  size_t node_size, 
                  arc_tree_insert_fn_t insert_fn,
                  arc_tree_remove_fn_t remove_fn,
                  arc_cmp_fn_t cmp_fn)
{
    /* The aligned size is the current size of the data block including the
       space occupied by the alignment */
    tree->root = NULL;
    tree->size = 0;
    tree->data_size = data_size;
    tree->data_offset = data_offset;
    tree->node_size = node_size;
    tree->cmp_fn = cmp_fn;
    tree->insert_fn = insert_fn;
    tree->remove_fn = remove_fn;

    tree->front.parent = NULL;
    tree->front.left = NULL;
    tree->front.right = NULL;

    tree->back.parent = NULL;
    tree->back.left = NULL;
    tree->back.right = NULL;

    return ARC_SUCCESS;
}

/******************************************************************************/

struct arc_tree_snode ** arc_tree_node_ref(struct arc_tree *tree,
                                           struct arc_tree_snode *node)
{
    if (node->parent == NULL)
    {
        return (struct arc_tree_snode **)&(tree->root);
    }
    else
    {
        return (node->parent->left == node ? &(node->parent->left) :
                                             &(node->parent->right));
    }
}


/******************************************************************************/

void arc_tree_fini(struct arc_tree *tree)
{
    arc_tree_clear(tree);
}

/******************************************************************************/

struct arc_tree * arc_tree_create(size_t data_size, 
                                  size_t data_offset,
                                  size_t node_size, 
                                  arc_tree_insert_fn_t insert_fn,
                                  arc_tree_remove_fn_t remove_fn,
                                  arc_cmp_fn_t cmp_fn)
{
    struct arc_tree * tree = malloc(sizeof(struct arc_tree));

    if (tree == NULL)
    {
        return NULL;
    }

    arc_tree_init(tree,
                  data_size, data_offset, node_size,
                  insert_fn, remove_fn, cmp_fn);

    return tree;
}

/******************************************************************************/

void arc_tree_destroy(struct arc_tree *tree)
{
    arc_tree_fini(tree);
    free(tree);
}

/******************************************************************************/
/**
 * @brief Finds the successor of a node in its subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
struct arc_tree_snode *arc_tree_successor(struct arc_tree_snode *node)
{
    if (node->left == NULL)
    {
        if (node->right == NULL)
        {
            return NULL;
        }

        return node->right;
    }
    else if (node->right == NULL)
    {
        return node->left;
    }

    node = node->right;

    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}


/******************************************************************************/
/**
 * @brief Finds the minimum element in the subtree
 *
 * @param[in] node Binary search tree to perform the operation on
 */
struct arc_tree_snode *arc_tree_min(struct arc_tree_snode *node)
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
struct arc_tree_snode *arc_tree_max(struct arc_tree_snode *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }

    return node;
}

/******************************************************************************/

int arc_tree_insert(struct arc_tree *tree, const void * data)
{
     return (*tree->insert_fn)(tree, data);
}

/******************************************************************************/
/**
 * @brief Finds and returns a node in the tree
 *
 * @param[in] tree Binary search tree to perform the operation on
 * @param[in] data Data element to be found
 * @return 0 If the element was not found
 * @retval 1 If the element was found
 */
static struct arc_tree_snode * arc_tree_find_node(struct arc_tree *tree,
                                                  const void * data)
{
    struct arc_tree_snode *node = tree->root;

    while (node != NULL)
    {
        void * node_data = (void *)((char *)node + tree->data_offset);
        int cmp_result;
       
        if (tree->cmp_fn == NULL) {
            cmp_result = memcmp(node_data, data, tree->data_size);
        } else {
            cmp_result = (*tree->cmp_fn)(node_data, data);
        }

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

void *arc_tree_retrieve(struct arc_tree *tree, const void * data)
{
    struct arc_tree_snode *node = arc_tree_find_node(tree, data);
    return (node == NULL ? NULL : (void *)((char *)node + tree->data_offset));
}

/******************************************************************************/

void arc_tree_remove(struct arc_tree *tree, const void * data)
{
    struct arc_tree_snode *node;

    node = arc_tree_find_node(tree, data);

    if (node == NULL)
    {
        return;
    }

    (*tree->remove_fn)(tree, node);
}

/******************************************************************************/

int arc_tree_empty(struct arc_tree * tree)
{
    return tree->size == 0;
}

/******************************************************************************/

size_t arc_tree_size(struct arc_tree * tree)
{
    return tree->size;
}

/******************************************************************************/

void arc_tree_clear(struct arc_tree *tree)
{
    while (tree->root != NULL)
    {
        (*tree->remove_fn)(tree, tree->root);
    }

    tree->root = NULL;
    tree->size = 0;
}

/******************************************************************************/

int arc_tree_iterator_init(struct arc_tree_iterator *it,
                           struct arc_tree *tree)
{
    it->container = tree;
    it->node_ptr = NULL;
    it->node_num = 0;
    it->node_idx = 0;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_tree_iterator_fini(struct arc_tree_iterator *it)
{
    it->container = NULL;
    it->node_ptr = NULL;
    it->node_num = 0;
    it->node_idx = 0;
}

/******************************************************************************/

struct arc_tree_iterator *arc_tree_iterator_create(struct arc_tree *tree)
{
    struct arc_tree_iterator *it = malloc(sizeof(struct arc_tree_iterator));

    if (it == NULL)
    {
        return NULL;
    }

    arc_tree_iterator_init(it, tree);

    return it;
}

/******************************************************************************/

void arc_tree_iterator_destroy(struct arc_tree_iterator *it)
{
    arc_tree_iterator_fini(it);
    free(it);
}


/******************************************************************************/

void arc_tree_before_begin(struct arc_tree_iterator * it)
{
    struct arc_tree * tree = it->container;

    tree->front.parent = (tree->root != NULL ?
                            arc_tree_min(tree->root) : NULL);

    it->node_ptr = &(tree->front);
}

/******************************************************************************/

void arc_tree_begin(struct arc_tree_iterator * it)
{
    struct arc_tree * tree = it->container;

    tree->front.parent = (tree->root != NULL ?
                            arc_tree_min(tree->root) : NULL);

    it->node_ptr = tree->front.parent;
}

/******************************************************************************/

void arc_tree_end(struct arc_tree_iterator * it)
{
    struct arc_tree * tree = it->container;

    tree->back.parent = (tree->root != NULL ?
                            arc_tree_max(tree->root) : NULL);

    it->node_ptr = tree->back.parent;
}

/******************************************************************************/

void arc_tree_after_end(struct arc_tree_iterator * it)
{
    struct arc_tree * tree = it->container;

    tree->back.parent = (tree->root != NULL ?
                            arc_tree_max(tree->root) : NULL);

    it->node_ptr = &(tree->back);
}

/******************************************************************************/

int arc_tree_previous(struct arc_tree_iterator * it)
{
    struct arc_tree * tree = it->container;
    struct arc_tree_snode * node = it->node_ptr;

    if (node == NULL)
    {
        return 0;
    }

    if (node->parent == NULL)
    {
        if (node->left == NULL)
        {
            it->node_ptr = &(tree->front);
            return 0;
        }

        it->node_ptr = arc_tree_max(node->left);
    }
    else
    {
        if (node->left != NULL)
        {
            it->node_ptr = arc_tree_max(node->left);
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

            it->node_ptr = &(tree->front);
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

int arc_tree_next(struct arc_tree_iterator * it)
{
    struct arc_tree * tree = it->container;
    struct arc_tree_snode * node = it->node_ptr;

    if (node == NULL)
    {
        return 0;
    }

    if (node->parent == NULL)
    {
        if (node->right == NULL)
        {
            it->node_ptr = &(tree->back);
            return 0;
        }

        it->node_ptr = arc_tree_min(node->right);
    }
    else
    {
        if (node->right != NULL)
        {
            it->node_ptr = arc_tree_min(node->right);
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

            it->node_ptr = &(tree->back);
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

void * arc_tree_data(struct arc_tree_iterator * it)
{
    struct arc_tree * tree = it->container;
    struct arc_tree_snode * current = it->node_ptr;

    return (void *)((char *)current + tree->data_offset);
/*(*tree->node_data_fn)(current);*/
}

/******************************************************************************/

int arc_tree_position(struct arc_tree_iterator * it, const void * data)
{
    struct arc_tree * tree = it->container;
    struct arc_tree_snode * node = arc_tree_find_node(tree, data);

    it->node_ptr = node;

    return (node != NULL);
}

/******************************************************************************/
void arc_tree_erase(struct arc_tree_iterator * it)
{
    struct arc_tree * tree = it->container;
    struct arc_tree_snode * current = it->node_ptr;

    if (it->node_ptr != (struct arc_tree_snode *)&(tree->front) &&
        it->node_ptr != (struct arc_tree_snode *)&(tree->back))
    {
        (*tree->remove_fn)(tree, current);
    }
}

/******************************************************************************/
