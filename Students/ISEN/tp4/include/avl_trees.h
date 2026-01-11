#include <stdlib.h>
#include <string.h> //NULL, ...
#include <stdbool.h>
#include <stdio.h>


struct avl_node{
    struct avl_node *left;
    struct avl_node *right;
    int height;
};

struct avl_tree{
    struct avl_node *root;
    int (*cmp)(const void *, const void *);
    int offset;
};


void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset);
void *avl_tree_find(struct avl_tree *t, const void *data);
void avl_tree_insert(struct avl_tree *t, void *data);
struct avl_node *fix_balance(struct avl_node *root);
struct avl_node *avl_tree_insert_rec(struct avl_tree *t, void *data, struct avl_node *n);
