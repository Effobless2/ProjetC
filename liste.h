#include <stdio.h>
#include <stdlib.h>
#include "noeud_liste.h"

typedef struct liste *lst;

typedef struct liste{
	int taille;
	nd_liste premier;
};

lst creer_liste();
void ajouter_liste(lst l, char val, int occurence);
void supprimer_liste(lst l, char val);
void afficher_liste(lst l);
void detruire_liste(lst *l);