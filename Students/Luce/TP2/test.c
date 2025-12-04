#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){

    FILE *f = fopen("valeurs","w");
    fprintf(f,"1 2\n");
    fprintf(f,"1 4\n");
    fprintf(f,"2 3\n");
    fprintf(f,"1 2\n");
    fclose(f);
    

    system(
        "gnuplot -persist -e \""
        "set xrange [0:10];"
        "set yrange [0:10];"
        "set ylabel 'y';"
        "set xlabel 'x';"
        "plot 'valeurs' using 1:2 with linespoints"

        "\""
        );
    
    
    
}