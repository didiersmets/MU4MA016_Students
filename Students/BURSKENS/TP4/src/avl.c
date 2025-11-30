#include <avl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset){
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}

void update_height(struct avl_node* n){
    if(n == NULL){
        return;
    }
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
    //printf("Root info: %s\n", (char*)((char*)t->root - t->offset + offsetof(struct user_data, info)));
    struct user_data* data1 = (struct user_data*)data;
    void* find_info = data1->info;
    //printf("Searching for: %s\n", (char*)find_info);
    while(current != NULL){
        void* current_data = (void*)((char*)current - t->offset);
        void* current_info = ((struct user_data*)current_data)->info;
        //printf("At node: %s\n", (char*)current_info);
        int cmp_result = t->cmp(find_info, current_info);
        if(cmp_result == 0){
            return current_data;
        }
        else if(cmp_result < 0){
            current = current->left;
            //printf("Going left\n");
        }
        else{
            current = current->right;
            //printf("Going right\n");
        }
    }
    return NULL;
}

void rebalance_tree_post_insert(struct avl_tree *t, const void *data){
    struct avl_node* current = t->root;
    struct user_data* data1 = (struct user_data*)data;
    while(current != NULL){
        update_height(current);
        int balance_factor = (current->left ? current->left->height : 0) -
                             (current->right ? current->right->height : 0);
        //printf("Balance factor: %d\n", balance_factor);
        if(balance_factor > 1){
            if(t->cmp(data1->info, (void*)((char*)current->left - t->offset)) <= 0){
                if(current == t->root){
                    t->root = current->left;
                }
                current = avl_rotation_right(current);
                //printf("Performed right rotation\n");
            }
            else{
                current->left = avl_rotation_left(current->left);
                if(current == t->root){
                    t->root = current->left;
                }
                //printf("Performed child-left, parent-right rotation\n");
                current = avl_rotation_right(current);
            }
        }
        else if(balance_factor < -1){
            if(t->cmp(data1->info, (void*)((char*)current->right - t->offset)) > 0){
                if(current == t->root){
                    t->root = current->right;
                }
                current = avl_rotation_left(current);
                //printf("Performed left rotation\n");
            }
            else{
                current->right = avl_rotation_right(current->right);
                if(current == t->root){
                    t->root = current->right;
                }
                //printf("Performed child-right, parent-left rotation\n");
                current = avl_rotation_left(current);
            }
        }
        if(t->cmp(data1->info, (void*)((char*)current - t->offset)) <=  0){
            current = (current->left);
            //printf("Moving left for rebalance\n");
        }
        else{
            current = (current->right);
            //printf("Moving right for rebalance\n");
        }
    }
}

void avl_tree_insert(struct avl_tree *t, void *data){
    struct user_data* data1 = (struct user_data*)data;
    data1->node.left = NULL;
    data1->node.right = NULL;
    data1->node.height = 1;
    if(t->root == NULL){
        /*struct avl_node** temp2 = (void*)((char*)(data) + t->offset);
        //struct avl_node* temp2 = *temp;
        (*temp2)->height = 1;
        t->root = (*temp2);*/
        t->root = &data1->node;
        struct user_data *root_data = (struct user_data*)(&data1->node - t->offset);
        //printf("Inserted root: %s\n", root_data->info);
        //printf("Inserted root: %s\n", t->root ? (char*)((char*)t->root - t->offset + offsetof(struct user_data, info)) : "NULL");
    }
    else{
        void* insert_info = data1->info;
        //printf("Inserting: %s\n", (char*)insert_info);
        struct avl_node* current = t->root;
        struct avl_node* parent = NULL;
        struct avl_node* (*visited_nodes) = malloc(sizeof(struct avl_node)*t->root->height);
        for(int i = 0; i < t->root->height; i++){
            visited_nodes[i] = NULL;
        }
        int index = 0;
        int cmp_result = 0;
        while(current != NULL){
            struct user_data* current_user_data = (struct user_data*)((char*)(current) - t->offset);
            void* current_info = current_user_data->info;
            //printf("At node: %s\n", (char*)current_info);
            cmp_result = t->cmp(insert_info, current_info);
            visited_nodes[index] = current;
            index++;
            parent = current;
            if(cmp_result <= 0){
                current = (current->left);
                //printf("Going left in insert\n");
            }
            else{
                current = (current->right);
                //printf("Going right in insert\n");
            }
        }
        if(current == NULL){
            //struct user_data** parent_user_data = (void*)((char*)(current) - t->offset);
            //void* parent_info = (*parent_user_data)->info;
            //int cmp_result = t->cmp(insert_info, parent_info);
            //struct avl_node** temp2 = (void*)((char*)(data) + t->offset);
            ////struct avl_node* temp2 = *temp;
            //(*temp2)->height = 1;
            if(cmp_result <= 0){
                parent->left = &data1->node;
            }
            else{
                parent->right = &data1->node;
            }
        }
        int end = t->root->height;
        for(int i = 1; i <= end; i++){
            update_height(visited_nodes[end-i]);
        }
        free(visited_nodes);
        rebalance_tree_post_insert(t,data);
    }
}
