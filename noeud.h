#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct noeud* nd;

typedef struct noeud{
	char val;
	void *occ;
	nd gauche;
	nd droite;
};

void ajout(nd *src, char val, void *occ);
void supprimer(nd src, char val);
nd creer_noeud(char val, void *occ);
nd *rechercher(nd *racine, char val);
void detruire(nd* src);
void afficher(nd n);
int nodeComparision(nd, nd);
nd fusion(nd, nd);
char* recherchePrefixe(nd src, char val);
char* compression(nd src, char *str);
nd compression_Fichier(char *name);
char* decompression(nd src, char *str);
char* decompression_Fichier(char *, nd);