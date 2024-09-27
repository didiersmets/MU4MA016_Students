#include <stdio.h>
#include <stdlib.h>

void pascal_nth(int N){
  for (int line = 1; line <= N; line++) {
    // used to represent C(line, i)
    int coef = 1;
    for (int i = 1; i <= line; i++) {
      // The first value in a line
      // is always 1
      printf("%4d", coef);
      coef = coef * (line - i) / i;
    }
    printf("\n");
  }
}

int main(int argc,char ** argv)
{
  int N=atoi(argv[1]);
  pascal_nth(N);
  return EXIT_SUCCESS;
  
}
