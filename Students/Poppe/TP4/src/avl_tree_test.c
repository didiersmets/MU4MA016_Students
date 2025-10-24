// gcc -o avl_test src/avl_tree.c src/avl_tree_test.c -Iinclude -std=c11 -m64
// Run with wsl!

#include <stdlib.h>
#include <stddef.h> // for offsetof
#include <stdio.h>
#include <time.h>
#include "avl_tree.h"


struct user_data {
    int value;
    int id;
    char padding[7]; //random padding to test offset
    struct avl_node node;
    char padding2[5]; //random padding to test offset
};

int compare_user_data(const void* left, const void* right) {
    struct user_data* left_user_data = (struct user_data*) left;
    struct user_data* right_user_data = (struct user_data*) right;
    return left_user_data->value - right_user_data->value;
}

void test1() {
    printf("doing test 1\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {4, 2, 6, 7, 1, 5, 3};
    for(int i=0; i < 7; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test2() {
    printf("doing test 2\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    for(int i=0; i < 7; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test3() {
    printf("doing test 3\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {7, 6, 5, 4, 3, 2, 1};
    for(int i=0; i < 7; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test4() {
    printf("doing test 4\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {1, 3, 2, 4};
    for(int i=0; i < 4; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test5() {
    printf("doing test 5\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {3, 1, 2, 0};
    for(int i=0; i < 4; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test6() {
    printf("doing test 6\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {7, 6, 2, 1, 4, 5, 3};
    for(int i=0; i < 7; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test7() {
    printf("doing test 7\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {1, 2, 6, 7, 4, 3, 5};
    for(int i=0; i < 7; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test8() {
    printf("doing test 8\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {7, 6, 5, 3, 1, 4, 2};
    for(int i=0; i < 7; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test9() {
    printf("doing test 9\n");
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    struct user_data data[8];
    int values[] = {1, 2, 3, 5, 7, 4, 6};
    for(int i=0; i < 7; i++){
        data[i].id = i;
        data[i].value = values[i];
        printf("Inserting %d at step %d\n", data[i].value, i);
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

void test_final() {
    printf("doing final test\n");

    // Seed the random number generator
    srand(time(NULL));  // Use the current time as the seed

    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_user_data, offsetof(struct user_data, node));

    #define N 1000
    struct user_data data[N];
    for(int i=0; i < N; i++){
        data[i].id = i;
        data[i].value = rand() % N;
        avl_tree_insert(&tree, data + i);
    }
    printf("\n");
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test_final();
    return 0;
}