#include <stdio.h>
#include <stdlib.h>
#include <math.h> // should work
//#include <wx-3.2/wx/math.h> // but for some reason I have to add that line

// to do : cmake not working and segmentation fault
// gcc sin.c sin.exe -lm works

int main(int argc, char **argv){

    int n = atoi(argv[1]);
    if (n <= 0) return EXIT_FAILURE;
    FILE *f = fopen("texte.txt", "w");
    if (!f) return EXIT_FAILURE;
    
    double xmin = -6 * M_PI;
    double xmax = 6 * M_PI;
    double delta = (xmax - xmin)/(n-1);

    for(int j = 0; j < n; j++){
        double xj = xmin + j*delta;
        //double yj = sin(xj)/xj;
        double yj = xj == 0 ? 1 : sin(xj) / xj;
        fprintf(f, "%lf\t%lf\n", xj, yj);
    }
    
    fclose(f);
    return EXIT_FAILURE;
}