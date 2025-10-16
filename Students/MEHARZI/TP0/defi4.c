#include <stdio.h>
int main() {
	int n;
	int i;

	printf("Définis le compte à rebours : ");
	scanf("%d", &n);

	for(i=n; i!=0; i--)
		{
		printf("%d \n", i);
		}

	printf("Décollage ! \n");

	return 0;
}
