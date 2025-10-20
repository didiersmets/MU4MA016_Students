#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("wrong number of arguments\n");
        return 1;
    }

    char *endptr;
    int n = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0')
    {
        printf("argument must be an integer\n");
        return 1;
    }

    if (n < 2)
    {
        printf("n must be at least 2\n");
        return 1;
    }

    FILE *fptr = fopen(argv[2], "w");
    if (fptr == NULL)
    {
        fprintf(stderr, "could not open file %s\n", argv[2]);
        return 1;
    }

    const double xmin = -6 * M_PI;
    const double xmax = 6 * M_PI;
    const double dx = (xmax - xmin) / (n - 1);

    for (int j = 0; j < n; j++)
    {
        double x = xmin + j * dx;
        double y;
        if (fabs(x) < 1e-12)
        {
            y = 1.0;
        }
        else
        {
            y = sin(x) / x;
        }
        fprintf(fptr, "%f\t%f\n", x, y);
    }

    fclose(fptr);
    return 0;
}