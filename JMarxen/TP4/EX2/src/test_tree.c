#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

struct user_data {
	int value;
	struct avl_node node;
};

int compare_user_data(const void *a, const void *b) {
	int val_a = ((struct user_data *)a)->value;
	int val_b = ((struct user_data *)b)->value;
	return val_a - val_b;
}

void print_tree(struct avl_tree *t, struct avl_node *node, int level) {
	if (node == NULL) {
		return;
	}
	print_tree(t, node->right, level + 1);
	for (int i = 0; i < level; i++) {
		printf("    ");
	}
	struct user_data *data = get_data(t, node);
	printf("%d\n", data->value);
	print_tree(t, node->left, level + 1);
}

int main(int argc, char *argv[]) {
	struct avl_tree tree;
	avl_tree_initialize(&tree, compare_user_data,
			    offsetof(struct user_data, node));
	printf("Tree intitialized. \n");
	// Test data
	int values[] = {20, 15, 10, 30, 5, 40, 25};
	int n = sizeof(values) / sizeof(values[0]);
	// Insert values into the AVL tree
	for (int i = 0; i < n; i++) {
		struct user_data *new_data =
		    (struct user_data *)malloc(sizeof(struct user_data));
		new_data->value = values[i];
		struct avl_node *node =
		    (struct avl_node *)malloc(sizeof(struct avl_node));
		node->left = NULL;
		node->right = NULL;
		node->height = 1;
		new_data->node = *node;
		printf("Insert node %d with value %d. \n", i, values[i]);
		avl_tree_insert(&tree, new_data);
		printf("Inserted.\n");
		print_tree(&tree, tree.root, 0);
	}
	printf("Values inserted. \n");
	print_tree(&tree, tree.root, 0);
	// Test finding values in the AVL tree
	int find_values[] = {15, 100};	// 15 exists, 100 not
	for (int i = 0; i < 2; i++) {
		struct user_data temp_data;
		temp_data.value = find_values[i];
		struct user_data *found_data =
		    (struct user_data *)avl_tree_find(&tree, &temp_data);
		if (found_data) {
			printf("Found value: %d\n", found_data->value);
		} else {
			printf("Value %d not found in the tree.\n",
			       find_values[i]);
		}
	}
	return 0;
}
