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

nd creer_noeud(char val, int occ)
{
	nd res = (nd)malloc(sizeof(struct noeud));

	res->val = val;
	res->droite = NULL;
	res->gauche = NULL;
	res->occ = occ;

	return res;
}

void ajout(nd *src, char val)
{
	if ((*src) != NULL)
	{
		if ((*src)->val == val)
		{
			(*src)->occ++;
		} else if (val < (*src)->val)
		{
			printf("Ajout gauche \n");
			ajout(&(*src)->gauche, val);
		} else
		{
			printf("Ajout droite \n");
			ajout(&(*src)->droite, val);
		}
	} else
	{
		printf("null \n");
		(*src) = creer_noeud(val, 1);
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


char* recherchePrefixe(nd src, char val){
	if( (*src).val == NULL ){
		//puts("Entrer dans le if null");
		if( (*src).gauche != NULL ){
			//puts("Entrer dans le gauche");
			char *rc = recherchePrefixe( (*src).gauche, val );
			//printf("%s\n", rc);

			if( rc != NULL){
				//puts("rc pas null");
				//printf("Taille rc = %d\n", sizeof(rc));
				char *temp = malloc(sizeof(rc)+ sizeof(char));
				//printf("Taille temp = %d\n", sizeof(temp));
				temp[0] = '0';
				int i;
				for (i = 0; i < sizeof(rc)/sizeof(char); i++){
					temp[i+1] = rc[i];
				}
				temp[i] = '\o';
				//strcat(temp, rc);
				if (strlen(rc) != 0){
					free(rc);
				}
				//printf("%s\n", temp);
				return temp;
			}
		}

		if( (*src).droite != NULL ){
			//puts("Entrer dans le droite");
			char *rc = recherchePrefixe( (*src).droite, val );
			
			if( rc != NULL){
				//puts("rc pas null");
				//printf("Taille rc = %d\n", sizeof(rc));
				char *temp = malloc(sizeof(rc)+ sizeof(char));
				//printf("Taille temp = %d\n", sizeof(temp));
				temp[0] = '1';
				int i;
				for (i = 0; i < sizeof(rc)/sizeof(char); i++){
					temp[i+1] = rc[i];
				}
				temp[i] = '\o';
				//strcat(temp, rc);
				if (strlen(rc) != 0){
					free(rc);
				}
				//printf("%s\n", temp);
				return temp;
			}
		}

	}else if( (*src).val == val){
		//puts("if val == ");
		return "";
	}

	return NULL;
}


char* compression(nd src, char *str){
	int i=0;
	char *rt = malloc(sizeof(char));
	rt[0] = '\0';
	char *temp;
	while(i < strlen(str)){
		//printf("while i = %d\n", i);
		temp = recherchePrefixe(src, str[i]);
		//printf("Temp : %s\n", temp);
		//puts("apres recherche");
		rt = realloc( rt, sizeof(char) * (strlen(rt) + strlen(temp)) + 1 );
		strcat(rt, temp);
		//printf("Temp : %s\n", rt);
		i++;
		free(temp);
	}

	printf("taille = %d | %d\n", strlen(rt), strlen(rt)*sizeof(char));
	return rt;
}

void compression_Fichier(char *name){
	// On lit le fichier et on store les char dans un tableau et on en profite pour compter le nb de symbole
	FILE *fp;
	int taille = 0;
	char* tout;

	fp = fopen(name, "r");
	/* On récupère la taille en allant à la fin du fichier */
	fseek(fp, 0, SEEK_END); // on va a la fin du fichier
	taille = ftell(fp); // cb de bits on a parcouru
	rewind(fp); // retour au début

	tout = malloc(taille+1 * sizeof(char));

	fread(tout, taille, 1, fp);
	tout[taille] = '\0';

	fclose(fp);

	printf("%s\n",tout);

	free(tout);

}

char* decompression(nd src, char *str){
	
	int i = 0;
	char *rt = malloc(sizeof(char));
	nd temp = src;
	rt[0] = '\0';

	while( i < strlen(str)+1 ){
		if( (*temp).val != NULL ){
			rt = realloc( rt, sizeof(char) * (strlen(rt)) + 2);
			// printf("Temp val = %c\n", (*temp).val);
			char valTemp[2];
			valTemp[0] = (*temp).val;
			valTemp[1] = '\0';
			strcat(rt, valTemp);
			temp = src;
		}else{
			if( str[i] == '0' ){
				temp = (*temp).gauche;
			}else{
				temp = (*temp).droite;
			}
			i++;
		}

	}

	return rt;
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
	nd res = creer_noeud(NULL, n1->occ + n2->occ);
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