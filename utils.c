#include "utils.h"

char *readFile(char *name){
    FILE *fp;
	int taille = 0;
	char* texte;

	fp = fopen(name, "r");
	// On récupère la taille en allant à la fin du fichier 
	fseek(fp, 0, SEEK_END); // on va a la fin du fichier
	taille = ftell(fp); // cb de bits on a parcouru
	rewind(fp); // retour au début

	texte = malloc(taille+1 * sizeof(char));

	fread(texte, taille, 1, fp);
	texte[taille] = '\0';

	fclose(fp);
    return texte;
}