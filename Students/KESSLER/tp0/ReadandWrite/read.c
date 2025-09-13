#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Please provide exactly 1 argument.\n");
        return 1;
    }

    // Buffer
    char line[256];

    // Opening file in reading mode
    FILE *file = fopen(argv[1], "r");

    // Checking if file exists
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    // Reading file line by line and printing to console
    while (fgets(line, sizeof(line), file))
        printf("%s", line);
        
    // Closing the file
    fclose(file);
    return 0;
}