#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noeud.h"


char* supprimer_duplication(char *str, int taille);
nd* liste_huffman(char *str);
void afficher_liste_huffman(nd *liste);
void detruire_liste_huffman(nd *liste);