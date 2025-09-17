#include <stdio.h>
#include <stdlib.h>  /*for the exit failure*/
#define _USE_MATH_DEFINES
#include <math.h>

int main(){
    FILE *wif;  
    wif = fopen("writeintofile.txt", "w"); /*w = writing mode*/

    int n;
    printf("How many iterations (>0)?");
    scanf("%d", &n);

    if(n <= 0){return EXIT_FAILURE;}

    float xmin = -6 * M_PI;
    float xmax = 6 * M_PI;
    float deltax = (xmax - xmin)/(n-1);

    for (int j = 0; j < n; j++){
        float xj = xmin + j * deltax;
        float yj = sin(xj)/xj;               /*missing : make sure we don't divide by 0 ?? (--> double y = x == 0 ? 1 : sin(x) / x;)*/

        fprintf(wif, "%f\t%f\n", xj,yj); /*write text into file, tab & linkebreak*/
    }

    fclose(wif); /*close the file*/

}

// exo 4.3)
/* gnuplot : plot [-6 * pi : 6 * pi] sin(x) * 1/x
or : 
plot "writeintofile.txt" 
plot "writeintofile.txt" with lines
plot "writeintofile.txt" with linespoints
*/

