#include "avl_tree.h"

static void *node_to_data(struct avl_tree *t, struct avl_node *n)
{
    return (void *)((char *)n - t->offset);
}

static struct avl_node *data_to_node(struct avl_tree *t, void *data)
{
    return (struct avl_node *)((char *)data + t->offset);
}

static int h(struct avl_node *n)
{
    return n ? n->height : 0;
}

static int max2(int a, int b) { return (a > b) ? a : b; }

static void update_height(struct avl_node *n)
{
    n->height = 1 + max2(h(n->left), h(n->right));
}

static int balance_factor(struct avl_node *n)
{
    return h(n->left) - h(n->right);
}

static struct avl_node *rotate_right(struct avl_node *y)
{
    struct avl_node *x = y->left;
    struct avl_node *T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);
    return x;
}

static struct avl_node *rotate_left(struct avl_node *x)
{
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
    update_height(n);
    int bf = balance_factor(n);

    // Left heavy
    if (bf > 1)
    {
        if (balance_factor(n->left) < 0)
        {
            n->left = rotate_left(n->left);
        }
        return rotate_right(n);
    }

    // Right heavy
    if (bf < -1)
    {
        if (balance_factor(n->right) > 0)
        {
            n->right = rotate_right(n->right);
        }
        return rotate_left(n);
    }

    return n;
}

void avl_tree_initialize(struct avl_tree *t,
                         int (*cmp)(const void *, const void *),
                         int offset)
{
    t->root = 0;
    t->cmp = cmp;
    t->offset = offset;
}

void *avl_tree_find(struct avl_tree *t, const void *data)
{
    struct avl_node *cur = t->root;
    while (cur)
    {
        void *cur_data = node_to_data(t, cur);
        int c = t->cmp(data, cur_data);
        if (c == 0)
            return cur_data;
        if (c < 0)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return 0;
}

static struct avl_node *insert_rec(struct avl_tree *t, struct avl_node *root, void *data)
{
    struct avl_node *n = data_to_node(t, data);

    if (!root)
    {
        n->left = 0;
        n->right = 0;
        n->height = 1;
        return n;
    }

    void *root_data = node_to_data(t, root);
    int c = t->cmp(data, root_data);

    if (c < 0)
        root->left = insert_rec(t, root->left, data);
    else if (c > 0)
        root->right = insert_rec(t, root->right, data);
    else
        return root;

    return rebalance(root);
}

void avl_tree_insert(struct avl_tree *t, void *data)
{
    t->root = insert_rec(t, t->root, data);
}
