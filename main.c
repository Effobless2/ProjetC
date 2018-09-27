#include "liste_nd.h"
#include <time.h>

int main(void){
	
	/*
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

	*/
	//test avec noeud de liste
	
	char *str = "J'adore l'informatique et j'adore manger";
	clock_t begin = clock();
	nd TreeTest = stringEncoding(str);
	clock_t end = clock();

	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("----------\nExe : %f\n----------\n", time_spent);
	afficher(TreeTest);
	char *testToto = recherchePrefixe(TreeTest, 'i');
	printf("Recherche de h : %s\n", testToto);
	free(testToto);

	char* compr = compression(TreeTest, str);
	printf("%s\n", compr);

	free(compr);
	detruire(&TreeTest);
	return EXIT_SUCCESS;
}
