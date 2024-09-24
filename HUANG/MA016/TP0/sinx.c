#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void main(int argc,char **argv)
{
  int n = atoi(argv[1]);
  FILE *f;
  f = fopen("results1.txt","w+");
    
  float xmin = -6*M_PI;
  float xmax = 6*M_PI;
  float xj ;
  float yj ;
  float dx =( xmax - xmin)/n;
  
  for (int j=0;j < n; j++)
  {
    xj = xmin + j* dx ;
    if( xj == 0 )
      {
	yj = 1;
      }
    else
      {
	yj = sinf(xj) / xj;
      }
    fprintf(f,"%f %f \n",xj,yj);
    
  }
  fclose(f);

}
