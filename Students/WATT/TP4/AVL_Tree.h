#pragma once

#include <stddef.h> /* for size_t */

/* Intrusive AVL node: embedded inside user objects */
struct avl_node {
    struct avl_node *left;
    struct avl_node *right;
    int height;
};

struct avl_tree {
    struct avl_node *root;
    int (*cmp)(const void *, const void *);
    int offset; /* offset of the embedded avl_node field within user struct */
};

/* Initialize AVL tree structure */
void avl_tree_initialize(struct avl_tree *t,
                         int (*cmp)(const void *, const void *),
                         int offset);

/* Find an element equal to 'data' (as per cmp); returns user-data pointer or NULL */
void *avl_tree_find(struct avl_tree *t, const void *data);

/* Insert 'data' (user-data pointer). If cmp says it already exists, insertion is ignored. */
void avl_tree_insert(struct avl_tree *t, void *data);
