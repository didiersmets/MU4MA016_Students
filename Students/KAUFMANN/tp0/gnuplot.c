#include <stdio.h>
#include <math.h>

int main() {
    FILE *gp = popen("gnuplot -persistent", "w");

    fprintf(gp, "plot '-' with lines\n");

    for (float x = -20; x <= 20; x += 0.1) {
        float y = (x == 0) ? 1 : sinf(x)/x;
        fprintf(gp, "%f %f\n", x, y);
    }

    fprintf(gp, "e\n");
    pclose(gp);

    return 0;
}