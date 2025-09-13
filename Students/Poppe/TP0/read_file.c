#include <stdio.h>

const int MAX_LINE_LENGTH = 256;

int main(int argc, char* args[]) {
    if (argc != 2) {
        printf("Expected 1 argument (filename)");
        return 1;
    }

    char* filename = args[1];

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        printf("%s", line);
    }

    return 0;
}