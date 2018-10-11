#include "noeud.h"

void afficher(nd n){
	char v = (char)(*n).val;
	int occ = (int)(*n).occ;
	printf("(%c , %d)\n", v, occ);
	if (n->gauche != NULL)
	{
		afficher(n->gauche);
	}
	if (n->droite != NULL)
	{
		afficher(n->droite);
	}
}

nd creer_noeud(char val, void *occ)
{
	nd res = (nd)malloc(sizeof(struct noeud));

	res->val = val;
	res->droite = NULL;
	res->gauche = NULL;
	res->occ = occ;

	return res;
}

void ajout(nd *src, char val, void *occ)
{
	if ((*src) != NULL)
	{
		if ((*src)->val == val)
		{
			return;
		} else if (val < (*src)->val)
		{
			//printf("Ajout gauche \n");
			ajout(&(*src)->gauche, val, occ);
		} else
		{
			//printf("Ajout droite \n");
			ajout(&(*src)->droite, val, occ);
		}
	} else
	{
		//printf("null \n");
		(*src) = creer_noeud(val, occ);
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
		printf("Copy recherche  = %c\n", (*recherche)->val);

		if ((*recherche)->droite == NULL && (*recherche)->gauche == NULL)
		{
			(*recherche) = NULL;
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
	//free(rac);
}


nd fusion(nd n1, nd n2){
	nd res = creer_noeud(NULL, (int)n1->occ + (int)n2->occ);
	if (n1->occ > n2->occ){
		res->droite = n1;
		res->gauche = n2;
	}
	else{
		res->droite = n2;
		res->gauche = n1;
	}

	return res;
}

int nodeComparision(nd n1, nd n2){
	if (n1->occ > n2->occ)
		return 1;
	if (n2->occ > n1->occ)
		return -1;
	if(n1->val == NULL)
		return nodeComparision(n1->droite, n2);
	if (n2->val == NULL)
		return nodeComparision(n1, n2->gauche);
	if (n1->val > n2->val)
		return 1;
	if (n2->val > n1->val)
		return -1;
	return 0;
}

char *GetSavedStringForTree(nd tree, char *prefixe){
	if (tree->val != NULL){
		char * res = malloc(sizeof(char) * (strlen(prefixe) + 5));
		res[0] = '\0';
		strcat(res, prefixe);
		res[strlen(prefixe)] = ':';
		res[strlen(prefixe) + 1] = tree->val;
		res[strlen(prefixe) + 2] = '/';
		res[strlen(prefixe) + 3] = '7';
		//res[strlen(prefixe) + 4] = '\n';
		res[strlen(prefixe) + 4] = '\0';

		if(strlen(prefixe) > 0){
			free(prefixe);
		}

		return res;
	}
	else{
		char *prefixeGauche = malloc(sizeof(char) * strlen(prefixe) +2);
		prefixeGauche[0] = '\0';
		strcat(prefixeGauche, prefixe);
		strcat(prefixeGauche, "0");
		char *prefixeDroite = malloc(sizeof(char) * strlen(prefixe) +2);
		prefixeDroite[0] = '\0';
		strcat(prefixeDroite, prefixe);
		strcat(prefixeDroite, "1");

		if(strlen(prefixe) > 0){
			free(prefixe);
		}

		char *gauche = GetSavedStringForTree(tree->gauche, prefixeGauche);
		char *droite = GetSavedStringForTree(tree->droite, prefixeDroite);

		char *totalRes = malloc(sizeof(char) * (strlen(gauche) + strlen(droite) + 1));
		totalRes[0] = '\0';
		strcat(totalRes, gauche);
		strcat(totalRes, droite);

		free(gauche);
		free(droite);

		return totalRes;

	}
}

void CreateTreeFromString(nd * racine, char *prefixed){
	printf("%s\n", prefixed);
	if(prefixed[0] == ':'){
		(*racine) = creer_noeud(prefixed[1], 0);puts("creation");afficher((*racine));
	}
	else{
		if((*racine) == NULL){
			(*racine) = creer_noeud(NULL, 0);
			
		}
	//afficher((*racine));
		if(prefixed[0] == '0') {
			puts("gauche");
			prefixed++;
			CreateTreeFromString(&((**racine).gauche), prefixed);
		}
		else {
			puts("autre gauche");
			prefixed++;
			CreateTreeFromString(&((**racine).droite), prefixed); 
		}
	}
}