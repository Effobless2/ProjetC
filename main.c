#include "utils.h"


int main(void){
	/*
	nd test = creer_noeud('p', 1);
	ajout(&test, 'h');
	ajout(&test, 'j');
	ajout(&test, 'i');
	ajout(&test, 'd');
	ajout(&test, 'f');
	ajout(&test, 'e');
	ajout(&test, 't');
	nd *recherche = rechercher(&test, 't');
	printf("valeur t = %c\n", (char)(*recherche)->val);
	afficher(test);
	supprimer(test, 'h');
	afficher(test);
	detruire(&test);
	*/

	char str[10] = "chaval";
	nd *liste = liste_huffman(str);

	for(int i=0; liste[i] != NULL; i++){
		afficher(liste[i]);
	}
	
	return EXIT_SUCCESS;
}
