#include <stdio.h>
#include <string.h>
int main(void)
{

	char nom[5];

	printf("Donne ton prénom:\n");
	scanf("%s", nom);

	if (strcmp(nom, "Mira") == 0 )
		printf("Jvais te péter le fiak\n");

	else if (strcmp(nom, "Alex") == 0)
		printf("T'es un beau gosse toi je reconnais\n");

	else if (strcmp(nom, "Kani") == 0)
		printf("Tu es très homosexuel\n");

	else
		printf("jsp t'es qui\n");




	return 0;
	}
