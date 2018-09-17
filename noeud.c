#include "noeud.h"

void afficher(nd n){
	printf("Valeur : %c\n", n->val);
	if (n->droite != NULL){
		afficher(n->droite);
	}
	if (n->gauche != NULL){
		afficher(n->gauche);
	}
}
void ajout(nd *src, char val){
	if((*src) != NULL){
		if( (*src)->val == val ){
			(*src)->occ ++;
		} else{
			if( val < (*src)->val ){
				printf("Ajout gauche \n");
				ajout( &(*src)->gauche, val);
			} else{
				printf("Ajout gauche \n");
				ajout( &(*src)->droite, val);
			}
		}
	} else{
		printf("null \n");
		(*src) = creer_noeud(val);

	}
}

void supprimer(nd src, char val){
	nd *recherche = rechercher(src, val);
	if ( (*recherche)->droite == NULL && (*recherche)->gauche == NULL){
		
	}
	if ((*recherche)->droite == NULL && (*recherche)->gauche != NULL){}

	
	if ((*recherche)->droite != NULL && (*recherche)->gauche == NULL){
		
	}

	if(recherche != NULL){
		detruire(recherche);
	}

}

nd creer_noeud(char val){
	nd res = (nd) malloc(sizeof(struct noeud));
	
	res->val = val;
	res->droite = NULL;
	res->gauche = NULL;
	res->occ = 1;
	
	return res;
}

nd* rechercher(nd *racine, char val){
	if ((*racine) == NULL){
		return NULL;
	}
	if ((*racine)->val == val){
		return racine;
	}
	if ((*racine)->val < val){
		return (*racine)->droite == NULL ? NULL : rechercher(&(*racine)->droite, val);
	}
	return (*racine)->gauche == NULL ? NULL : rechercher(&(*racine)->gauche, val);
}


void detruire(nd *rac){
	if((*rac) != NULL){
		if( (*rac)->gauche != NULL )
			detruire(&(*rac)->gauche );
		if( (*rac)->droite != NULL )
			detruire(&(*rac)->droite );
		free((*rac));
	}
	free(rac);
}
