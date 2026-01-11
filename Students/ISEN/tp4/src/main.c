#include "../include/avl_trees.h"
#include "../include/tp4.h"

#include <stddef.h>  //for offset

//______________________avl-trees________________________________________________
struct user_data{
    //user data: strings
    struct avl_node node;
    char *val;
};

//comparison 
static int comp_function(const void *d1, const void *d2){
    struct user_data *data1 = d1;
    struct user_data *data2 = d2;
    //0 if =, <0 id str1 < str2, >0 if str1 > str2
    return strcmp(data1->val, data2->val);
}

int main(){
    //_____________________priority queue________________
    int max_id = 9;
    struct priority_queue q; 
    priority_queue_init(&q, 10);
    
    printf("\nAfter init\n");
    print_priority_queue(&q);

    
    float val[10] = {11,9,8,35,56,1,4,98,5,7};
    for (int i = 0; i < 10; i++){
        priority_queue_push(&q, i, val[i]);
    }
    printf("\nAfter push\n");
    print_priority_queue(&q);

    printf("\nTry push over capacity\n");
    //try to push one more 
    priority_queue_push(&q, 10, 15);
    print_priority_queue(&q);

    //try update
    printf("\nAfter update\n");
    priority_queue_update(&q, 5, 2);
    print_priority_queue(&q);

    //try pop
    struct priority_data p;
    for (int i = 0; i < 10; i++){
        p = priority_queue_pop(&q);
        printf("id: %d, val: %f\n", p.id, p.val);
    };
    printf("\nAfter pop");
    print_priority_queue(&q);

    //try one more pop
    priority_queue_pop(&q);


    //___________________avl_trees___________________________
    /*
    char *data[] = {
        "qwertzu",
        "asdfgh",
        "wertz", 
        "bvchds", 
        "poiuz", 
        "lkjhgf", 
        "bxvsssjipq"
    }; 

    struct avl_tree t;
    int offset = offsetof(struct user_data, node);
    avl_tree_initialize(&t, comp_function, offset);

    printf("Insertion\n");
    struct user_data userd[7];
    for (int i = 0; i < 7; i++){
        printf("\n%d ", i);
        userd[i].val = data[i];
        avl_tree_insert(&t, &userd[i]);
    }


    printf("\nSearch\n");
    char *tofind[] = {"bxvsssjipq", "poiutz", "asdfgh"};
    struct user_data find;
    for (int i = 0; i < 3; i++){
        printf("%d ", i);
        find.val = tofind[i];
        avl_tree_find(&t, &find);
        printf("\n");
    }*/
}