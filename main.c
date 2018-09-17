#include "noeud.h"

int main(void){
	nd test = creer_noeud('a');
	ajout(&test, 'b');
	ajout(&test, 'c');
	nd *recherche = rechercher(&test, 'b');
	//supprimer(test, 'b');
	printf("valeur b = %c\n", (*recherche)->val);
	afficher(test);
	supprimer(test, 'b');
	afficher(test);
	detruire(&test);
	
	
	return EXIT_SUCCESS;
}
