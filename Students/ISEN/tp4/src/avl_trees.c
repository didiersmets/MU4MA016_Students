#include "..//include/avl_trees.h"
#include <stdlib.h>
#include <string.h> //NULL, ...
#include <stdbool.h>
#include <stdio.h>


void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset){
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}

static int balance_factor(struct avl_node *root){
    //copy from course_notes
    if (!root){
        return 0;
    }
    //height of left child and right child
    int left = root->left ? root->left->height : 0;
    int right = root->right ? root->right->height : 0;
    return right - left;
}

static void update_height(struct avl_node *root){
    //also from course_notes
    if (!root){
        return;
    }
    int left = root->left ? root->left->height : 0;
    int right = root->right ? root->right->height :0;
    root->height = 1 + (left > right ? left : right);
}

static struct avl_node *rotate_right(struct avl_node *root){
    if (!root || !root->left){return root;}
    //th child you want to rotate
    struct avl_node *tmp_child = root;
    //the child of the new root that will be the new left child of the old root
    struct avl_node *tmp_childchild = root->left->right;

    //new root
    root = root->left;
    //right = old root
    root->right = tmp_child;
    //left of the right --> former right of the left child
    root->right->left = tmp_childchild;
    update_height(root->right);
    update_height(root);
    return root;
}

static struct avl_node *rotate_left(struct avl_node *root){
    if (!root || !root->right){return root;}
    struct avl_node *tmp_child = root;
    struct avl_node *tmp_childchild = root->right->left;

    root = root->right;
    root->left = tmp_child;
    root->left->right = tmp_childchild;
    update_height(root->left);
    update_height(root);
    return root;
}

struct avl_node *fix_balance(struct avl_node *root){
    //from course_notes & slightly adapted
    int blnce = balance_factor(root);
    if(abs(blnce) <= 1){  //no balancing needed
        return root; 
    }
    //dir = heavy direction, not rotate direction
    bool dir = blnce > 0;  
    // dir = true --> balance > 0 --> right > left --> right heavy
    // dir = false --> balance < 0 --> left heavy
    
    int bc;  //balance child 
    if(dir){
        //if its right heavy, we wand balance of right child
        bc = balance_factor(root->right);
    }else{
        //if its left heaxy, we want balance of left child
        bc = balance_factor(root->left);
    }

    bool dirc = bc > 0; 
    //dir & dirc different --> first rotation in other direction
    if (bc && (dir != dirc)){
        if(dir){
            root->right = rotate_right(root->right);
        }else{
            root->left = rotate_left(root->left);
        }
    }
    if(dir){
        root = rotate_left(root);
    }else{
        root = rotate_right(root);
    }
    return root;
}


//____________find_____________________________________________________

void *avl_tree_find(struct avl_tree *t, const void *data){
    if(t->root == NULL){  //tree empty
        printf("Tree empty, search failed");
        return NULL;
    }
    struct avl_node *curr_node = t->root;  //start with root and go down
    while(curr_node != NULL){
        //address of user data: substract offset from address of the node
        void *curr_data = (char *)curr_node - t->offset;

        //comparing two struct user_data: use cmp
        int comp = t->cmp(data, curr_data);
        if(comp == 0){  //true
            printf("found");
            return curr_data;
        }
        if(comp < 0){
            curr_node = curr_node->left;
        }
        if(comp > 0){
            curr_node = curr_node->right;
        }
    }
    printf("not found");
    return NULL;
}

//_____________________insert___________________________________________
void avl_tree_insert(struct avl_tree *t, void *data){
   t->root = avl_tree_insert_rec(t, data, t->root);
   printf("Insertion completed");
}

struct avl_node *avl_tree_insert_rec(struct avl_tree *t, void *data, struct avl_node *n){
    //first case: no root in tree // return condition
    if(n == NULL){ 
        struct avl_node *new_node = (struct avl_node *)((char *)data + t->offset);
        new_node->height = 1;
        new_node->left = NULL; 
        new_node->right = NULL;
        return new_node;
    }
    
    void *curr_data = (char*)n - t->offset;
    int comp = t->cmp(data, curr_data);  //data of node and data to insert
    if(comp == 0){
        return n; //--> already exists
    }else if(comp < 0){
        n->left = avl_tree_insert_rec(t, data, n->left);
    }else{
        n->right = avl_tree_insert_rec(t, data, n->right);
    }
    update_height(n);
    n =  fix_balance(n);
    return n;
}



