#include "avl_trees.h"
//#include <stdlib.h>
#include <string.h> //NULL, ...


void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset){
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}


void *avl_tree_find(struct avl_tree *t, const void *data){
    if(t->root == NULL){  //tree empty
        printf("Tree empty, search failed");
        return;
    }
    struct avl_node *curr_node = t->root;  //start with root and go down
    while(curr_node != NULL){
        //address of user data: substract offset from address of the node
        void *curr_data = &curr_node - t->offset;
        //comparing two struct user_data: use cmp
        int comp = t->cmp(data, curr_data);
        if(comp == 0){  //true
            print("found");
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

void avl_tree_insert(struct avl_tree *t, void *data){
   *t->root = avl_tree_insert_rec(t, data, t->root);
}

struct avl_node avl_tree_insert_rec(struct avl_tree *t, void *data, struct avl_node *n){
    //first case: no root in tree // return condition
    if(n == NULL){ 
        struct avl_node *new_node = data + t->offset;
        new_node->height = 1;
        new_node->left = NULL; 
        new_node->right = NULL;
        return *new_node;
    }
    
    void *curr_data = &n - t->offset;
    int comp = t->cmp(data, curr_data);  //data of node and data to insert
    if(comp == 0){
        return n; //--> already exists
    } else if(comp < 0){
        n->left = avl_tree_insert_rec(t, data, n->left);
    } else {
        n->right = avl_tree_insert_rec(t, data, n->right);
    }
    update_height(n);
    fix_balance(n);
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

static void uptdate_height(struct avl_node *root){
    //also from course_notes
    if (!root){
        return;
    }
    int left = root->left ? root->left->height : 0;
    int right = root->right ? root->right->height :0;
    root->height = 1 + (left > right ? left : right);
}


struct avl_node *fix_balance(struct avl_node *root){
    int b = get_balance(root);
    if(abs(b) <= 1){  //no balancing needed
        return root; 
    }
    //....
}



static void left_rotate(){

}
static void right_rotate(){

}
