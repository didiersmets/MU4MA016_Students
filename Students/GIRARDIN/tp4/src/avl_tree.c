#include <stddef.h>
#include <stdlib.h>
#include "../include/avl_tree.h"

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *),
                                int offset){
    (t->cmp) = cmp;         //cmp is 0 if they are equal, <0 if 1st < 2nd & >0 if 1st > 2nd
    (t->offset) = offset;
}

//--------------------------------------------------------------------
static void avl_tree_rebalance(struct avl_tree* t);
//--------------------------------------------------------------------
void *avl_tree_find(struct avl_tree *t, const void *data){

    struct avl_node *n = t->root;

    while((n != NULL) && (cmp(data, (char *)n - t->offset))){       //cmp = 0 (false) if data is found
        if(cmp(data, (char *)(n->left) - t->offset) <= 0){          //data is smaller than left child of n
            n = n->left;
        }else if(cmp(data, (char *)(n->right) - t->offset) <= 0){   //data is smaller than right child of n
            n = n->right;
        }   
    }

    return n;
}

//--------------------------------------------------------------------
void avl_tree_insert(struct avl_tree *t, void *data){

    if(t->root == NULL){
        //Assign the new root
        struct avl_node n = {NULL, NULL, 1};
        t->root = &n;
        *((struct avl_node *)data + t->offset) = n;

    }else{
        
        //Start at the root of the tree
        struct avl_node *n = t->root;
        
        //Find node n where to insert new node
        while((n != NULL) && (cmp(data, (char *)n - t->offset) <= 0)){  //data is smaller than current node
            if(cmp(data, (char *)(n->left) - t->offset) < 0){           //data is smaller than left child of n
                n = n->left;
            }else if(cmp(data, (char *)(n->right) - t->offset) < 0){    //data is smaller than right child of n
                n = n->right;
            }else{                                                      //data is bigger than both children
                break;
            }   
        }

        //Decide side of n to insert new node
        if(n->left == NULL){            //no children
            struct avl_node new = {NULL, NULL, 1};
            (n->left) = &new;
        }else if (n->right == NULL){    //only left child
            struct avl_node new = {NULL,  NULL, 1};
            (n->right) = &new;
        }else{                          //two children; replace left one
            //Compute height
            int left_h = (n->left)->left ? (n->left)->left->height : 0;
            int right_h = (n->left)->right ? (n->left)->right->height : 0;
            int height = 1 + (left_h > right_h ? left_h : right_h);

            struct avl_node new = {(n->left)->left, (n->left)->right, height};
            (n->left) = &new;   
        }
        
        *((struct avl_node *)data + t->offset) = *n;
        avl_tree_rebalance(t);    
    }
}