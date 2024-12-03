struct avl_node {
	struct avl_node *left;
	struct avl_node *right;
	int height;
};

struct avl_tree {
	struct avl_node *root;
	int (*cmp)(const void*, const void*);
	int offset;
};

struct user_data{
	int d1;
	struct avl_node node;
	float d2;
};

void avl_tree_initialize(struct avl_tree *t ,int (*cmp)(const void* , const void*), int offset);
void* avl_tree_find(struct avl_tree *t, const void *data);
struct avl_node *avl_tree_insert(struct avl_tree *t, struct avl_node *current_node, void *data);





