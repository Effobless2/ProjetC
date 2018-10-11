//--------------------------------------------------------------------
//Projet de C : Codage de Huffman
//DEBOFFLE Maxime
//IDOUX Etienne
//--------------------------------------------------------------------

#include "liste_nd.h"

/*
    Crée et retourne une liste chainée contenant comme valeur le noeud node
*/
lt create(nd node){
    lt res = malloc(sizeof(struct ltest));
    res->val = node;
    res->next = NULL;

    return res;
}

/*
    Ajoute une nouvelle liste chainée ayant un noeud possédant comme valeur val
    à la fin de la liste chaînée list
*/
void addToList(lt list, char val){
    if (list->val->val == val){
        list->val->occ++;
        return;
    }
    if (list->next == NULL){
        lt new = create(creer_noeud(val, 1));
        list->next = new;
        return;
    }
    else{
        addToList(list->next, val);
    }
}


/*
    Supprime la liste chainée ayant pour valeur le paramètre node
    à la liste lt et resoude cette dernière
*/
void suppressNode(lt *list, nd node){
    if ((*list)->val == node){
        lt temp = (*list);
        (*list) = temp->next;
        free(temp);
    }
    else if ((*list)->next != NULL){
        suppressNode(&(*list)->next,node);
    }
}


/*
    Détruit la liste chaînée lt et le reste de sa chaîne
*/
void destroyList(lt list){
    if (list->next != NULL){
        destroyList(list->next);
    }
    free(list);
}

/*
    affiche la liste chaînée list
*/
void afficherList(lt list){
    printf("Valeur : %c, Occurence : %d\n", list->val->val, list->val->occ);
    if (list->next != NULL){
        afficherList(list->next);
    }
}