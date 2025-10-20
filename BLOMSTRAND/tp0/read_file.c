#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("wrong number of arguments\n");
        return 1;
    }

    FILE *fptr = fopen(argv[1], "r");

    if (fptr == NULL)
    {
        return 1;
    }

    char ch;
    while ((ch = fgetc(fptr)) != EOF)
    {
        putchar(ch);
    }

    fclose(fptr);
    return 0;
}