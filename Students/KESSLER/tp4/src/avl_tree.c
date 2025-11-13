#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

int get_balance(struct avl_node *node) {
    if (!node) return 0;
    int left_height = (node->left) ? node->left->height : 0;
    int right_height = (node->right) ? node->right->height : 0;
    return left_height - right_height;
}

void update_height(struct avl_node *node) {
    if (!node) return;
    int left_height = (node->left) ? node->left->height : 0;
    int right_height = (node->right) ? node->right->height : 0;
    node->height = (left_height > right_height ? left_height : right_height) + 1;
}

struct avl_node *rotate_right(struct avl_node *root) {
    if (!root || !root->left) return root; // Cannot perform right rotation
    struct avl_node *new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;

    // Update heights
    update_height(new_root);
    update_height(root);

    return new_root;
}

struct avl_node *rotate_left(struct avl_node *root) {
    if (!root || !root->right) return root; // Cannot perform left rotation
    struct avl_node *new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;

    // Update heights
    update_height(new_root);
    update_height(root);

    return new_root;
}

struct avl_node *fix_tree(struct avl_node *node) {
    if (!node) return node;
    update_height(node);
    int balance = get_balance(node);

    // Left heavy
    if (balance > 1) {
        if (get_balance(node->left) < 0) {
            // Left-Right case
            node->left = rotate_left(node->left);
        }
        // Left-Left case
        return rotate_right(node);
    }
    // Right heavy
    if (balance < -1) {
        if (get_balance(node->right) > 0) {
            // Right-Left case
            node->right = rotate_right(node->right);
        }
        // Right-Right case
        return rotate_left(node);
    }
    return node;
}

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset) {
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}

void *avl_tree_find(struct avl_tree *t, const void *data) {
    struct avl_node *current = t->root;
    while (current) {
        void *current_data = (void *)((char *)current - t->offset);
        int cmp_result = t->cmp(data, current_data);
        if (cmp_result == 0) {
            return current_data;
        } else if (cmp_result < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL; // Not found
}


struct avl_node *recursive_insert(struct avl_tree *t, struct avl_node *node, void *data) {
    if (!node) {
        struct avl_node *new_node = (struct avl_node *)((char *)data + t->offset);
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 1;
        return new_node;
    }

    void *node_data = (void *)((char *)node - t->offset);
    int cmp_result = t->cmp(data, node_data);
    
    if (cmp_result < 0) {
        node->left = recursive_insert(t, node->left, data);
    } else if (cmp_result > 0) {
        node->right = recursive_insert(t, node->right, data);
    } else {
        return node; // Duplicate value
    }

    return fix_tree(node); // update height and rebalance if needed
}

void avl_tree_insert(struct avl_tree *t, void *data) {
    t->root = recursive_insert(t, t->root, data);
}