#include <stdlib.h>
#include <stddef.h>

#include "../include/avl_trees.h"

int cmp(const void* data1, const void* data2){
	if(data1==data2){
		return 0;
	} else if(data1<data2) {
		return -1;
	} else {
		return 1;
	}
}

int main(){
	struct avl_tree *t = (struct avl_tree*) malloc(sizeof(struct avl_tree));
	avl_tree_initialize(t,cmp,offsetof(struct user_data,node));

	struct user_data *data1 = (struct user_data*) malloc(sizeof(struct user_data));
	data1->d1 = 1;
	struct avl_node node1;
	node1.left = NULL;
	node1.right = NULL;
	node1.height = 0;
	data1->node = node1;
	data1->d2 = 1.0;	
	avl_tree_insert(t,t->root,data1);

	return 0;
}
