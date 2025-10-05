#include <stdio.h>
int main() {
	int age;

	printf("Renseigner votre age : ");
	scanf("%d", &age);

	while (age<0 || age>130)
	{
		printf("Votre age est INCORRECTE ! \n");
		printf("Renseigner votre age : ");
		scanf("%d", &age);
	}

	printf("Age enregistré : %d ans \n", age);

	return 0;
}
