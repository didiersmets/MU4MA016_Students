#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");  // open file in read mode
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];  // buffer to store each line
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  // print the line
    }

    fclose(file);  // close the file
    return 0;
}
