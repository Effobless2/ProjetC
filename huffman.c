
#include "huffman.h"

/*
	Création de l'arbre binaire associé au paramètre text
*/
nd stringEncoding(char *text){
    lt list = create(creer_noeud(text[0], 1));
    for (int i = 1; i < strlen(text); i++){
        addToList(list, text[i]);
    }
    while(list->next != NULL){ //tant que la liste ne contient qu'un seul arbre
        lt *curList = &list;
           
        lt *curNode1 = NULL; 
        lt *curNode2 = NULL; //smaller of two Nodes
        while((*curList) != NULL){ //parcourt de la liste chaînée
            if (curNode2 == NULL){
                curNode2 = curList;
            }
            else if (curNode1 == NULL){
                if(nodeComparision((*curNode2)->val, (*curList)->val) > 0){
                    curNode1 = curNode2;
                    curNode2 = curList;
                }
                else{
                    curNode1 = curList;
                }
            }
            else if (nodeComparision((*curNode1)->val, (*curList)->val) > 0){
                if (nodeComparision((*curNode2)->val, (*curList)->val) > 0){
                    curNode1 = curNode2;
                    curNode2 = curList;
                }
                else{
                    curNode1 = curList;
                }
            }
            curList = &((*curList)->next);
        }

        nd fusion = creer_noeud(NULL, (int)((*curNode1)->val->occ) + (int)((*curNode2)->val->occ));
        fusion->gauche = (*curNode2)->val;
        fusion->droite = (*curNode1)->val;

        (*curNode1)->val = fusion;
        lt temp = (*curNode2);
        (*curNode2) = (*curNode2)->next;
        free(temp); //suppression de la liste chaïnée n'ayant plus de raison d'exister
    }
    
    nd res = &((*list->val));
    destroyList(list);

    return res;
}

nd compression_Fichier(char *name, char *newName){
	// On lit le fichier et on store les char dans un tableau et on en profite pour compter le nb de symbole
	char *texte = readFile(name);
	if(texte == NULL){
		return NULL;
	}
	puts("*****Read file");

	/* ---------- Compression du texte ---------- */
	nd arbreCompression = stringEncoding(texte);
	puts("*****Arbre done");
	char* compr = compression(arbreCompression, texte);
	puts("*****Compression faite");

	free(texte);

	/* ---------- Ecriture dans une archive ---------- */

	char*nameOfCompil = malloc(sizeof(char) * (strlen(newName) + strlen("/compression.txt") + 3));
	nameOfCompil[0] = '.';
	nameOfCompil[1] = '/';
	nameOfCompil[2] = '\0';
	strcat(nameOfCompil, newName);
	nameOfCompil[strlen(newName) + 2] = '\0';

	mkdir(nameOfCompil, 0700);

	strcat(nameOfCompil, "/compression.txt");	
	FILE *fp = fopen(nameOfCompil, "w");
	fwrite(compr, sizeof(char), strlen(compr), fp);
	fclose(fp);

	char *nameOfTree = malloc(sizeof(char) * (strlen(newName) + strlen("/tree.txt") + 3));
	nameOfTree[0] = '.';
	nameOfTree[1] = '/';
	nameOfTree[2] = '\0';
	strcat(nameOfTree, newName);
	nameOfCompil[strlen(newName) + 2] = '\0';
	strcat(nameOfTree, "/tree.txt");

	char *StringTree = GetSavedStringForTree(arbreCompression, "");

	FILE *fT = fopen(nameOfTree, "w");
	fwrite(StringTree, sizeof(char), strlen(StringTree), fT);
	fclose(fT);
	puts("*****Ajout dans le fichier fait");

	free(nameOfCompil);

	free(nameOfTree);

	free(compr);

	free(StringTree);

	return arbreCompression;


}

char* decompression_Fichier(char *name, nd arbre, char *newName){
	char *texte = readFile(name);

	char *texte_binaire = stringASCII_to_stringBinary(texte);
	char *prefixedBinary = HeaderRemoving(texte_binaire);
	char* res = decompression(arbre, prefixedBinary);
	free(texte);
	free(texte_binaire);
	free(prefixedBinary);
	puts("Decompression terminée");

	FILE * fp = fopen(newName, "w");
	fwrite(res, sizeof(char), strlen(res), fp);
	fclose(fp);

	puts("***** Fichier créer");

	return res;
}

/*
	Retourne la chaîne de caractère correspondant au texte 
	préfixé à décompresser en supprimant les en-têtes de chaque bloc de 8 bits
*/
char* HeaderRemoving(char *headeredBinary){
	int taille = strlen(headeredBinary);
	int newTaille = (6*taille)/8;

	char *res = malloc( sizeof(char) * newTaille+1 );
	int cmpt = 0; // reset tout les 6 bits
	int i = 0; // navigation headeredBinary
	int j = 0; // navigation res

	while(i < taille){
		if(cmpt == 0){
			i += 2;
			cmpt = 6;
		}else{
			i++;
			j++;
			cmpt--;
		}
		res[j] = headeredBinary[i];
	}
	res[newTaille] = '\0';

	return res;
}


/*
	Décompresse le texte préfixé str en fonction de l'arbre binaire src
	et retourne le texte décompressé
*/
char* decompression(nd src, char *str){
	
	int i = 0;
	char *rt = malloc(sizeof(char));
	nd temp = src;
	rt[0] = '\0';
	while( i < strlen(str) ){
		if( (*temp).val != NULL ){
			rt = realloc( rt, sizeof(char) * (strlen(rt)) + 2);
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

/*
	Compresse le texte str en fonction de l'arbre binaire src
*/
char* compression(nd src, char *str){
	char **lprefixes[3000];
	nd prefixes = NULL;
	int nbletters = 0;

	char *rt = malloc(sizeof(char));
	rt[0] = '\0';
	char *temp;
	int i = 0;
	while(i < strlen(str)){
		temp = NULL;

		if (prefixes == NULL){ //prefixes est nul -> début du parcourt du texte
			temp = recherchePrefixe(src, str[i]);
			prefixes = creer_noeud(str[i], temp);
			lprefixes[0] = temp;
			nbletters++;
		}
		else{
			nd *cur = rechercher(&prefixes, str[i]); //recherche d'abord dans la liste chaînée
			temp = cur == NULL ? NULL : (char *)((*cur)->occ);
		}

		if (temp == NULL){ //si le caractère a été rencontré poour la première fois
			temp = recherchePrefixe(src, str[i]);
			ajout(&prefixes, str[i], temp);
			lprefixes[nbletters] = temp;
			nbletters++;
		}
		//concaténation du résultat avec le préfixe du char
		rt = realloc( rt, sizeof(char) * (strlen(rt) + strlen(temp)) + 1 );
		strcat(rt, temp);
		i++;
	}

	detruire(&prefixes);
	for (int i = 0; i < nbletters; i++){
		free(lprefixes[i]);
	}
	char *result = stringBinary_to_stringASCII(rt);
	free(rt);
	return result;
}

/*
	Parcourt l'arbre src en profondeur jusqu'à trouver le caractère val
	et retourne son préfixe
*/
char *recherchePrefixe(nd src, char val){
	if (src->val != NULL){ //src est uen feuille
		if (src->val == val){
			char * res = malloc(sizeof(char));
			res[0]= '\0';
			return res;
		}
		else{
			return NULL; // val n'est pas inclut dans cette partie de l'arbre
		}
	}
	else{
		char *res = recherchePrefixe(src->gauche, val); //recherche à gauche
		if (res != NULL){ //si val a pas été trouvé dans les enfants de gauche
			char *temp = malloc(sizeof(char) * (strlen(res) + 2));
			temp[0] = '0';
			temp[1] = '\0';
			strcat(temp, res);
			free(res);
			return temp;
		}
		else{
			res = recherchePrefixe(src->droite, val); //recherche à droite
			if (res != NULL){ //si val a pas été trouvé dans les enfants de droite
				char *temp = malloc(sizeof(char) * (strlen(res) + 2));
				temp[0] = '1';
				temp[1] = '\0';
				strcat(temp, res);
				free(res);
				return temp;
			}
			else{
				return NULL; //val ne fait définitivement pas partie de l'arbre
			}
		}
	}
}