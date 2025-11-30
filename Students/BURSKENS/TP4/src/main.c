#include <avl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

int cmp(const void* add_1, const void* add_2) {
        return strcmp((const char *)add_1, (const char *)add_2);
}

int main(int argc, char* argv[]){
    char* filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    
    int num_of_strings = 0;
    char line[256];
    fgets(line, sizeof(line), fp);
    sscanf(line,"%d",&num_of_strings);
    printf("Number of strings: %d\n", num_of_strings);
    struct user_data* data = malloc(sizeof(struct user_data)*num_of_strings);
    for(int i = 0; i < num_of_strings; i++){
        //data[i].node = malloc(sizeof(struct avl_node));
        data[i].node.left = NULL;
        data[i].node.right = NULL;
        data[i].node.height = -1;
        fgets(line, sizeof(line), fp);
        sscanf(line,"%s",data[i].info);
        //printf("Read string: %s\n", data[i].info);
        //printf("Stored string: %s\n", data[i].info);
    }
    struct avl_tree* tree = malloc(sizeof(struct avl_tree));
    avl_tree_initialize(tree, cmp, offsetof(struct user_data, node));
    for(int i = 0; i < num_of_strings; i++){
        avl_tree_insert(tree, &data[i]);
        //printf("Inserted string nmbr: %d\n",i);
        /*void* found = avl_tree_find(tree, &data[i]);
        if(found != NULL){
            //printf("Found: %s\n", (char*)found);
        }
        else{
            //printf("Not Found: %s\n", (char*)found);
        }*/
    }
    //void* found1 = avl_tree_find(tree, &data[0]);
    //printf("Found1: %s\n", (char*)found1);
    for(int i = 0; i < num_of_strings; i++){
        void* found = avl_tree_find(tree, &data[i]);
        if(found != NULL){
            //printf("Found: %s\n", (char*)found);
        }
        else{
            //printf("Not Found: %s\n", (char*)found);
        }
    }
    //printf("\n");
    struct avl_node* (*tree_nodes) = malloc(sizeof(struct avl_node)*2^(tree->root->height));
    struct avl_node* current = tree->root;
    int index = 1;
    int iter = 1;
    tree_nodes[0] = current;
    while(index < (int)pow(2,tree->root->height)-1+1e-9){
        if(current != NULL){
            tree_nodes[index] = current->left;
        }
        else{
            tree_nodes[index] = NULL;
        }
        index++;
        if(current != NULL){
            tree_nodes[index] = current->right;
        }
        else{
            tree_nodes[index] = NULL;
        }
        index++;
        current = tree_nodes[iter];
        iter++;
    }
    printf("Treeheight: %d\n", tree->root->height);
    for(int j = 0; j < tree->root->height; j++){
        int start = (int)pow(2,j) -1 + 1e-9;
        int end = (int)pow(2,j+1) -1 + 1e-9;
        for(int k = start; k < end; k++){
            //printf("J: %d K: %d ", j, k);
            if(tree_nodes[k] != NULL){
                void* print_data_ptr = (void*)((char*)tree_nodes[k] - tree->offset);
                struct user_data* print_data = print_data_ptr;
                printf("%8s ", print_data->info);
                //printf("Succcess ");
            }
            else{
                printf("%8s ", "NULL");
            }
        }
        printf("\n");
    }
    /*rebalance_tree_post_insert(tree,&data[num_of_strings-1]);
    printf("Treeheight: %d\n", tree->root->height);
    for(int j = 0; j < tree->root->height; j++){
        int start = (int)pow(2,j) -1 + 1e-9;
        int end = (int)pow(2,j+1) -1 + 1e-9;
        for(int k = start; k < end; k++){
            //printf("J: %d K: %d ", j, k);
            if(tree_nodes[k] != NULL){
                void* print_data_ptr = (void*)((char*)tree_nodes[k] - tree->offset);
                struct user_data* print_data = print_data_ptr;
                printf("%s ", print_data->info);
                //printf("Succcess ");
            }
            else{
                printf("NULL ");
            }
        }
        printf("BREAK\n");
    }*/
    fclose(fp);
    free(data);
    free(tree);
    return 0;
}


