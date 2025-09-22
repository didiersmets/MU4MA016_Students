#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    char *filename = "sin_values.txt";
    FILE *file = fopen(filename, "w");
    if (n <= 1)
    {
        printf("N must be greater than 1");
        return 1;
    }
    double x_min = -12 * M_PI;
    double x_max = 12 * M_PI;
    double step_size = (x_max - x_min) / (n - 1);
    double y_value = 0;
    for (double x_value = x_min; x_value <= x_max; x_value += step_size)
    {
        if (x_value == 0)
        {
            y_value = 0;
        }
        else
        {
            y_value = sin(x_value) / x_value;
        }

        fprintf(file, "%f\t%f\n", x_value, y_value);
    }

    return 0;
}