#include "AVL_Tree.h"

#include <assert.h>
#include <stdlib.h>

/* Convert node pointer -> user data pointer using the intrusive offset */
static inline void *node_to_data(const struct avl_tree *t, const struct avl_node *n)
{
    return (void *)((char *)n - t->offset);
}

/* Convert user data pointer -> node pointer using the intrusive offset */
static inline struct avl_node *data_to_node(const struct avl_tree *t, void *data)
{
    return (struct avl_node *)((char *)data + t->offset);
}

static inline int height(const struct avl_node *n)
{
    return n ? n->height : 0;
}

static inline int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

static inline void update_height(struct avl_node *n)
{
    if (!n) return;
    n->height = 1 + max_int(height(n->left), height(n->right));
}

/* balance factor = height(right) - height(left) */
static inline int balance_factor(const struct avl_node *n)
{
    if (!n) return 0;
    return height(n->right) - height(n->left);
}

/* Right rotation:
        y              x
       / \            / \
      x  T3   ==>    T1  y
     / \                / \
    T1 T2              T2 T3
*/
static struct avl_node *rotate_right(struct avl_node *y)
{
    assert(y && y->left);
    struct avl_node *x = y->left;
    struct avl_node *T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);
    return x;
}

/* Left rotation:
      x                 y
     / \               / \
    T1  y     ==>     x  T3
       / \           / \
      T2 T3         T1 T2
*/
static struct avl_node *rotate_left(struct avl_node *x)
{
    assert(x && x->right);
    struct avl_node *y = x->right;
    struct avl_node *T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);
    return y;
}

static struct avl_node *rebalance(struct avl_node *n)
{
    if (!n) return n;

    update_height(n);
    int bf = balance_factor(n);

    /* Right heavy */
    if (bf > 1) {
        if (balance_factor(n->right) < 0) {
            /* Right-Left case */
            n->right = rotate_right(n->right);
        }
        return rotate_left(n);
    }

    /* Left heavy */
    if (bf < -1) {
        if (balance_factor(n->left) > 0) {
            /* Left-Right case */
            n->left = rotate_left(n->left);
        }
        return rotate_right(n);
    }

    return n;
}

/* Recursive insert: returns new subtree root.
   If duplicate (cmp == 0), do nothing and return existing root. */
static struct avl_node *insert_rec(struct avl_tree *t,
                                  struct avl_node *root,
                                  struct avl_node *new_node,
                                  void *new_data)
{
    if (!root) {
        return new_node;
    }

    void *root_data = node_to_data(t, root);
    int c = t->cmp(new_data, root_data);

    if (c < 0) {
        root->left = insert_rec(t, root->left, new_node, new_data);
    } else if (c > 0) {
        root->right = insert_rec(t, root->right, new_node, new_data);
    } else {
        /* Duplicate key: ignore insertion */
        return root;
    }

    return rebalance(root);
}

void avl_tree_initialize(struct avl_tree *t,
                         int (*cmp)(const void *, const void *),
                         int offset)
{
    assert(t);
    assert(cmp);
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}

void *avl_tree_find(struct avl_tree *t, const void *data)
{
    assert(t && t->cmp);

    struct avl_node *cur = t->root;
    while (cur) {
        void *cur_data = node_to_data(t, cur);
        int c = t->cmp(data, cur_data);

        if (c == 0) {
            return cur_data;
        } else if (c < 0) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return NULL;
}

void avl_tree_insert(struct avl_tree *t, void *data)
{
    assert(t && t->cmp);
    assert(data);

    struct avl_node *n = data_to_node(t, data);

    /* Initialize node fields for first insertion */
    n->left = NULL;
    n->right = NULL;
    n->height = 1;

    t->root = insert_rec(t, t->root, n, data);
}
