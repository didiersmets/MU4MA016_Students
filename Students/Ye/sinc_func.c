#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
    if(argc !=2){
        fprintf(stderr, "Usage: %s<n>\n", argv[0]);
        fprintf(stderr, "where n is a positive integer for thr number of points. \n");
        return EXIT_FAILURE;    }

    int n = atoi(argv[1]);
    if (n <=1){
        fprintf(stderr, "Error: n must be an integer greater than 1.\n");
    }
    const double xmin = -6.0 * M_PI;
    const double xmax = 6.0*M_PI;
    const double delta_x = (xmax -xmin)/(n-1);
    FILE*fp = fopen("output_data.txt","w");
    if(!fp){
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    for (int j = 0;j<n;j++){
        double x_j = xmin + j*delta_x;
        double y_j;
        if (x_j == 0.0){
            y_j =1.0;
        }else{
            y_j = sin(x_j)/x_j;
        }
        fprintf(fp,"%.6f\t%.6f\n",x_j,y_j);
    }
    fclose(fp);
    return EXIT_FAILURE;
}




