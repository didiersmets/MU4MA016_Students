#include <stdio.h>

int main() {
	char prenom[100];
	int age;

	printf("Quel est ton prenom ?");
	scanf("%s", prenom);

	printf("Quel est ton age ?");
	scanf("%d", &age);

	printf("Bonjour %s, tu as %d ans \n", prenom, age);

	return 0;
}
