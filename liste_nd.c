//--------------------------------------------------------------------
//Projet de C : Codage de Huffman
//DEBOFFLE Maxime
//IDOUX Etienne
//--------------------------------------------------------------------



#include "liste_nd.h"



//--------------------------------------------------------
//Paramètres : Pointeur de noeud nd
//Retourne : Pointeur de liste lt
//Utilité : Permet de créer une liste à partir d'un noeud.
//--------------------------------------------------------
lt create(nd node){
    lt res = malloc(sizeof(struct ltest));
    res->val = node;
    res->next = NULL;

    return res;
}



//-------------------------------------------------------------
//Paramètres : 
//      Pointeur de liste
//      Caractère à ajouter à la liste
//Retourne : void
//Utilité : Ajoute le caractère à la liste donnée en paramètre.
//-------------------------------------------------------------
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



//---------------------------------------------------------------------------
//Paramètres : 
//      Pointeur de pointeur de liste
//      Pointeur de noeud
//Retourne : void
//Utilité : Supprime le noeud de la liste des paramètres et resoude celle-ci.
//---------------------------------------------------------------------------
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



//------------------------------------------------------
//Paramètres : Pointeur de liste
//Retourne : void
//Utilité : Supprime la liste ainsi que tout ses noeuds.
//------------------------------------------------------
void destroyList(lt list){
    if (list->next != NULL){
        destroyList(list->next);
    }
    free(list);
}



//---------------------------------------------------
//Paramètres : Pointeur de liste
//Retourne : void
//Utilité : Permet d'afficher la liste et ses noeuds.
//---------------------------------------------------
void afficherList(lt list){
    printf("Valeur : %c, Occurence : %d\n", list->val->val, list->val->occ);
    if (list->next != NULL){
        afficherList(list->next);
    }
}