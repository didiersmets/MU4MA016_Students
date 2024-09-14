

#include<stdio.h>
#include<stdlib.h>


int main(int argc, char** argv) {

  int LINES = 10000;
  char myString[LINES];
  FILE *fptr;

  if ((fptr = fopen(argv[1], "r")) == NULL ){
    printf("File %s cannot open \n", argv[1]);
    return EXIT_FAILURE;
  }

  while(fgets(myString, LINES, fptr)) {
    printf("%s", myString);
  }



  fclose(fptr);



  return EXIT_SUCCESS;
}
