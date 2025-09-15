#include <stdio.h>

int main() {
    int c;
    FILE *f = fopen("test-tp0.txt", "r");
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }
    fclose(f);
    return 0;
}