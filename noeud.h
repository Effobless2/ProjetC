#include <stdlib.h>
#include <stdio.h>

typedef struct noeud* nd;

typedef struct noeud{
	void *val;
	int occ;
	nd gauche;
	nd droite;
};

void ajout(nd *src, void *val);
void supprimer(nd src, void *val);
nd creer_noeud(void *val);
nd *rechercher(nd *racine, void *val);
void detruire(nd* src);
void afficher(nd n);
