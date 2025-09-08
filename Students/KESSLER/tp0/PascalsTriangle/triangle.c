#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Please provide exactly 1 argument.");
        return 1;
    }

    triangle(argv[1]);
    return 0;
}

void triangle(int numberOfLines) {

    int one = 1;
    int two = 1;

    for (int lineIndex = 0; lineIndex < numberOfLines; lineIndex++) {
        printf(1);

        for (int columnIndex = 1, columnIndex < lineIndex; columnIndex++) {

        }

        printf(1);
    }
}