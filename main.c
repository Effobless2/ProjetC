#include "noeud.h"

int main(void){
	nd test = creer_noeud('p');
	//printf("Size of test %d\n", sizeof(nd));
	//printf("Size of *test %d\n", sizeof(struct noeud));
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

	
	
	return EXIT_SUCCESS;
}
