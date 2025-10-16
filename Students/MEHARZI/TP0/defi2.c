#include <stdio.h>
int main() {
	int age;
	char prenom[100];

	printf("Quel est ton prenom ?");
	scanf("%s", prenom);

	printf("Quel est ton age ?");
	scanf("%d", &age);

	if (age >= 18)
		printf("Bonjour %s ! Tu as %d ans, tu es donc majeur \n", prenom, age);
	else
		printf("Bonjour %s ! Tu as %d ans, tu es donc mineur \n", prenom, age);

	return 0;
}
