#include <stdio.h>
#include <math.h>

int main() {
	int nbsnotes;
	int note[100];

	printf("Combien de notes veux-tu entrer ?");
	scanf("%d", &nbsnotes);

	for(int i=0; i<nbsnotes; i++) {
		printf("Note %d : ", i +1);
		scanf("%d", &note[i]); }

	printf("Voici les notes : \n");
	for(int i=0; i<nbsnotes; i++) {
		printf("Note %d = %d \n", i+1, note[i]); }

	float moy;
	int sum = 0;

	for(int i=0; i<nbsnotes; i++) {
		sum += note[i]; }
	printf("Somme = %d \n", sum);

	moy = (float)sum / nbsnotes;
	printf("Moyenne = %.2f \n", moy);

	int min = note[0];
	for(int i=1; i<nbsnotes; i++) {
		if(note[i] < min) min=note[i]; }
	printf("La note la plus basse est %d \n", min);
	
	return 0;
}
