#include <stdio.h>

int main(int argc, char** argv) {
	FILE* fptr = fopen(argv[1],"r");
	
	char c;
	while ((c = fgetc(fptr)) != EOF) {
        	printf("%c", c);
   	}
	fclose(fptr);
}
