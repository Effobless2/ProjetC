#include "huffman.h"
#include <time.h>

nd tree;

void cleanBUFFER(){
	int c;
	while(((c = getchar()) != '\n') && (c != EOF));
}

void compressionne(){
	puts("Compression d'un fichier");
	printf("Entrer le nom de votre fichier suivi du nouveau nom du fichier compressé:\n>>");
	char curName[100];
	char newName[100];
	scanf("%s %s", curName, newName);
	cleanBUFFER();

	tree = compression_Fichier(curName, newName);
	if(tree == NULL){
		fprintf(stderr, "[Erreur] Le fichier que vous essayez de compresser n'existe pas\n");
		return EXIT_FAILURE;
	}

	detruire(&tree);
}

void decompressionne(){
	puts("Compression d'un fichier");
	printf("Entrer le nom de votre fichier à dédcompresser suivi du nouveau nom du fichier décompressé:\n>>");
	char curName[100];
	char newName[100];
	scanf("%s %s", curName, newName);
	strcat(newName, ".txt");

	char *TreePath = malloc(sizeof(char) * (3 + strlen(curName) + strlen("/tree.txt")));
	TreePath[0] = '.';
	TreePath[1] = '/';
	TreePath[2] = '\0';
	strcat(TreePath, curName);
	strcat(TreePath, "/tree.txt");
	char *TreeSt = readFile(TreePath);
	if(TreeSt == NULL){
		fprintf(stderr, "[Erreur] Le fichier que vous essayez de décompresser n'existe pas\n");
		return NULL;
	}
	free(TreePath);

	nd tree = NULL;
	char* token;
	char *delim ="/7";

	token = strtok(TreeSt, delim);
	while(token != NULL){
		CreateTreeFromString(&tree, token);
		token = strtok(NULL, delim);

	}

	char *CompPath = malloc(sizeof(char) * (3 + strlen(curName) + strlen("/compression.txt")));
	CompPath[0] = '.';
	CompPath[1] = '/';
	CompPath[2] = '\0';
	strcat(CompPath, curName);
	strcat(CompPath, "/compression.txt");

	char *res = decompression_Fichier(CompPath,tree,newName);
	
	free(CompPath);
	detruire(&tree);
	free(res);
	free(TreeSt);
}


int main(int argc, char *argv[]){
	int choix; // Int representant le choix de l'utilisateur
	int choisir = 0; // Boolean pour sortir de la boucle
	int c;
	char *test;

	puts("-----CODAGE DE HUFFMAN-----");
	puts("Bonjour ! ");
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
				compressionne();
				break;
			case 2:
				decompressionne();
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
