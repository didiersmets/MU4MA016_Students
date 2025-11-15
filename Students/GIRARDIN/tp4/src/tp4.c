#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/avl_tree.h"
#include "../include/priority_queue.h"

#define TO_STRING(val)  #val

struct user_data{
    char *val;
    struct avl_node node;
};

void initialse_user_data(struct user_data* x, char* val){
    x->val = val;
}

void insert_userdata(struct avl_tree *t, struct user_data* x, char* name){
    printf("Inserting %s...\n", name);
    avl_tree_insert(t, x);
}

void finding_userdata(struct avl_tree *t, struct user_data* x, char* name){
    printf("\nLooking for %s...\n", name);
    
    struct user_data *found;
    found = avl_tree_find(t, x);
    if(found != NULL){
        printf("Found the node %s with value \"%s\" at height %d\n", name, found->val, (found->node).height);
    }else{
        printf("Did not find the node :(\n");
    }
}

int compare(const void* data, const void* x){
    return strcmp(((struct user_data*)data)->val, ((struct user_data*)x)->val);
}

int main(int argc, char **argv){

printf("AVL TREE ====================================================================================\n");
    struct user_data x1;
    initialse_user_data(&x1, "0");

    struct user_data x2;
    initialse_user_data(&x2, "1");

    struct user_data x3;
    initialse_user_data(&x3, "2");

    struct user_data x4;
    initialse_user_data(&x4, "3");

    struct user_data x5;
    initialse_user_data(&x5, "4");

    struct user_data x6;
    initialse_user_data(&x6, "5");

    struct user_data x7;
    initialse_user_data(&x7, "6");

    struct avl_tree t;
    
    int offset = offsetof(struct user_data, node);
    avl_tree_initialize(&t, compare, offset);

    insert_userdata(&t, &x1, TO_STRING(x1));
    insert_userdata(&t, &x2, TO_STRING(x2));
    insert_userdata(&t, &x3, TO_STRING(x3));
    insert_userdata(&t, &x4, TO_STRING(x4));
    insert_userdata(&t, &x5, TO_STRING(x5));
    insert_userdata(&t, &x6, TO_STRING(x6));
    insert_userdata(&t, &x7, TO_STRING(x7));
    
    finding_userdata(&t, &x1, TO_STRING(x1));
    finding_userdata(&t, &x2, TO_STRING(x2));
    finding_userdata(&t, &x3, TO_STRING(x3));
    finding_userdata(&t, &x4, TO_STRING(x4));
    finding_userdata(&t, &x5, TO_STRING(x5));
    finding_userdata(&t, &x6, TO_STRING(x6));
    finding_userdata(&t, &x7, TO_STRING(x7));

printf("\n\nPRIORITY QUEUE ==============================================================================\n");
    struct priority_queue q;

    int capacity = 20;
    int max_id = 20;
    
    priority_queue_init(&q, capacity , max_id);

    float vals[] = {18,11,6,7,6,3,4,5,1,2,4,1,10};
    int size = 13;
    
    for(int i = 0; i < size; i++){
        priority_queue_push(&q, i, vals[i]);
    }

    priority_queue_print(&q);

    printf("Poping a node...\n");
    struct priority_data pop = priority_queue_pop(&q);
    printf("\nPop.id : %d and pop.val : %.2f\n", pop.id, pop.val);
    
    printf("Updating the value of a node...\n");
    float new_val = 0.4;
    priority_queue_update(&q, 10, new_val);
    
    printf("Poping a node...\n");
    pop = priority_queue_pop(&q);
    printf("Pop.id : %d and pop.val : %.2f\n", pop.id, pop.val);

    priority_queue_print(&q);
    
    priority_queue_destroy(&q);
    return 0;
}