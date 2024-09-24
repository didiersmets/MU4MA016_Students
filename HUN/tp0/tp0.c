
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


void pascal(int n);
void read_file(char* f);
void genData(int n);
void plotData();

int main(int argc, char **argv) {

  if(argc < 2){
    printf("Usage:  <command> [argument] ... \n");
    printf("        pascal <n>       \n");
    printf("        read_file  <filename>       \n");
    printf("        genData  <n>       \n");
    printf("        plotData  <n>       \n");
    return 0;
  };

  char *command = argv[1];

  if(strcmp(command, "pascal") == 0){
    int n = (argc==2)? 5: atoi(argv[2]);
    pascal(n);
  }
  else if (strcmp(command, "read_file")==0){
    if (argc==2){
      fprintf(stdout, "Usage: read_file `filename`\n");
      exit(0);
    }
    read_file(argv[2]);
  }
  else if (strcmp(command, "genData")==0){
    if (argc==2){
      fprintf(stdout, "Usage: genData `numbers of points`\n");
      exit(0);
    }
    genData(atoi(argv[2]));
  }
  else if (strcmp(command, "plotData")==0){
    plotData();
  }


  return 0;
}


/* ================================================== */

void pascal(int n) {
  int i, j, coef;
  for (i = 0; i < n; i++) {
    for (j = 0; j <= i; j++) {
      if (j == 0 || i == 0) coef = 1;
      else coef = coef * (i - j + 1) / j;
      printf("%d ", coef);
    }
    printf("\n");
  }
}


/* ================================================== */

void read_file(char *f) {
  int LINES = 10000;
  char text[LINES];
  FILE *fp;

  if ((fp = fopen(f, "r")) == NULL ){
    fprintf(stderr, "No such file `%s` exist.\n", f);
    exit(EXIT_FAILURE);
  }

  while(fgets(text, LINES, fp)) {
    printf("%s", text);
  }

  fclose(fp);
}

/* ================================================== */

void genData(int n) {
  int j;
  float xmin = -6 * M_PI, xmax =  6 * M_PI;
  float dx   = (xmax-xmin)/(n-1);
  float x, y;
  FILE *fp;

  fp = fopen("plotted.dat", "w+");
  for(j=0; j<n; j++){
    x = xmin + j*dx;
    y = sin(x)/x;
    fprintf(fp, "%f\t%f\n", x, y);
  }
  fclose(fp);
  printf("Data is written to file `plotted.dat`.\n");
}

void plotData(){
  system("gnuplot -p -e 'plot \"plotted.dat\" with lines'");
}
