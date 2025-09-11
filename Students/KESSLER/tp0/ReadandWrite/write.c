#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void writeTextFile(double xMin, double xMax, double deltaX, int n);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Please provide exactly 1 argument.\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    // Define range and step size
    double xMin = -6 * M_PI;
    double xMax = 6 * M_PI;
    double deltaX = (xMax - xMin) / (n - 1);

    writeTextFile(xMin, xMax, deltaX, n);
    return 0;
}

void writeTextFile(double xMin, double xMax, double deltaX, int n) {

    // Opening file in writing mode
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }

    // Writing data to file
    for (int i = 0; i < n; i++) {
        double x = xMin + i * deltaX;
        double sinx = sin(x);
        double y = sin(x) / x;
        fprintf(file, "%lf %lf\n", x, y);
    }

    fclose(file);
}