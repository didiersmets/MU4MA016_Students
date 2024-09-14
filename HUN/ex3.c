
#include<stdio.h>
#include<stdlib.h>


int main(int argc, char** argv) {
  int i, j, coef;
  int n = atoi(argv[1]);

  for (i = 0; i < n; i++) {
    for (j = 0; j <= i; j++) {
      if (j == 0 || i == 0) coef = 1;
      else coef = coef * (i - j + 1) / j;
      printf("%d ", coef);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
