#include "huffman.h"
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
	
	


	/*char *str = "J'aimerai manger des bonnes pâtes au curry mais le problème c'est que je dois faire mon codage de Huffman avant !!";
	clock_t begin = clock();
	nd TreeTest = stringEncoding(str);
	clock_t end = clock();

	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("----------\nExe : %f\n----------\n", time_spent);

	char* compr = compression(TreeTest, str);
	printf("%s\n", compr);

	char* decompr = decompression(TreeTest, compr);
	printf("%s\n", decompr);

	free(decompr);
	free(compr);
	detruire(&TreeTest);*/

	nd tree = compression_Fichier("tests.txt");

	char *decomp = decompression_Fichier("compression.txt", tree);

	printf("décompressé = %s", decomp);

	detruire(&tree);

	free(decomp);


	return EXIT_SUCCESS;
}
