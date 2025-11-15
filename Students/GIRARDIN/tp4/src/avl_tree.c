#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/avl_tree.h"

#define INIT_CAP 2

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *),
                                int offset){
    t->cmp = cmp;     //cmp is 0 if they are equal, <0 if 1st < 2nd & >0 if 1st > 2nd
    t->offset = offset;
    t->root = NULL;
}

//--------------------------------------------------------------------
static struct avl_node *avl_tree_rebalance(struct avl_node* root);
static void update_height(struct avl_node *n);
//--------------------------------------------------------------------
//data is a user's struct containing a node
void *avl_tree_find(struct avl_tree *t, const void *data){

    struct avl_node *n = t->root;

    if(!n){
        perror("Empty tree");
        exit(2);
    }

    int comp = t->cmp(data, (char *)n - t->offset);

    while(comp && (n != NULL)){       //cmp = 0 (false) if data is found

        if((n->left != NULL) && comp<0){          //data is smaller than n
            printf("On the left?\n");
            n = n->left;
            comp = t->cmp(data, (char *)n - t->offset);

        }else if((n->right != NULL) && comp>0){   //data is greater than n
            printf("On the right?\n");
            n = n->right;
            comp = t->cmp(data, (char *)n - t->offset);
        }else{
            return NULL;
        }
    }

    if(n == NULL){
        return n;
    }

    return ((char *)n - t->offset);
}

//--------------------------------------------------------------------
//data is a user's struct containing a node
void avl_tree_insert(struct avl_tree *t, void *data){

    struct avl_node* node2insert = (struct avl_node *)((char *)data + t->offset);
    node2insert->height = 1;
    node2insert->left = NULL;
    node2insert->right = NULL;

    if(t->root == NULL){
        //Assign the root
        t->root = node2insert;

    }else{        
        //Start at the root of the tree
        struct avl_node *n = t->root;

        //Keeping track of the ascendants to update their height and possibly rebalance
        size_t capacity = INIT_CAP;
        struct avl_node **ascendants = (struct avl_node**)malloc(sizeof(struct avl_node*)*capacity);
        bool *ascendant_dir = (bool *)malloc(sizeof(bool)*capacity);    //keeping track of the direction in which we descend (true => right and false => left)
        ascendant_dir[0] = false;   //first ascendant always the root which is not a child
        size_t current = 0;         //index of the next entry to insert
        struct avl_node *parent;    //keeping track of the parent of n to update its children

        
        //Find empty node n where to insert data
        int comp;
        do{ 
            //compare data with the element at node n
            comp = t->cmp(data, (void *)((char *)n - t->offset));
            if(!comp){
                printf("Please insert a node with a different key !\n");
                exit(1);
            }

            ascendants[current] = n;
            parent = ascendants[current];
            current++;

            //Updating size of the arrays ascendants and ascendant_dir
            if(current >= capacity){
                capacity *= 2;
                struct avl_node** new = (struct avl_node**)malloc(sizeof(struct avl_node*)*capacity);
                bool* new_b = (bool*)malloc(sizeof(bool)*capacity);

                for(int i = 0; i < current; i++){
                    new[i] = ascendants[i];
                    new_b[i] = ascendant_dir[i];

                }

                free(ascendants);
                free(ascendant_dir);
                
                ascendants = new;
                ascendant_dir = new_b;
            }

            if(comp < 0){   //data is smaller than n => continue looking left of it
                n = n->left;
                ascendant_dir[current] = false;
                if(n == NULL){
                    parent->left = node2insert;
                    break;
                }
            }else{          //data is greater than n => continue looking right of it
                n = n->right;
                ascendant_dir[current] = true;
                if(n == NULL){
                    parent->right = node2insert;
                    break;
                }
            }     
        }while(n != NULL);

        
        //Going up in the tree to update height and rebalance 
        for(int i = 1; i <= current; i++){
            update_height(ascendants[current - i]);

            struct avl_node* new_root = avl_tree_rebalance(ascendants[current - i]);

            if((i != current) && ascendant_dir[current - i]){
                ascendants[current - i - 1]->right = new_root;
            }else if((i != current) && !ascendant_dir[current - i]){
                ascendants[current - i - 1]->left = new_root;
            }else if(i == current){
                t->root = new_root;
            }
        }

        free(ascendants);
        free(ascendant_dir);
    }
}

//--------------------------------------------------------------------
/*>0 : right heavier & <0 : left heavier*/
static int get_balance(struct avl_node* n ){
    if(!n)
        return 0;

    int left = n->left ? n->left->height : 0;
    int right = n->right ? n->right->height : 0;
    return  right - left;
}

//--------------------------------------------------------------------
static void update_height(struct avl_node *n){
    int left_h = n->left ? n->left->height : 0;
    int right_h = n->right ? n->right->height : 0;
    
    int added_h = left_h > right_h ? left_h : right_h;
    n->height = 1 + added_h;
}

//--------------------------------------------------------------------
//dir : 0 left & 1 right
static struct avl_node *rotate_tree(struct avl_node *root, bool dir){
    if(!root)
        return NULL;
    
    struct avl_node *new_root;

    if (dir == 1){
        new_root = root->left;
        if(!new_root)
            return NULL;

        root->left = new_root->right;        
        new_root->right = root;
        
    }else{
        new_root = root->right;
        if(!new_root)
            return NULL;

        root->right = new_root->left;
        new_root->left = root;
    }
    update_height(root);
    update_height(new_root);

    return new_root;  
}

//--------------------------------------------------------------------
static struct avl_node *avl_tree_rebalance(struct avl_node* root){
    int bal = get_balance(root);
    if(abs(bal)<= 1){
        return root;
    }

    //Direction of imbalance (heavier side) : true right & false left
    bool dir = bal > 0;

    //Balance of heavy child
    int bal_child = dir ? get_balance(root->right) : get_balance(root->left);

    //Direction of imbalance (heavier side) of heavy child : true right & false left
    bool dir_child = bal_child > 0;

    if(bal_child && (dir != dir_child)){
        if(dir){    //right heavier
            //direction of imbalance != rotating direction
            root->right = rotate_tree(root->right, !dir_child);
        }else{      //left heavier
            //direction of imbalance != rotating direction
            root->left = rotate_tree(root->left, !dir_child);
        }
    }

    //direction of imbalance != rotating direction
    root = rotate_tree(root, !dir);

    return root;
}