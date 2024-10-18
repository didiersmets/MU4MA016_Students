#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	FILE *text = fopen(argv[1],"r");
	char ch = fgetc(text);

	while (ch != EOF){
		printf("%c", ch);
		ch = fgetc(text);
	}
	fclose(text);

	return 0;
}