#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


// question 3 Loops and formatted output (1)
int main(int argc, char *argv[]) {
    if (argc !=2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    for (int i = 0; i < n; i++) {
        int val =1;
        for (int j = 0; j <= i; j++) {
            printf("%d", val);
            val = val * (i - j) / (j + 1);
        }
        printf("\n");
    }
    return 0;
}
