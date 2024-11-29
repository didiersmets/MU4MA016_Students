#include <stdlib.h>

#include "../include/avl_trees.h"

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void*, const void*), int offset){
	t->offset = offset;
	t->cmp = cmp;
}


// cmp(a,b) = -1 a<b
// cmp(a,b) = 0 a=b
// cmp(a,b) = 1 a>b
void* avl_tree_find(struct avl_tree *t, const void *data){
	int offset = t->offset;
	struct avl_node *current_node = t->root - offset;
	void *current_data = (void*) (t->root - offset);
	int res=(t->cmp)(data,current_data);
	while(!res){
		if(res<0){
			current_node = current_node->left;
		} else {
			current_node = current_node->right;
		}
		current_data = (void*) (current_node - offset);
		res=(t->cmp)(data,current_data);

	}
	return current_data;
}

void avl_tree_insert(struct avl_tree *t, void *data){

	// Step 1: insert as in a binary tree
	int offset = t->offset;
	struct avl_node *current_node = t->root;
	void *current_data = (void*) (t->root - offset);
	int res=(t->cmp)(data,current_data);
	while(current_node!=NULL){
		if(res==0) {
			return; // data already present
		} else if(res<0){
			if(current_node->left != NULL){
				current_node = current_node->left;
			} else { // insert new node here
				current_node->left = (struct avl_node*) ((char*) data) + offset;
			}
		} else {
			if(current_node->right != NULL){
				current_node = current_node->right;
			} else {
				current_node->left = (struct avl_node*) ((char*) data) + offset;
			}
		}
		current_data = (void*) (current_node - offset);
		res=(t->cmp)(data,current_data);
	}

	// Step 2: update height 
	

	// Step 3: balance
	
	
}
