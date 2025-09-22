#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) /*this is to ensure only argument, excluding name*/ {
        fprintf(stderr, "Usage: %s n\n", argv[0]); // tells user how to use the program
        return 1; 
    }

    int n = atoi(argv[1]); // convert argument to integer, needed for n > 9.
    int prev[n], curr[n]; // creating the arrays

    for (int i = 0; i < n; i++) {// outer
        for (int j = 0; j <= i; j++) {// inner
            if (j == 0 || j == i) {
                curr[j] = 1; // left and rightmost values
            } else {
                curr[j] = prev[j-1] + prev[j]; // Pascals relation
            }
            printf("%d ", curr[j]); 
        } // inner loop is printed and ends
        printf("\n"); // new line

        // copy curr into prev
        for (int j = 0; j <= i; j++) {
            prev[j] = curr[j];
        }
    }

    return 0;
}
