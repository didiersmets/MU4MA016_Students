#include <stdio.h>
int main() {
	int nbnotes;
	int note[100];

	printf("Combien de notes veux-tu entrer ? ");
	scanf("%d", &nbnotes);

	printf("Entre toutes tes notes : ");

	int i;
	for (i=0; i<nbnotes; i++)
		{
		printf("Note %d : ", i + 1);
		scanf("%d", &note[i]);
		}

	printf("Voici les notes : ");
	for (i=0; i<nbnotes; i++) {
		printf("Note %d = %d \n", i + 1, note[i]);
	}

	return 0;
}
