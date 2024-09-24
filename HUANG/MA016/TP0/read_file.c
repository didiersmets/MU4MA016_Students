#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

int main(int argc,char ** argv)
{
  //open a doc in read mode
  FILE *f = fopen(argv[1], "r");
  char line[MAX_LINE_LENGTH];
  
  if (f != NULL)
  {
    while (fgets(line,MAX_LINE_LENGTH,f) )
    {
      printf("%s",line);
    }
  
  }
  else
  {
    printf("can not open");
    return 1;
  }    
  
  fclose(f);
  return EXIT_SUCCESS;
}

