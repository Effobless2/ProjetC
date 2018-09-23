#include <stdlib.h>
#include <stdio.h>

typedef struct noeud* nd;

typedef struct noeud{
	void *val;
	int occ;
	nd gauche;
	nd droite;
};

void ajout(nd *src, char val);
void supprimer(nd src, char val);
nd creer_noeud(char val);
nd *rechercher(nd *racine, char val);
void detruire(nd* src);
void afficher(nd n);
