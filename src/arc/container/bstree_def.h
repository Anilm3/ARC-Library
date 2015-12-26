/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
#ifndef ARC_BSTREE_DEF_H_
#define ARC_BSTREE_DEF_H_

#include <stdlib.h>
#include <arc/container/tree_def.h>

/* Standard node definition */
struct arc_bstree_node
{
    struct arc_bstree_node * parent;
    struct arc_bstree_node * left;
    struct arc_bstree_node * right;
    char data[1];
};

typedef struct arc_tree arc_bstree;

#endif
