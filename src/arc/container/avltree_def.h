/*******************************************************************************
* Copyright (C) 2015 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
#ifndef ARC_AVLTREE_DEF_H_
#define ARC_AVLTREE_DEF_H_

#include <stdlib.h>
#include <arc/container/tree_def.h>

/* Standard node definition */
struct arc_avltree_node
{
    struct arc_avltree_node * parent;
    struct arc_avltree_node * left;
    struct arc_avltree_node * right;
    int balance_factor;
    char data[1];
};

int arc_avltree_init(struct arc_tree *tree, 
                     size_t data_size,
                     arc_cmp_fn_t cmp_fn);

void arc_avltree_fini(struct arc_tree *tree);
int arc_avltree_iterator_init(struct arc_tree_iterator *it,
                              struct arc_tree *tree);
void arc_avltree_iterator_fini(struct arc_tree_iterator *it);

#endif
