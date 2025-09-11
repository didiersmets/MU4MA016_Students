#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    if (argc != 2){
        fprintf (stderr, "Usage: %s file_name\n", argv[0]);
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");

    if (f == 0){
        perror(argv[1]);
        exit(2);
    }

    char c;

    while (fscanf(f, "%c", &c) == 1){
        putc (c, stdout);
    }
    return 0;
}