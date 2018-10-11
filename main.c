//--------------------------------------------------------------------
//Projet de C : Codage de Huffman
//DEBOFFLE Maxime
//IDOUX Etienne
//--------------------------------------------------------------------



#include "huffman.h"
#include <time.h>



//------------------------------------------------------------------------------------
//Paramètres : None
//Retourne : void
//Utilité : Permet de nettoyer le buffer lors de la lecteur d'entrée de l'utilisateur.
//------------------------------------------------------------------------------------
void cleanBUFFER(){
	int c;
	while(((c = getchar()) != '\n') && (c != EOF));
}



//-----------------------------------------------------------------------------
//Paramètres : None
//Retourne : void
//Utilité : Gère la compression d'un fichier en utilisant le codage de Huffman.
//-----------------------------------------------------------------------------
void compressionne(){
	puts("\n\n-----Compression d'un fichier-----");
	printf("Saisissez le nom/chemin de votre fichier à compresser ainsi que le nom de l'archive où il sera stocké\n");
	printf("(Vous pouvez les séparer d'un espace ou avec un retour à la ligne)\n>>");
	char curName[100]; //Nom du fichier à compresser
	char newName[100]; //Nom du dossier où sera stocké l'arbre et le fichier compressé
	scanf("%s %s", curName, newName);
	cleanBUFFER();

	nd tree = compression_Fichier(curName, newName);
	
	// Condition si l'arbre est NULL alors le fichier n'existe pas et on sort
	if(tree == NULL){
		fprintf(stderr, "\n[Erreur] Le fichier que vous essayez de compresser n'existe pas\n");
		return EXIT_FAILURE;
	}

	detruire(&tree);
}



//-------------------------------------------------------------------------------
//Paramètres : None
//Retourne : void
//Utilité : Gère la décompression d'un fichier en utilisant le codage de Huffman.
//-------------------------------------------------------------------------------
void decompressionne(){
	puts("\n\n-----Décompression d'un fichier-----");
	printf("Saisissez le nom/chemin de votre dossier à décompresser ainsi que le nom du nouveau fichier décompressé :\n");
	printf("(Vous pouvez les séparer d'un espace ou avec un retour à la ligne)\n>>");
	char curName[100]; //Nom du fichier à décompresser
	char newName[100]; //Nom du nouveau fichier où sera stocké la décompression
	scanf("%s %s", curName, newName);
	strcat(newName, ".txt");

	// Tableau de char représentant le chemin vers l'arbre du dossier
	char *TreePath = malloc(sizeof(char) * (3 + strlen(curName) + strlen("/tree.txt")));
	TreePath[0] = '.';
	TreePath[1] = '/';
	TreePath[2] = '\0';
	strcat(TreePath, curName);
	strcat(TreePath, "/tree.txt");

	// On tente de lire le fichier, la condition IF représente le cas où le fichier n'existe pas
	char *TreeSt = readFile(TreePath);
	if(TreeSt == NULL){
		fprintf(stderr, "\n[Erreur] Le fichier que vous essayez de décompresser n'existe pas\n");
		return NULL;
	}
	free(TreePath);

	// On créer un pointeur de noeud représentant l'arbre à reconstruire
	// On utilise un token '/7' dans notre fichier pour délimiter chaque préfixe/valeur
	// On recupère chaque prefixe/valeur individuellement avec strtok
	nd tree = NULL;
	char* token;
	char *delim ="/7";

	token = strtok(TreeSt, delim);
	while(token != NULL){
		CreateTreeFromString(&tree, token);
		token = strtok(NULL, delim);

	}

	// Tableau de char représentant le chemin du fichier compressé
	char *CompPath = malloc(sizeof(char) * (3 + strlen(curName) + strlen("/compression.txt")));
	CompPath[0] = '.';
	CompPath[1] = '/';
	CompPath[2] = '\0';
	strcat(CompPath, curName);
	strcat(CompPath, "/compression.txt");

	// On décompresse le fichier et on recupère un tableau de char
	char *res = decompression_Fichier(CompPath,tree,newName);
	
	// Libération des variables allouées
	free(CompPath);
	detruire(&tree);
	free(res);
	free(TreeSt);
}



//--------------------------------------------------------------------------------
//Paramètres : None
//Retourne : int 0 ou 1 pour savoir si le programme s'est bien déroulé
//Utilité : Interface du codage d'huffman et gestion des entrées de l'utilisateur.
//--------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	int choix; // Int representant le choix de l'utilisateur
	int choisir = 0; // int utilisé comme booléen pour savoir si on sort du programme ou non

	while(choisir == 0){

		puts("-----CODAGE DE HUFFMAN-----");
		puts("1- Compression | 2- Decompression | 3- Quitter");
		printf("Entrer l'entier correspondant à l'action que vous souhaitez effectuer\n>>");
		
		scanf("%d", &choix);
		cleanBUFFER();
		switch(choix){
			case 1: // Cas de la compression
				compressionne();
				break;
			case 2: //Cas de la décompression
				decompressionne();
				break;
			case 3: // Cas pour quitter le programme
				puts("Merci d'avoir utiliser le codage de Huffman");
				choisir = 1;
				break;
			default: // Cas entrée non supportée
				fprintf(stderr, "\n[Erreur] Votre saisie n'est pas une valeur valide.\n", choix);
				break;
		}
	}

	return EXIT_SUCCESS;
}
