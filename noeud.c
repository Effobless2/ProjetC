#include "noeud.h"

/*
	Affiche l'arbre mit en paramètre
*/
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
/*
	Crée un noeud minimal possédant les informations mises en pramètre
*/
nd creer_noeud(char val, void *occ)
{
	nd res = (nd)malloc(sizeof(struct noeud));

	res->val = val;
	res->droite = NULL;
	res->gauche = NULL;
	res->occ = occ;

	return res;
}

/*
	Ajoute à l'arbre src un nouveau noeud possédant une valeur val et une occurence occ
*/
void ajout(nd *src, char val, void *occ)
{
	if ((*src) != NULL)
	{
		if ((*src)->val == val)
		{
			return;
		} else if (val < (*src)->val)
		{
			ajout(&(*src)->gauche, val, occ);
		} else
		{
			ajout(&(*src)->droite, val, occ);
		}
	} else
	{
		(*src) = creer_noeud(val, occ);
	}
}

/*
	Retourne le noeud max d'un arbre s'il existe
*/
nd noeudMax(nd racine){
	if (racine != NULL){
		return (*racine).droite == NULL ? racine : noeudMax((*racine).droite);
	}
	return NULL;
}
/*
	Retourne le noeud min d'un arbre s'il existe
*/
nd noeudMin(nd racine){
	if (racine != NULL){
		return racine->gauche == NULL ? racine : noeudMin(racine->gauche);
	}
	return NULL;
}

/*
	Retourne le noeud parent d'un noeud possédant la valeur val dans le noeud src (si ce dernier s'y trouve) 
*/
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


/*
	Supprime le noeud possédant la valeur val dans src et remplace ce premier 
	dans src par un de ses enfants afin de maintenir la cohhésion générale de l'arbre
*/
void supprimer(nd src, char val)
{
	nd *recherche = rechercher(&src, val);
	if (recherche != NULL)
	{
		nd copyRecherche = (*recherche);

		if ((*recherche)->droite == NULL && (*recherche)->gauche == NULL)
		{
			(*recherche) = NULL;
		}
		else if ((*recherche)->droite == NULL && (*recherche)->gauche != NULL)
		{
			(*recherche) = (*recherche)->gauche;
		}
		else if ((*recherche)->droite != NULL && (*recherche)->gauche == NULL)
		{
			(*recherche) = (*recherche)->droite;

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
		}
		
		free(copyRecherche);
	}
}

/*
	retourne l'adresse du pointeur du noeud ayant la valeur val dans racine
*/
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

/*
	Détruit l'arbre 'rac et ses enfants
*/
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
}

/*
	Permettait de fusionner les deux noeuds mis en paramètre mais n'est pas utilisée
*/
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

/*
	Compare deux noeuds selon leur occurence et selon leur valeurs.
	Si leur occurence est égale et leur valeur NULL, nous les comparons en fonction de leurs enfants
*/
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


/*
	Permet de créer une chaine de caractère représentative de l'arbre tree
	prefixe est le prefixe créer avant les appels récursifs
*/
char *GetSavedStringForTree(nd tree, char *prefixe){
	if (tree->val != NULL){ //si tree est une feuille
		char * res = malloc(sizeof(char) * (strlen(prefixe) + 5));
		res[0] = '\0';
		strcat(res, prefixe);
		res[strlen(prefixe)] = ':';
		res[strlen(prefixe) + 1] = tree->val;
		res[strlen(prefixe) + 2] = '/';
		res[strlen(prefixe) + 3] = '7';
		res[strlen(prefixe) + 4] = '\0'; //marque la fin du parcourt de cette partie de l'arbre et retourne le chemin et le caractère associé

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

		char *gauche = GetSavedStringForTree(tree->gauche, prefixeGauche); //ensemble des chemins pour tous les enfants gauche de l'arbre
		char *droite = GetSavedStringForTree(tree->droite, prefixeDroite); //ensemble des chemins pour tous les enfants droite de l'arbre

		char *totalRes = malloc(sizeof(char) * (strlen(gauche) + strlen(droite) + 1));
		totalRes[0] = '\0';
		strcat(totalRes, gauche);
		strcat(totalRes, droite);

		free(gauche);
		free(droite);

		return totalRes; //string à écrire dans le fichier tree.txt

	}
}

/*
	Permet de recréer l'arbre tree à partir d'un préfixe prefixe
*/
void CreateTreeFromString(nd * racine, char *prefixed){
	if(prefixed[0] == ':'){ //arbre parcourut jusqu'à la feuille contenant le caractère
		(*racine) = creer_noeud(prefixed[1], 0);
	}
	else{
		if((*racine) == NULL){ //si l'on construit une nouvelle branche de l'arbre global
			(*racine) = creer_noeud(NULL, 0);
			
		}

		if(prefixed[0] == '0') { //si le chemin demande d'aller à gauche
			prefixed++; //on déplace le curseur de prefixe afin de passer au prochain pas
			CreateTreeFromString(&((**racine).gauche), prefixed);
		}
		else { //si le chemin demande d'aller à droite
			prefixed++; //on déplace le curseur de prefixe afin de passer au prochain pas
			CreateTreeFromString(&((**racine).droite), prefixed); 
		}
	}
}