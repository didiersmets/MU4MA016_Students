#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/avl_tree.h"
//#include "../include/priority_queue.h"

#define TO_STRING(val)  #val

struct user_data{
    char *val;
    struct avl_node node;
};

void initialse_user_data(struct user_data* x, char* val){
    x->val = val;
}

void insert_userdata(struct avl_tree *t, struct user_data* x, char* name){
    printf("\nInserting %s------------------------\n", name);
    avl_tree_insert(t, x);
}

void finding_userdata(struct avl_tree *t, struct user_data* x, char* name){
    printf("\nFinding %s------------------------\n", name);
    
    struct user_data *found;
    found = avl_tree_find(t, x);
    if(found != NULL){
        printf("Found the node with value \"%s\" at height %d\n", found->val, (found->node).height);
    }else{
        printf("Didn't find the node :(\n");
    }
}

int compare(const void* data, const void* x){
    return strcmp(((struct user_data*)data)->val, ((struct user_data*)x)->val);
}

int main(int argc, char **argv){

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
    
    printf("\n\n====================================================================\n");
    
    finding_userdata(&t, &x1, TO_STRING(x1));
    finding_userdata(&t, &x2, TO_STRING(x2));
    finding_userdata(&t, &x3, TO_STRING(x3));
    finding_userdata(&t, &x4, TO_STRING(x4));
    finding_userdata(&t, &x5, TO_STRING(x5));
    finding_userdata(&t, &x6, TO_STRING(x6));
    finding_userdata(&t, &x7, TO_STRING(x7));

    return 0;
}