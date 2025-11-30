#include <stdlib.h>
#include <string.h>

struct avl_node {
 struct avl_node* left;
 struct avl_node* right;
 int height;
};

struct avl_tree {
struct avl_node* root;
int (*cmp)(const void *, const void *);
int offset;
};

struct user_data {
 char info[16];
 /*
 * whatever struct fields before node, possibly none
 */
 struct avl_node node;
 /*
 * whatever struct fields after node, possibly none
 */
 };

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *),int offset);

void *avl_tree_find(struct avl_tree *t, const void *data);
void avl_tree_insert(struct avl_tree *t, void *data);

//void rebalance_tree_post_insert(struct avl_tree *t, const void *data);
