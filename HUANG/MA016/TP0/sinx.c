#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float xmin = -6*M_PI
float xmax = 6*M_PI

int sin(int argc,char **argv)
{
  int n = argv[1];
  float xj = 0;
  float yj = 0;
  float dx =( xmax - xmin)/(n - 1);

  filename= "output_sin(x)/x.txt";

  FILE *outfile = fopen(filename,'w');
  
  while(int j=0;j < n; j++)
  {
    xj = xmin + j* dt ;
    yj = sin(xj)/xj
    
  }
  
  
}
