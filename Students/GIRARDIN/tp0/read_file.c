#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    FILE* file = fopen(argv[1], "r");

    int LINE = 64;
    char line[LINE];

    while (fgets(line, LINE, file) != NULL){
        printf(line);
    }

    fclose(file);

    return 0;
}