#include <stdio.h>
#include <stdlib.h>

typedef struct noeud_liste* nd_liste;

typedef struct noeud_liste{
	char val;
	int occurence;

	nd_liste suivant;
};

nd_liste creer_noeud_liste(char val, int occurence);
void ajouter_noeud_liste(nd_liste n, char val, int occurence);
void supprimer_noeud_liste(nd_liste *n, char val);
void afficher_noeud_liste(nd_liste n);
void detruire_noeud_liste(nd_liste *n);