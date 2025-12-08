//question 2 (Intrusive) AVL trees
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> 

struct avl_node {
    struct avl_node *left;
    struct avl_node *right;
    int height;
};

struct avl_tree {
    struct avl_node *root;
    int (*cmp)(const void *, const void *);
    int offset;
};

static struct avl_node *get_node(struct avl_tree *t, void *data) {
    return (struct avl_node *)((char *)data + t->offset);
}


static void *get_data(struct avl_tree *t, struct avl_node *node) {
    return (void *)((char *)node - t->offset);
}

static int height(struct avl_node *n) {
    return n ? n->height : 0;
}

static void update_height(struct avl_node *n) {
    int hl = height(n->left);
    int hr = height(n->right);
    n->height = (hl > hr ? hl : hr) + 1;
}

static int balance_factor(struct avl_node *n) {
    return height(n->left) - height(n->right);
}

static struct avl_node *rotate_right(struct avl_node *y) {
    struct avl_node *x = y->left;
    struct avl_node *T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    return x;   // 新子树根
}

static struct avl_node *rotate_left(struct avl_node *x) {
    struct avl_node *y = x->right;
    struct avl_node *T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    return y;   // 新子树根
}

static struct avl_node *rebalance(struct avl_tree *t, struct avl_node *node) {
    update_height(node);
    int bf = balance_factor(node);

    if (bf > 1) {  // 左边太高
        // 判断是 LL 还是 LR
        if (balance_factor(node->left) < 0)
            node->left = rotate_left(node->left);  // 先左旋孩子
        return rotate_right(node);
    } else if (bf < -1) {  // 右边太高
        if (balance_factor(node->right) > 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

void avl_tree_initialize(struct avl_tree *t,
                         int (*cmp)(const void *, const void *),
                         int offset)
{
    t->root   = NULL;
    t->cmp    = cmp;
    t->offset = offset;
}

void *avl_tree_find(struct avl_tree *t, const void *data)
{
    struct avl_node *cur = t->root;

    while (cur != NULL) {
        void *cur_data = get_data(t, cur);   // 从结点拿回 user_data*
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

static struct avl_node *insert_rec(struct avl_tree *t,
                                   struct avl_node *root,
                                   void *data)
{
    struct avl_node *new_node = get_node(t, data);

    if (root == NULL) {
        new_node->left = new_node->right = NULL;
        new_node->height = 1;
        return new_node;
    }

    void *root_data = get_data(t, root);
    int c = t->cmp(data, root_data);

    if (c < 0) {
        root->left = insert_rec(t, root->left, data);
    } else if (c > 0) {
        root->right = insert_rec(t, root->right, data);
    } else {
        return root;
    }
    return rebalance(t, root);
}

void avl_tree_insert(struct avl_tree *t, void *data)
{
    t->root = insert_rec(t, t->root, data);
}
