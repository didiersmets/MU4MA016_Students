#include <stdio.h>
#include <stdlib.h>

void printPascalTriangle(int n);
int calculatePascalValue(int line, int position);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide exactly 1 positive integer.\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    printPascalTriangle(n);
    return 0;
}

// Calculates the value at a specific position in Pascal's Triangle
int calculatePascalValue(int line, int position) {
    if (position == 0 || position == line)
        return 1;
    
    return calculatePascalValue(line - 1, position - 1) + calculatePascalValue(line - 1, position);
}

// Prints Pascal's Triangle with n lines
void printPascalTriangle(int n) {
    for (int line = 0; line < n; line++) {
        // Add indentation
        for (int space = 0; space < n - line - 1; space++) {
            printf("  ");
        }

        // Calculate and print the values in this line
        for (int position = 0; position <= line; position++) {
            printf("%4d", calculatePascalValue(line, position));
        }
        printf("\n");
    }
}