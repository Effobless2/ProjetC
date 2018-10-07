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

char* stringBinary_to_stringASCII(char *src){
	char* rt = malloc(sizeof(char));
	rt[0] = '\0';
	int t_rt = 1; // taille de la chaine a retourner
	char acompr[8] = ""; // string binaire
	int icompr = 0; // string binaire en dec
	int compt = 0; // compteur de bits

	int taille = strlen(src);
	for(int i=0; i<taille; i++){
		acompr[compt] = src[i];
		compt++;
		if(compt >= 8){
			compt = 0;
			icompr = (int) strtol(acompr, NULL, 2); // transforme un string en long avec un cast int dans sa base 2
			printf("Icompr = %d | %c \n", icompr, ( (char) icompr));
			rt = realloc(rt, sizeof(char) * t_rt+1);
			rt[t_rt-1] = (char) icompr;
			rt[t_rt] = '\0';
			t_rt ++;
		}
	}

	/*if(compt < 8){
		int diff = 7 - compt;
		printf("%d\n", diff);
		for(int i=diff; i<7; diff++){
			acompr[diff] = '0';
		}
		icompr = (int) strtol(acompr, NULL, 2); // transforme un string en long avec un cast int dans sa base 2
		rt = realloc(rt, sizeof(char) * t_rt+1);
		t_rt ++;
		rt[t_rt] = (char) icompr;
	}*/

	while(compt < 8){
		acompr[compt] = '0';
		compt++;
	}
	icompr = (int) strtol(acompr, NULL, 2); // transforme un string en long avec un cast int dans sa base 2
	printf("Icompr = %d | %c \n", icompr, ( (char) icompr));
	rt = realloc(rt, sizeof(char) * t_rt+1);
	rt[t_rt] = (char) icompr;

	return rt;
}