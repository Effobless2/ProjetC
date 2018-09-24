#include "liste.h"

lst creer_liste(){
	lst liste = malloc(sizeof(struct liste));
	(*liste).taille = 0;
	(*liste).premier = NULL;

	return liste;
}

void ajouter_liste(lst l, char val, int occurence){
	if( (*l).taille == 0 ){
		nd_liste n = creer_noeud_liste(val, occurence);
		(*l).premier = n;
	}else{
		ajouter_noeud_liste( (*l).premier, val, occurence);
	}
	(*l).taille ++;
}

void supprimer_liste(lst l, char val){
	supprimer_noeud_liste( &((*l).premier), val);
	(*l).taille --;
}

void afficher_liste(lst l){
	printf("Taille de la liste = %d\n", (*l).taille);
	afficher_noeud_liste( (*l).premier );
}

void detruire_liste(lst *l){
	if( (*(*l)).taille != 0){
		detruire_noeud_liste( &((*(*l)).premier) );
	}
	free(*l);
}