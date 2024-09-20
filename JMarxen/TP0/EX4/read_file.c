#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){      
        
	FILE *file_pointer;
	file_pointer = fopen(argv[1], "r");
	// Store the content of the file
	char file_content[500];
	// Read the content and print it
	while(fgets(file_content, 500, file_pointer)) {
  		printf("%s", file_content);
	}
	// Close the file
	fclose(file_pointer);

	return 0;
}
