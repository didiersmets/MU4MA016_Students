#include <stdio.h>

int readfile(char *filename){
	FILE *fp = fopen(filename, "r");

	if (fp == NULL)
	{
		printf("Error: could not open file %s \n", filename);
		return 1;
	}

	const unsigned MAX_LENGTH = 256;
	char buffer[MAX_LENGTH];

	while (fgets(buffer, MAX_LENGTH, fp)){
		printf("%s", buffer);
	}

	fclose(fp);
	return 0;
}


int main() { 
	char text[256]; 
	printf("Enter the name of the file you wish to read: ");
	scanf("%255s", text);

	if (readfile(text) != 0) {
		printf("Failed to read file. \n");
	}

	return 0;
}