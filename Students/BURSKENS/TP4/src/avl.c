#include <avl.h>
#include <stdlib.h>
#include <stdio.h>

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset){
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}

void update_height(struct avl_node* n){
    int left_height = (n->left) ? n->left->height : 0;
    int right_height = (n->right) ? n->right->height : 0;
    n->height = 1 + ((left_height > right_height) ? left_height : right_height);
}

static struct avl_node* avl_rotation_right(struct avl_node* pivot){
    struct avl_node* new_root = pivot->left;
    pivot->left = new_root->right;
    new_root->right = pivot;
    update_height(pivot);
    update_height(new_root);
    return new_root;
}

static struct avl_node* avl_rotation_left(struct avl_node* pivot){
    struct avl_node* new_root = pivot->right;
    pivot->right = new_root->left;
    new_root->left = pivot;
    update_height(pivot);
    update_height(new_root);
    return new_root;
}

void *avl_tree_find(struct avl_tree *t, const void *data){
    struct avl_node* current = t->root;
    while(current != NULL){
        void* current_data = (void*)((char*)current - t->offset);
        int cmp_result = t->cmp(data, current_data);
        if(cmp_result == 0){
            return current_data;
        }
        else if(cmp_result < 0){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    return NULL;
}

void rebalance_tree_post_insert(struct avl_tree *t, const void *data){
    struct avl_node* current = t->root;
    while(current != NULL){
        update_height(current);
        int balance_factor = (current->left ? current->left->height : 0) -
                             (current->right ? current->right->height : 0);
        if(balance_factor > 1){
            if(t->cmp(data, (void*)((char*)current->left - t->offset)) < 0){
                current = avl_rotation_right(current);
            }
            else{
                current->left = avl_rotation_left(current->left);
                current = avl_rotation_right(current);
            }
        }
        else if(balance_factor < -1){
            if(t->cmp(data, (void*)((char*)current->right - t->offset)) > 0){
                current = avl_rotation_left(current);
            }
            else{
                current->right = avl_rotation_right(current->right);
                current = avl_rotation_left(current);
            }
        }
        if(t->cmp(data, (void*)((char*)current - t->offset)) < 0){
            current = (current->left);
        }
        else{
            current = (current->right);
        }
    }
}

void avl_tree_insert(struct avl_tree *t, void *data){
    struct avl_node* current = t->root;
    struct avl_node* parent = NULL;
    struct avl_node* visited_nodes = malloc(sizeof(struct avl_node)*t->root->height);
    for(int i = 0; i < t->root->height; i++){
        visited_nodes[i] = NULL;
    }
    int index = 0;
    while(current != NULL){
        void* current_data = (void*)((char*)(current) - t->offset);
        int cmp_result = t->cmp(data, current_data);
        visited_nodes[i] = current;
        i++;
        parent = current;
        if(cmp_result < 0){
            current = (current->left);
        }
        else{
            current = (current->right);
        }
    }
    if(current == NULL){
        void* parent_data = (void*)((char*)(parent) - t->offset);
        int cmp_result = t->cmp(data, parent_data);
        (void*)((char*)(data) + t->offset)->height = 1;
        if(cmp_result < 0){
            parent->left = (void*)((char*)(data) + t->offset);
        }
        else{
            parent->right = (void*)((char*)(data) + t->offset);
        }
    }
    int end = t->root->height;
    for(int i = 1; i <= end; i++){
        update_height(visited_nodes[end-1]);
    }
    rebalance_tree_post_insert(t,data);
}
