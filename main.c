#include "huffman.h"
#include <time.h>

void cleanBUFFER(){
	int c;
	while(((c = getchar()) != '\n') && (c != EOF));
}

void compressionne(){
	puts("Compression d'un fichier");
	printf("Entrer le nom de votre fichier :\n>>");
	char nom[100];
	scanf("%s", nom);
	cleanBUFFER();

	printf("%s\n", nom);

	nd tree = compression_Fichier(nom);
	detruire(&tree);
}


int main(int argc, char *argv[]){
	
	/*
	clock_t begin = clock();
	FONCTION A TIMER ICI
	clock_t end = clock();

	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("----------\nExe : %f\n----------\n", time_spent);*/


	/*nd tree = compression_Fichier("tests.txt");
	puts("Compression faite, tree dispo");

	char *decomp = decompression_Fichier("compression.txt", tree);

	printf("décompressé = %s\n", decomp);

	detruire(&tree);

	free(decomp);*/




	int choix; // Int representant le choix de l'utilisateur
	int choisir = 0; // Boolean pour sortir de la boucle
	int c;
	char *test;

	puts("-----CODAGE DE HUFFMAN-----");
	puts("1 - Compression de fichier");
	puts("2 - Decompression de fichier");
	puts("3 - Quitter le programme");
	while(choisir == 0){
		printf("Que souhaitez-vous faire ?\n>>");
		scanf("%d", &choix);
		cleanBUFFER();
		switch(choix){
			case 0:
				puts("[Erreur] La saisie n'est pas un entier.");
				while(((c = getchar()) != '\n') && (c != EOF))
					printf("%c\n", c);
				break;

			case 1:
				//cleanBUFFER();
				compressionne();
				break;
			case 2:
				puts("decompr");
				break;
			case 3:
				puts("Merci d'avoir utiliser le codage de Huffman");
				choisir = 1;
				break;
			default:
				printf("[Erreur] \"%d\" n'est pas une valeur valide.\n", choix);
				break;
		}
	}

	return EXIT_SUCCESS;
}
