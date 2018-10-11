#include "utils.h"
/*
	Permet de lire le contenu d'un fichier possédant comme nom le paramètre name
*/
char *readFile(char *name){
    FILE *fp;
	int taille = 0;
	char* texte;

	fp = fopen(name, "r");
	if(fp == NULL){
		return NULL;
	}
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

/*
	Convertie une suite de caractère composée de 0 et de 1 en une suite de caractère ASCII associée
*/
char* stringBinary_to_stringASCII(char *src){
	char* rt = malloc(sizeof(char));
	rt[0] = '\0';
	int t_rt = 1; // taille de la chaine a retourner
	char acompr[8] = ""; // string binaire
	unsigned int icompr = 0; // string binaire en dec
	int compt = 2; // compteur de bits
	int taille = strlen(src);
	for(int i=0; i<taille; i++){
		acompr[compt] = src[i];
		compt++;
		if(compt > 7){
			acompr[0] = '0';
			acompr[1] = '1';
			icompr = (unsigned int) strtol(acompr, NULL, 2); // transforme un string en long avec un cast int dans sa base 2
			rt = realloc(rt, sizeof(char) * t_rt+1);
			rt[t_rt-1] = (char) icompr;
			rt[t_rt] = '\0';
			t_rt ++;
			compt = 2;
		}
	}
	if (compt > 2){
		while(compt < 7){
			acompr[compt] = '0';
			compt++;
		}
		acompr[0] = '0';
		acompr[1] = '1';
		icompr = (int) strtol(acompr, NULL, 2); // transforme un string en long avec un cast int dans sa base 2
		rt = realloc(rt, sizeof(char) * t_rt+1);
		rt[t_rt-1] = (char) icompr;
		rt[t_rt] = '\0';
		}
	

	return rt;
}

/*
	Convertie une chaine de caractère ASCII en suite binaire associée
*/
char* stringASCII_to_stringBinary(char *src){
	char *rt = malloc(sizeof(char));
	rt[0] = '\0';
	int t_rt = 1;
	unsigned int codeASCII = 0; // Le décimal récupéré depuis un caractère de la chaîne avec un cast 
	char *codeASCII_binaire = malloc(sizeof(char)*9);

	int taille = strlen(src);
	for(int i=0; i<taille; i++){
		codeASCII = (unsigned char) src[i];
		int_to_stringBinary(codeASCII, codeASCII_binaire);
		codeASCII_binaire[8] = '\0';
		rt = realloc(rt, sizeof(char) * (t_rt + 8));
		strcat(rt, codeASCII_binaire);
		t_rt +=8;
	}	

	free(codeASCII_binaire);
	return rt;
}

/*
	Convertie un entier en chaîne de caractère représentant l'entier en binaire
	mettant le résultat de cette conversion dans dst
*/
void int_to_stringBinary(unsigned char n, char* dst){

	int i=7;
	do {
   		if (n%2 == 1) {
       		dst[i] = '1';
   		} else {
       		dst[i] = '0';
   		}
   		n >>= 1;
   		i--;
	} while(i >=0);

	
	while(i>=0){
		dst[i] = '0';
		i--;
	}
}