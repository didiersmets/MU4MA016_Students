#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI (3.141)

int main (int argc, char **argv)
{
    if (argc != 3){
        fprintf (stderr, "Usage: %s jumpsize filename \n", argv[0]);
        exit(1);
    }

    int n = argv[1];

    double x_min = -6*PI;
    double x_max = -x_min;

    double xj, yj;

    double dx = (x_max-x_min) / (n-1);

        FILE *f;

    f = fileopen(argv[2], "w");

    
    for (int j=0;j<n;j++){
        xj = x_min + dx*j;
        yj = sin(xj) / xj; 

        putc(xj, f);
        putc('\t', f);
        putc(yj, f);
        putc('\n', f);

    }

    fclose(f);
    return 0;
}
