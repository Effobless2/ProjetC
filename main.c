#include "utils.h"
#include <time.h>

int main(void){

	char str[100] = "J'adore faire des longues phrases, miam";
	printf("(%s) = %d\n", str, strlen(str));

		clock_t begin = clock();
	nd *liste = liste_huffman(str);
		clock_t end = clock();

	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("----------\nExe : %f\n----------\n", time_spent);

	for(int i=0; liste[i] != NULL; i++){
		afficher(liste[i]);
	}

	for(int i=0; liste[i] != NULL; i++){
		detruire(&liste[i]);
	}
	free(liste);
	
	return EXIT_SUCCESS;
}
