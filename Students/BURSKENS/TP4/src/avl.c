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

void avl_tree_insert(struct avl_tree *t, void *data){
    struct avl_node** current = &t->root;
    struct avl_node* parent = NULL;
    while(*current != NULL){
        void* current_data = (void*)((char*)(*current) - t->offset);
        int cmp_result = t->cmp(data, current_data);
        parent = *current;
        if(cmp_result < 0){
            current = &((*current)->left);
        }
        else{
            current = &((*current)->right);
        }
    }
    struct avl_node* new_node = malloc(sizeof(struct avl_node));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    *current = new_node;

    // Rebalance the tree
    current = &t->root;
    while(current != NULL){
        update_height(*current);
        int balance_factor = ((*current)->left ? (*current)->left->height : 0) - 
                             ((*current)->right ? (*current)->right->height : 0);
        if(balance_factor > 1){
            // Left heavy
            if(t->cmp(data, (void*)((char*)(*current)->left - t->offset)) < 0){
                // Left-Left case
                *current = avl_rotation_right(*current);
            }
            else{
                // Left-Right case
                (*current)->left = avl_rotation_left((*current)->left);
                *current = avl_rotation_right(*current);
            }
        }
        else if(balance_factor < -1){
            // Right heavy
            if(t->cmp(data, (void*)((char*)(*current)->right - t->offset)) > 0){
                // Right-Right case
                *current = avl_rotation_left(*current);
            }
            else{
                // Right-Left case
                (*current)->right = avl_rotation_right((*current)->right);
                *current = avl_rotation_left(*current);
            }
        }
        if(parent == NULL) break;
        if(t->cmp(data, (void*)((char*)parent - t->offset)) < 0){
            current = &(parent->left);
        }
        else{
            current = &(parent->right);
        }
        parent = NULL; // To avoid infinite loop, as we don't keep track of ancestors here
    }
}