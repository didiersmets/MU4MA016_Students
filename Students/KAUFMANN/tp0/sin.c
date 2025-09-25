#include <stdio.h>
#include <math.h>

float x_min = -6*3.14159;
float x_max = 6*3.14159;

FILE *gp = popen("gnuplot -persistent", "w");

void x_and_y(int n) {
    float x[n];
    float y[n];
    float delta_x = (x_max-x_min)/(n-1);
    for (int i = 0; i < n; i++) {
        x[i] = x_min + i*delta_x;
        y[i] = x[i] == 0 ? 1 : sinf(x[i])/x[i];
        fprintf(gp, "%f" "%f\n", x[i], y[i]);
    }
    fprintf(gp, "e\n");

    pclose(gp);
}


int main() {
    int N;
    scanf("%d", &N);
    x_and_y(N);
    return 0;
}