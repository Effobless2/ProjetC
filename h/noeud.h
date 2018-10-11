#include <stdio.h>

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
char *GetSavedStringForTree(nd tree, char *prefixe);
void CreateTreeFromString(nd * racine, char *prefixed);