#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) 
{

    FILE *file = fopen(argv[1], "r");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
    return 0;
}
