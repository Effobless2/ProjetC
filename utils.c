#include "utils.h"


char* supprimer_duplication(char *str, int taille){
	char *rt = malloc(taille+1 * sizeof(char)); // Tableau de char représentant str sans duplication
	char *utiliser = malloc(taille * sizeof(char)); // Tableau de char représentant les symboles déjà visités
	int indice = 0; // Indice pour se déplacer dans les chaînes

	for(int i=0; str[i] != '\0'; i++){ 
		if( strchr(utiliser, str[i]) == NULL ){ // Si le symbole de str[i] n'est pas présent dans la chaîne utiliser
			utiliser[indice] = str[i]; // On ajoute le symbole dans la chaîne utiliser
			rt[indice] = str[i]; // On ajoute le symbole dans la chaîne à retourner
			indice ++; // On incrémente l'indice pour se déplacer dans la chaîne à retourner
		}
	}

	rt[indice+1] = '\0'; // On marque la fin de la chaîne à retourner
	free(utiliser);
	return rt;
}


nd* liste_huffman(char *str){

	int taille = strlen(str); // Taille de la chaîne source
	nd *rt = malloc( taille * sizeof(struct noeud)); // Tableau de noeud

	// Calcul des frequences de chaque symbole de la liste
	char *str_unique = supprimer_duplication(str, taille); // On récupère la chaîne source sans duplication
	int *frequences = malloc( taille * sizeof(int) ); // Tableau contenant la fréquence de chaque symbole

	for(int i=0; str_unique[i] != '\0'; i++){ // Parcours de la chaîne source sans duplication 
		for(int j=0; str[j] != '\0'; j++){ // Parcours de la chaîne source
			if(str_unique[i] == str[j]){ // Si le symbole de la chaîne source et celui de la chaîne source sans duplication sont identiques
				frequences[i] ++; // On augmente la fréquence de ce symbole
			}
		}

		rt[i] = creer_noeud( str_unique[i], frequences[i] ); // Création d'un arbre minimaliste avec le symbole et sa fréquence associée dans le tableau à retourner
	}

	free(str_unique);
	free(frequences);

	return rt;

}