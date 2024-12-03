#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

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

static void update_height(struct avl_node *root){
	if (!root) return;
	int left = root->left ? root->left->height : 0;
	int right = root->right ? root->right->height : 0;
	root->height = 1 + (left > right ? left : right);
}

static int get_balance(struct avl_node *root){
	if (!root) return 0;
	int left = root->left ? root->left->height : 0;
	int right = root->right ? root->right->height : 0;
	return right - left;
}

static struct avl_node *rotate(struct avl_node *root, bool dir){
	assert(root);
	struct avl_node *next_root;
	if(dir==0) next_root = root->right;
	if(dir==1) next_root = root->left;
	assert(next_root);
	struct avl_node *tmp;
	if(dir==0) tmp = next_root->left;
	if(dir==1) tmp = next_root->right;
	if(dir==0) root->right = tmp;
	if(dir==1) root->left = tmp;
	if(dir==0) next_root->left = root;
	if(dir==1) next_root->right = root;
	update_height(root);
        update_height(next_root);
	return next_root;
}

static struct avl_node *fix_balance(struct avl_node *root) {
	int b = get_balance(root);
	if (abs(b) <= 1) return root;
	/* dir = heavy direction = ! rotate direction */
	bool dir = b > 0;
	int b2;
	if(dir==0) b2 = get_balance(root->left);
	if(dir==1) b2 = get_balance(root->right);
	bool dir2 = b2 > 0;
	if (b2 && (dir != dir2)){ 
		if(dir==0) root->left = rotate(root->left, !dir2);
		if(dir==1) root->right = rotate(root->right, !dir2);
	}
	root = rotate(root, !dir);
	return root;
}

struct avl_node *avl_tree_insert(struct avl_tree *t, struct avl_node *current_node, void *data){

	int offset = t->offset;
	void *current_data = (void*) (current_node - offset);
	int res=(t->cmp)(data,current_data);

	if(res==0) {
		return current_node; // data already present
	} else if(res<0){
		if(current_node->left != NULL){
			current_node = avl_tree_insert(t,current_node->left,data);
			update_height(current_node);
			current_node = fix_balance(current_node);

		} else { // insert new node here
			current_node->left = (struct avl_node*) ((char*) data) + offset;
		}	
		
	} else {
		if(current_node->right != NULL){
			current_node = avl_tree_insert(t,current_node->right,data);
			update_height(current_node);
			current_node = fix_balance(current_node);
		} else {
			current_node->left = (struct avl_node*) ((char*) data) + offset;
		}
	}	
	return current_node;
}
