//--------------------------------------------------------------------
//Projet de C : Codage de Huffman
//DEBOFFLE Maxime
//IDOUX Etienne
//--------------------------------------------------------------------



#include "../h/utils.h"



//-----------------------------------------------------------
//Paramètres : Nom du fichier à lire
//Retourne : Contenu du fichier sous forme de tableau de char
//			 NULL si le fichier n'existe pas
//Utilité : Gère la lecture d'un fichier grâce à son nom.
//-----------------------------------------------------------
char *readFile(char *name){
    FILE *fp;
	int taille = 0;
	char* texte;

	// Ouvre un FILE en mode lecture. La condition IF indique si le fichier est bien ouvert
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



//-------------------------------------------------------------------------------------------
//Paramètres : Tableau de char de 0 et de 1 à convertir
//Retourne : Tableau de char de la traduction en code ASCII du paramètre
//Utilité : Permet de modifier un préfixe du codage de huffman en code ASCII par paquet de 8.
// 			On récupère 6 char pour écrire le caractère ASCII et on ajoute le préfixe '01'
//			pour avoir des valeurs présentes entre 64 et 127.
//-------------------------------------------------------------------------------------------
char* stringBinary_to_stringASCII(char *src){
	char* rt = malloc(sizeof(char)); // Tableau de char à retourner
	rt[0] = '\0';
	int t_rt = 1; // Taille du tableau de char à retourner
	char acompr[8] = ""; // Tableau de char représentant les 0 et 1 à compresser par 8
	unsigned int icompr = 0; // string binaire en dec
	int compt = 2; // compteur de bits
	int taille = strlen(src);

	// On récupère un lot de 8 char que l'on va transformer en base 2 dans un unsigned int avec strtol()
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

	// Condition si la taille de l'entrée n'est pas un multiple de 8, on ajoute des 0 à la fin
	// Identique à la boucle FOR précédente
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



//---------------------------------------------------------------------------------------
//Paramètres : Tableau de char ASCII
//Retourne : Tableau de char de la traduction en binaire du paramètre
//Utilité : Permet de modifier un tableau de char en ASCII vers du binaire pour retrouver
//			les préfixes de l'arbre d'Huffman.
//---------------------------------------------------------------------------------------
char* stringASCII_to_stringBinary(char *src){
	char *rt = malloc(sizeof(char)); //Tableau de char à retourner
	rt[0] = '\0';
	int t_rt = 1; //Taille du tableau de char à retourner
	unsigned int codeASCII = 0; // Le décimal récupéré depuis un caractère de la chaîne avec un cast 
	char *codeASCII_binaire = malloc(sizeof(char)*9);

	int taille = strlen(src); // Taille de l'entrée

	// On recupère l'entier non-signé représentant le caractère ASCII
	// On le convertit en binaire et on l'ajoute au tableau de char à retourner
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



//----------------------------------------------------------------------------------------
//Paramètres :
//		-Entier non-signé représentant le code ASCII
//		-Tableau de char où l'on va ajouter le code binaire du 1er paramètre
//Retourne : void
//Utilité : Trouve le code binaire d'un entier non-signé et l'ajoute à un tableau de char.
//----------------------------------------------------------------------------------------
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