#pragma once
#include <stdint.h>

struct avl_node {
    void* children[2];
    uintptr_t pcb;
};

struct avl_tree {
    void* root;
    int (*cmp)(const void *, const void *);
    int offset;
};

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset );
void *avl_tree_find(struct avl_tree *t, const void *data);
void avl_tree_insert(struct avl_tree *t, void *data);