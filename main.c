#include "utils.h"
#include <time.h>

int main(void){

	//char str[100] = "sMfyIzYVy4TXQYVRn6mYP1djY5ZkjdujOa3vyJXIAGCEoUmt41SuEsc4zXd142uAPjYWhqAui8o6py2BRQJwgqhTn2f7fdftS0";
	char str[100] = "chossura";
	printf("(%s) = %d\n", str, strlen(str));

		clock_t begin = clock();
	nd *liste = liste_huffman(str);
		clock_t end = clock();

	double time_spent = (double) (end - begin) / 1000;
	printf("----------\nExe : %f ms\n----------\n", time_spent);

	afficher_liste_huffman(liste);
	puts("---------------------");
	int trouver = recherchePlusPetit(liste);
	printf("Plus petit trouvé à i = %d\n", trouver);
	afficher(liste[trouver]);


	for(int i=0; liste[i] != NULL; i++){
		detruire(&liste[i]);
	}
	free(liste);
	
	return EXIT_SUCCESS;
}
