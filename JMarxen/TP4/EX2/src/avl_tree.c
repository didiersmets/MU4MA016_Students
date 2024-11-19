#include "avl_tree.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) { return (a > b) ? a : b; }

void avl_tree_initialize(struct avl_tree *t,
			 int (*cmp)(const void *, const void *), int offset) {
	t->root = NULL;
	t->cmp = cmp;
	t->offset = offset;
}

struct avl_node *left_rotate(struct avl_node *x) {
	// Root node - x; left node - T2; right node - y
	struct avl_node *y = x->right;
	struct avl_node *T2 = y->left;
	y->left = x;
	x->right = T2;
	printf("Left rotate.\n");
	x->height = max(x->left ? x->left->height : 0,
			x->right ? x->right->height : 0) +
		    1;
	y->height = max(y->left ? y->left->height : 0,
			y->right ? y->right->height : 0) +
		    1;
	return y;  // new root
}

struct avl_node *right_rotate(struct avl_node *y) {
	// Root node - y; left node - x; right node - T2
	struct avl_node *x = y->left;
	struct avl_node *T2 = x->right;
	x->right = y;
	y->left = T2;
	printf("Right rotate.\n");
	y->height = max(y->left ? y->left->height : 0,
			y->right ? y->right->height : 0) +
		    1;
	x->height = max(x->left ? x->left->height : 0,
			x->right ? x->right->height : 0) +
		    1;
	return x;  // new root
}

struct user_data *get_data(struct avl_tree *tree, struct avl_node *node) {
	return (struct user_data *)((char *)node - tree->offset);
}

int compare_nodes(struct avl_tree *tree, struct avl_node *node1,
		  struct avl_node *node2) {
	struct user_data *data1 = get_data(tree, node1);
	struct user_data *data2 = get_data(tree, node2);
	return tree->cmp(data1, data2);
}

int get_balance(struct avl_node *node) {
	return node ? (node->left->height - node->right->height) : 0;
}

void *avl_tree_find(struct avl_tree *t, const void *data) {
	struct avl_node *curr_node = t->root;
	while (curr_node != NULL) {
		struct user_data *curr_data = get_data(t, curr_node);
		int cmp_result = t->cmp(data, curr_data);
		if (cmp_result == 0) {
			return curr_data;
		} else if (cmp_result < 0) {
			curr_node = curr_node->left;
		} else {
			curr_node = curr_node->right;
		}
	}
	return NULL;
}

struct avl_node *avl_insert_recursive(struct avl_tree *t, struct avl_node *node,
				      void *data) {
	if (node == NULL) {
		printf("Reached leaf node. Inserting new leaf node. \n");
		struct avl_node *new_node =
		    (struct avl_node *)((char *)data + (t->offset));
		return new_node;
	}
	struct user_data *node_data = get_data(t, node);

	if (t->cmp(data, node_data) <= 0) {
		// Insert into left suotree
		printf("Left insert.\n");
		node->left = avl_insert_recursive(t, node->left, data);
	} else {
		// Insert into right subtree
		printf("Right insert.\n");
		node->right = avl_insert_recursive(t, node->right, data);
	}
	// Update height of node
	int left_height = node->left ? node->left->height : 0;
	int right_height = node->right ? node->right->height : 0;
	node->height =
	    (left_height > right_height ? left_height : right_height) + 1;
	printf("Height: %d; Left Height: %d; Right Height: %d \n", node->height,
	       left_height, right_height);
	// Balance the node if unbal_banced:
	int balance = left_height - right_height;
	printf("Balancing node with balance factor %d...\n", balance);
	// Left Left case
	if (balance > 1 && node->left &&
	    t->cmp(data, get_data(t, node->left)) <= 0)
		return right_rotate(node);
	// Right Right Case
	if (balance < -1 && node->right &&
	    t->cmp(data, get_data(t, node->right)) > 0)
		return left_rotate(node);
	// Left Right Case
	if (balance > 1 && node->left &&
	    t->cmp(data, get_data(t, node->left)) > 0) {
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	// Right Left case
	if (balance < -1 && node->right &&
	    t->cmp(data, get_data(t, node->right)) <= 0) {
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
}

// It is much easier to use recursion in this case
void avl_tree_insert(struct avl_tree *t, void *data) {
	t->root = avl_insert_recursive(t, t->root, data);
}

