 #include <stdio.h>

int compte_ligne ()
{
	int nl=0;
	while((int c = getchar()) != EOF){
		if (c == '\n'){
			nl++;
		}
	}
	return nl;
}

int *lignes()
{

