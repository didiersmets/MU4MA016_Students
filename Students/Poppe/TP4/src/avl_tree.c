#include <stdlib.h>
#include <assert.h>
#include "avl_tree.h"

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset ) {
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}

void *avl_tree_find(struct avl_tree *t, const void *data) {
    void* current = t->root;
    int compare_result;
    while (current != NULL && (compare_result = t->cmp(data, current)) != 0) {
        current = ((struct avl_node*) (current+t->offset))->children[compare_result > 0];
    }
    return current;
}

#include <stdio.h>
#include <assert.h>

void avl_tree_traverse(struct avl_tree *t, void* current) {
    if(current != NULL) {
        void* left = ((struct avl_node*) (current+t->offset))->children[0];
        if(left != NULL) {
            printf("(");
            uintptr_t pcb = ((struct avl_node*) (left+t->offset))->pcb;
            avl_tree_traverse(t, left);
            printf(") ");
        }
        printf("%i", *(int*) current);
        void* right = ((struct avl_node*) (current+t->offset))->children[1];
        if(right != NULL) {
            printf(" (");
            uintptr_t pcb = ((struct avl_node*) (right+t->offset))->pcb;
            avl_tree_traverse(t, right);
            printf(")");
        }
    }
}

int avl_tree_verify_pcb(struct avl_tree *t, void* current) {
    int height = 0;
    if(current != NULL) {
        void* left = ((struct avl_node*) (current+t->offset))->children[0];
        int left_height = 0;
        if(left != NULL) {
            uintptr_t pcb = ((struct avl_node*) (left+t->offset))->pcb;
            assert((pcb & (~7)) == (uintptr_t) current);
            assert((pcb & 4) == 0);
            left_height = avl_tree_verify_pcb(t, left);
        }
        void* right = ((struct avl_node*) (current+t->offset))->children[1];
        int right_hight = 0;
        if(right != NULL) {
            uintptr_t pcb = ((struct avl_node*) (right+t->offset))->pcb;
            assert((pcb & (~7)) == (uintptr_t) current);
            assert((pcb & 4) == 4);
            right_hight = avl_tree_verify_pcb(t, right);
        }
        int wanted_balance = right_hight-left_height+1;
        uintptr_t pcb = ((struct avl_node*) (current+t->offset))->pcb;
        assert((pcb & 3) == wanted_balance);
        height = right_hight > left_height ? right_hight : left_height;
        height++;
    }
    return height;
}

void rotate(struct avl_tree *t, void **data, int direction) {
    // direction: 0=left, 1=right

    void* new_head = ((struct avl_node*) (*data+t->offset))->children[1-direction];
    void* moved = ((struct avl_node*) (new_head+t->offset))->children[direction];
    ((struct avl_node*) (*data+t->offset))->children[1-direction] = moved;

    if(moved != NULL) {
        ((struct avl_node*) (moved+t->offset))->pcb &= 7;
        ((struct avl_node*) (moved+t->offset))->pcb += (uintptr_t) *data;
        ((struct avl_node*) (moved+t->offset))->pcb ^= 4;
    }
    
    ((struct avl_node*) (new_head+t->offset))->children[direction] = *data;
    ((struct avl_node*) (new_head+t->offset))->pcb &= 3;
    ((struct avl_node*) (new_head+t->offset))->pcb += (((struct avl_node*) (*data+t->offset))->pcb & ((uintptr_t) (-1 ^ 3)));
    ((struct avl_node*) (*data+t->offset))->pcb &= 3;
    ((struct avl_node*) (*data+t->offset))->pcb += direction << 2;
    ((struct avl_node*) (*data+t->offset))->pcb += (uintptr_t) new_head;
    *data = new_head;
}

void avl_tree_insert(struct avl_tree *t, void *data) {
    // avl_tree_traverse(t, t->root);
    // printf("\n");
    avl_tree_verify_pcb(t, t->root);
    assert(((uintptr_t) data & 7) == 0); //check alignment
    struct avl_node* inserted_node = (struct avl_node*) (data+t->offset);
    inserted_node->children[0] = NULL;
    inserted_node->children[1] = NULL;

    if(t->root == NULL) {
        t->root = data;
        inserted_node->pcb = 1;
        return;
    }
    void* parent = t->root;
    int compare_result; // 0=left, 1=right
    while(((struct avl_node*) (parent+t->offset))->children[compare_result = (t->cmp(data, parent) > 0)] != NULL) {
        parent = ((struct avl_node*) (parent+t->offset))->children[compare_result];
    }
    inserted_node->pcb = ((uintptr_t) parent) | (compare_result << 2) | 1;
    ((struct avl_node*) (parent+t->offset))->children[compare_result] = data;
    uintptr_t balance_change = -1 + 2 * compare_result;
    uintptr_t* parent_pcb = &(((struct avl_node*) (parent+t->offset))->pcb);

    while((((*parent_pcb)+=balance_change) & 3) != 1) {
        if(((*parent_pcb) & 3) == 3) {
            (*parent_pcb)-=2*balance_change;
            int direction = (balance_change + 1) >> 1; // 0=left, 1=right
            void** child_addr = &(((struct avl_node*) (parent+t->offset))->children[direction]);
            void* child = ((struct avl_node*) (parent+t->offset))->children[direction];

            void* grand_parent = (void*) (*parent_pcb & ((uintptr_t) (~7)));
            void** parent_addr;
            if (grand_parent!=NULL) {
                parent_addr = &(((struct avl_node*) (grand_parent+t->offset))->children[((*parent_pcb) & 4) == 4]);
            } else {
                parent_addr = &(t->root);
            }

            if(((((struct avl_node*) (child+t->offset))->pcb) & 3) == 2*direction) {
                //single rotation
                rotate(t, parent_addr, 1 - direction);
                parent = *parent_addr;
                uintptr_t* parent_pcb = &(((struct avl_node*) (parent+t->offset))->pcb);
                // set balance of child to 0
                (((struct avl_node*) (child+t->offset))->pcb) -= balance_change;
                return;
            } else {
                //double rotation
                rotate(t, child_addr, direction);
                rotate(t, parent_addr, 1 - direction);
                parent = *parent_addr;
                // set balances
                uintptr_t* parent_pcb = &(((struct avl_node*) (parent+t->offset))->pcb);
                uintptr_t* dir_pcb = &(((struct avl_node*) (child+t->offset))->pcb);
                uintptr_t* other_pcb = &(((struct avl_node*) (((struct avl_node*) (parent+t->offset))->children[1 - direction]+t->offset))->pcb);
                *dir_pcb = ((*dir_pcb) & (~3)) + 2 - ((*parent_pcb) & 3);
                if((*parent_pcb & 3) == direction * 2) {
                    *dir_pcb += direction * 2 - 1;
                    *other_pcb += 1 - direction * 2;
                }
                *parent_pcb = ((*parent_pcb) & (~3)) + 1;
                return;
            }
        }
        balance_change = -1 + ((*parent_pcb & 4) >> 1);
        parent = (void*) (*parent_pcb & ((uintptr_t) (~7))); //clear last 3 bits
        if(parent == NULL) {
            return;
        }
        parent_pcb = &(((struct avl_node*) (parent+t->offset))->pcb);
    }
}