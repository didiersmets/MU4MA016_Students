#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){

    FILE* file = fopen("data_fct.txt", "w+");

    int n = atoi(argv[1]);

    float x_min = -6*M_PI;
    float x_max = 6*M_PI;
    float delta_x = (x_max - x_min)/(n - 1);

    for(int j = 0; j < n; j++){

        float x = x_min + j*delta_x;
        float y = sinf(x)/x;

        fprintf(file, "%f\t%f\n", x, y);
    }

    fclose(file);

    return 0;
}