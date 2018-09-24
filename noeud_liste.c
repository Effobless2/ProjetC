#include "noeud_liste.h"

nd_liste creer_noeud_liste(char val, int occurence){
	nd_liste src = malloc( sizeof(struct noeud_liste) );
	(*src).val = val;
	(*src).occurence = occurence;
	(*src).suivant = NULL;
}

void ajouter_noeud_liste(nd_liste n, char val, int occurence){
	if(n != NULL){
		if( (*n).suivant != NULL)
			ajouter_noeud_liste( (*n).suivant, val, occurence);
		else
			(*n).suivant = creer_noeud_liste(val, occurence);
	}
}

void supprimer_noeud_liste(nd_liste *n, char val){
	nd_liste temp = *n;
	nd_liste prev;

	if( temp != NULL && (*temp).val == val ){
		*n = (*temp).suivant;
		free(temp);
		return;
	}

	while( temp != NULL && (*temp).val != val ){
		prev = temp;
		temp = (*temp).suivant;
	}

	if( temp != NULL ){
		(*prev).suivant = (*temp).suivant;
		free(temp);
	}

}

void afficher_noeud_liste(nd_liste n){
	if( (*n).suivant != NULL ){
		printf("%c | %d\n", (*n).val, (*n).occurence);
		afficher_noeud_liste( (*n).suivant );
	}else{
		printf("%c | %d\n", (*n).val, (*n).occurence);
	}
}

void detruire_noeud_liste(nd_liste *n){
	if( (*n) != NULL ){
		if( (*n)->suivant != NULL){
			detruire_noeud_liste( &((*n)->suivant) ) ;
		}
		free(*n);
		(*n) = NULL;
	}
}