
#include "huffman.h"

nd stringEncoding(char *text){
    lt list = create(creer_noeud(text[0], 1));
    for (int i = 1; i < strlen(text); i++){
        addToList(list, text[i]);
    }
    //afficherList(list);
    //printf("list : %p\n",&list);
    while(list->next != NULL){
        lt *curList = &list;
        // &list == curList
        //printf("curlist : %p\n",curList);
           
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
            }/*
            else if (nodeComparision((*curNode2)->val, (*curList)->val) > 0){
                curNode1 = curNode2;
                curNode2 = curList;
            }*/
            curList = &((*curList)->next);
        }
        //afficherList((*curNode1));
        //afficherList((*curNode2));

        nd fusion = creer_noeud(NULL, (int)((*curNode1)->val->occ) + (int)((*curNode2)->val->occ));
        fusion->gauche = (*curNode2)->val;
        fusion->droite = (*curNode1)->val;
        //afficher(fusion);

        (*curNode1)->val = fusion;
        lt temp = (*curNode2);
        (*curNode2) = (*curNode2)->next;
        free(temp);
        
        //fuse(&curNode1, &curNode2);
        /*
        afficher(fusion);
        afficherList(list);*/
    }
    
    //afficherList((list));
    nd res = &((*list->val));
    //printf("\n");
    //afficher(res);
    //printf("\n");
    destroyList(list);

    return res;
}

nd compression_Fichier(char *name){
	// On lit le fichier et on store les char dans un tableau et on en profite pour compter le nb de symbole
	char *texte = readFile(name);

	/* ---------- Compression du texte ---------- */
	nd arbreCompression = stringEncoding(texte);
	char* compr = compression(arbreCompression, texte);

	free(texte);
	//detruire(&arbreCompression);
	//printf("Compression = %s\n", compr);

	/* ---------- Ecriture dans un fichier ---------- */
	FILE *fp = fopen("compression.txt", "w");
	fwrite(compr, sizeof(char), strlen(compr), fp);
	fclose(fp);


	free(compr);

	return arbreCompression;


}

char* decompression_Fichier(char *name, nd arbre){
	char *texte = readFile(name);

	char* res = decompression(arbre, texte);
	free(texte);

	return res;
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
		
		//puts("apres recherche");
		rt = realloc( rt, sizeof(char) * (strlen(rt) + strlen(temp)) + 1 );
		strcat(rt, temp);
		//printf("Temp : %s\n", rt);
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

char* recherchePrefixe(nd src, char val){
	if( (*src).val == NULL ){
		char prefixe;
		nd noeud;
		char *rc = NULL;
		if( (*src).gauche != NULL ){
			noeud = (*src).gauche;
			prefixe = '0';
			rc = recherchePrefixe( noeud, val );
			//printf("%s\n", rc);
		}

		if(rc == NULL && (*src).droite != NULL ){
			noeud = (*src).droite;
			prefixe = '1';
			//puts("Entrer dans le droite");
			rc = recherchePrefixe( noeud, val );
		}
		
		if (rc != NULL){
			//puts("rc pas null");
			//printf("Taille rc = %d\n", sizeof(rc));
			char *temp = malloc(sizeof(rc)+ sizeof(char));
			//printf("Taille temp = %d\n", sizeof(temp));
			temp[0] = prefixe;
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

	} else if( (*src).val == val){
		//puts("if val == ");
		return "";
	}

	return NULL;
}
