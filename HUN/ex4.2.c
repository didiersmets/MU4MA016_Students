

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void genData(int n);

int main(int argc, char **argv){
  int n;
  if (argc < 2) {n = 500;}
  else {n = atoi(argv[1]);}

  genData(n);
  system("gnuplot -p -e 'plot \"plotted.data\" with lines'");

  return EXIT_SUCCESS;
}





void genData(int n) {
  int j;
  float xmin = -6 * M_PI, xmax =  6 * M_PI;
  float dx   = (xmax-xmin)/(n-1);
  float x, y;
  FILE *fp;

  fp = fopen("plotted.data", "w+");
  for(j=0; j<n; j++){
    x = xmin + j*dx;
    y = sin(x)/x;
    fprintf(fp, "%f\t%f\n", x, y);
  }
  fclose(fp);
}
