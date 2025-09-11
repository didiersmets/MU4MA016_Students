#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc, char* args[]) {
    if (argc != 2) {
        printf("Expected 1 argument (n)");
        return 1;
    }
    int n = atoi(args[1]);

    

    FILE* file = fopen("data.txt", "w");

    if (file == NULL) {
        printf("Could not create data.txt");
        return 1;
    }

    float x_min = -6 * M_PI;
    float x_max = 6 * M_PI;
    float step = (x_max - x_min) / (n - 1);

    for(float x = x_min; x < x_max + (step / 2); x += step) {
        float y = - sin(x) / x;
        fprintf(file, "%f\t%f\n", x, y);
    }

    return 0;
}