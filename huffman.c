//--------------------------------------------------------------------
//Projet de C : Codage de Huffman
//DEBOFFLE Maxime
//IDOUX Etienne
//--------------------------------------------------------------------



#include "huffman.h"



//----------------------------------------------------------------
//Paramètres : Tableau de char représentant un texte à encodé
//Retourne : Pointeur de noeud représentant l'arbre de Huffman
//Utilité : Création de l'arbre binaire associé au paramètre text.
//----------------------------------------------------------------
nd stringEncoding(char *text){
    lt list = create(creer_noeud(text[0], 1));
    for (int i = 1; i < strlen(text); i++){
        addToList(list, text[i]);
    }
    while(list->next != NULL){
        lt *curList = &list;
           
        lt *curNode1 = NULL; 
        lt *curNode2 = NULL; //smaller of two Nodes
        while((*curList) != NULL){
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
        free(temp);
    }
    
    nd res = &((*list->val));
    destroyList(list);

    return res;
}



//-----------------------------------------------------------------------------------------------------------
//Paramètres :
//		Nom du fichier à compresser
//		Nom du fichier à créer
//Retourne : Pointeur de noeud de l'arbre de Huffman
//Utilité : Applique l'algorithme de Huffman pour créer un arbre et enregistre la traduction dans un fichier.
//-----------------------------------------------------------------------------------------------------------
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

	/* ---------- Ecriture dans un fichier ---------- */

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



//------------------------------------------------------------------------------------------------------------------
//Paramètres :
//		Nom du fichier à décompresser
//		Pointeur de noeud de l'arbre de Huffman associé au fichier à décompresser
//		Nom du fichier à créer
//Retourne : Tableau de noeud représentant le fichier décompressé
//Utilité : Décompresse un fichier de l'algorithme d'Huffman avec son arbre associé et l'enregistre dans un fichier.
//------------------------------------------------------------------------------------------------------------------
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



//---------------------------------------------------------------------------------------------------------------
//Paramètres : La chaîne ASCII des préfixes
//Retourne : La chaîne binaire des préfixes sans les ajouts de la compression
//Utilité : Supprime les préfixes ajoutés lors de la compression à chaque caractère ASCII et renvoie ce résultat.
//---------------------------------------------------------------------------------------------------------------
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



//-----------------------------------------------------------------------------
//Paramètres :
//		Arbre de Huffman associé à la chaîne
//		Chaîne à décompresser
//Retourne : La chaîne de caractère en paramètre décompressée
//Utilité : Décompresse le texte préfixé str en fonction de l'abre binaire src.
//-----------------------------------------------------------------------------
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



//-----------------------------------------------------------------------------
//Paramètres :
//		Arbre de Huffman associé à la chaîne str
//		Chaîne de caractère à compresser
//Retourne : Chaîne de caractère représentant la chaîne en paramètre compressée
//Utilité : Compresse le texte str en fonction de l'arbre binaire src.
//-----------------------------------------------------------------------------
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

		if (prefixes == NULL){
			temp = recherchePrefixe(src, str[i]);
			prefixes = creer_noeud(str[i], temp);
			lprefixes[0] = temp;
			nbletters++;
		}
		else{
			nd *cur = rechercher(&prefixes, str[i]);
			temp = cur == NULL ? NULL : (char *)((*cur)->occ);
		}

		if (temp == NULL){
			temp = recherchePrefixe(src, str[i]);
			ajout(&prefixes, str[i], temp);
			lprefixes[nbletters] = temp;
			nbletters++;
		}
		
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



//-------------------------------------------------------------------------------------------------------------------------
//Paramètres :
//		Arbre de Huffman
//		Caractère présent dans l'arbre donné en paramètre
//Retourne : Le préfixe du caractère dans l'arbre de Huffman
//Utilité : Parcours l'arbre de Huffman en profondeur jusqu'à trouver le caractère et créer son préfixe au fur et à mesure.
//-------------------------------------------------------------------------------------------------------------------------
char *recherchePrefixe(nd src, char val){
	if (src->val != NULL){
		if (src->val == val){
			char * res = malloc(sizeof(char));
			res[0]= '\0';
			return res;
		}
		else{
			return NULL;
		}
	}
	else{
		char *res = recherchePrefixe(src->gauche, val);
		if (res != NULL){
			char *temp = malloc(sizeof(char) * (strlen(res) + 2));
			temp[0] = '0';
			temp[1] = '\0';
			strcat(temp, res);
			free(res);
			return temp;
		}
		else{
			res = recherchePrefixe(src->droite, val);
			if (res != NULL){
				char *temp = malloc(sizeof(char) * (strlen(res) + 2));
				temp[0] = '1';
				temp[1] = '\0';
				strcat(temp, res);
				free(res);
				return temp;
			}
			else{
				return NULL;
			}
		}
	}
}