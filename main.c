#include <stdlib.h>
#include <stdio.h>
#include "noeud.h"

int main(void){
	nd test = creer_noeud('a');
	ajout(&test, 'b');
	//nd recherche = rechercher(test, 'b');
	//supprimer(test, 'b');
	afficher(test);
	detruire(&test);
	
	
	return EXIT_SUCCESS;
}
