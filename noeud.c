#include "noeud.h"

void afficher(nd n)
{
	printf("Valeur : %c\n", n->val);
	if (n->droite != NULL)
	{
		afficher(n->droite);
	}
	if (n->gauche != NULL)
	{
		afficher(n->gauche);
	}
}

void ajout(nd *src, char val)
{
	if ((*src) != NULL)
	{
		if ((*src)->val == val)
		{
			(*src)->occ++;
		}
		else
		{
			if (val < (*src)->val)
			{
				printf("Ajout gauche \n");
				ajout(&(*src)->gauche, val);
			}
			else
			{
				printf("Ajout droite \n");
				ajout(&(*src)->droite, val);
			}
		}
	}
	else
	{
		printf("null \n");
		(*src) = creer_noeud(val);
	}
}

nd noeudMax(nd racine){
	if (racine != NULL){
		return (*racine).droite == NULL ? racine : noeudMax((*racine).droite);
	}
	return NULL;
}

nd noeudMin(nd racine){
	if (racine != NULL){
		return racine->gauche == NULL ? racine : noeudMin(racine->gauche);
	}
	return NULL;
}

nd getParent(nd src, char val){
	nd curP = src;
	nd curChild = curP;
	if (src == NULL){
		return NULL;
	}
	while((curChild == curP) || (curChild->val != val)){
		if ((curChild == curP) & (curChild->val == val)){
			return curP;
		}
		if (curChild->val > val){
			if (curChild->gauche != NULL){
				if( curChild != curP){
					curP = curChild;
				}
				curChild = curChild->gauche;
			}
			else{
				return NULL;
			}
		}
		else if (curChild->val < val){
			if (curChild->droite != NULL){
				if (curChild != curP){
					curP = curChild;
				}
				curChild = curChild->droite;
			}
			else {
				return NULL;
			}
		}
	}
	return curP;
}

void supprimer(nd src, char val)
{
	nd *recherche = rechercher(&src, val);
	if (recherche != NULL)
	{
		nd copyRecherche = (*recherche);

		if ((*recherche)->droite == NULL && (*recherche)->gauche == NULL)
		{
			printf("feuille\n");
		}
		else if ((*recherche)->droite == NULL && (*recherche)->gauche != NULL)
		{
			(*recherche) = (*recherche)->gauche;
			printf("Gauche only\n");
		}
		else if ((*recherche)->droite != NULL && (*recherche)->gauche == NULL)
		{
			(*recherche) = (*recherche)->droite;
			printf("Droite only\n");

		}
		else
		{
			nd remplacant = noeudMax(copyRecherche->gauche);
			if (remplacant != NULL){
				nd parent = getParent(src, remplacant->val);
				if (parent != NULL){
					parent->droite = remplacant->gauche;
					remplacant->droite = copyRecherche->droite;
					remplacant->gauche = copyRecherche->gauche;
					(*recherche) = remplacant;
				}
			}
			else{
				remplacant = noeudMin(copyRecherche->droite);
				nd parent = getParent(src, remplacant->val);
				if (parent != NULL){
					parent->gauche = remplacant->droite;
					remplacant->gauche = copyRecherche->gauche;
					remplacant->droite = copyRecherche->droite;
					(*recherche) = remplacant;
				}
			}
			
			printf("C'est la merde\n");
		}
		
		free(copyRecherche);
	}
}

nd creer_noeud(char val)
{
	nd res = (nd)malloc(sizeof(struct noeud));

	res->val = val;
	res->droite = NULL;
	res->gauche = NULL;
	res->occ = 1;

	return res;
}

nd *rechercher(nd *racine, char val)
{
	if ((*racine) == NULL)
	{
		return NULL;
	}
	if ((*racine)->val == val)
	{
		return racine;
	}
	if ((*racine)->val < val)
	{
		return (*racine)->droite == NULL ? NULL : rechercher(&(*racine)->droite, val);
	}
	return (*racine)->gauche == NULL ? NULL : rechercher(&(*racine)->gauche, val);
}

void detruire(nd *rac)
{
	if ((*rac) != NULL)
	{
		if ((*rac)->gauche != NULL)
			detruire(&(*rac)->gauche);
		if ((*rac)->droite != NULL)
			detruire(&(*rac)->droite);
		free((*rac));
	}
	free(rac);
}
