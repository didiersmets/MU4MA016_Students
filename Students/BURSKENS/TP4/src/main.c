#include <avl.h>
#include <stdlib.h>
#include <stdio.h>

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
    sscanf(line,"%d",num_of_strings);
    struct user_data* data = malloc(sizeof(struct user_data)*num_of_strings);
    for(int i = 0; i < num_of_strings; i++){
        fgets(line, sizeof(line), fp);
        sscanf(line,"%s",&data[i]->info);
    }
    struct avl_tree;
    for(int i = 0; i < num_of_strings; i++){

    }

    return 0;
}


