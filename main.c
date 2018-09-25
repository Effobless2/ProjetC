#include "liste_nd.h"

int main(void){
	nd test = creer_noeud('p', 1);
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
	printf("valeur t = %c\n", (*recherche)->val);
	afficher(test);
	supprimer(test, 'h');
	afficher(test);
	detruire(&test);

	nd t1 = creer_noeud('p', 1);
	nd t2 = creer_noeud('a', 1);
	afficher(t1);
	afficher(t2);
	nd res = fusion(t1, t2);

	afficher(res);

	lt testList = create(creer_noeud('a', 1));
	addToList(testList, 'b');
	addToList(testList, 'c');
	addToList(testList, 'a');
	addToList(testList, 'c');

	afficherList(testList);

	destroyList(testList);
	
	detruire(&res);
	return EXIT_SUCCESS;
}
