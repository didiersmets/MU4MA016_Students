#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    if (argc !=2){
        fprintf(stderr, "use: %s <filename>\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        
        perror("error");
        return 1;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        
        printf("%s", buffer);
    }

    
    fclose(fp);

    
    return 0;

}