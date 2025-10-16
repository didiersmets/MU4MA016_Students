#include <stdio.h>

int main() {
	char prenom[100];

	printf("Quel est ton prénom ?");
	scanf("%s", prenom);

	printf("Bonjour, %s ! \n", prenom);

	return 0;
}
