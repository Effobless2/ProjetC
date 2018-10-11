#include "liste_nd.h"


lt create(nd node){
    lt res = malloc(sizeof(struct ltest));
    res->val = node;
    res->next = NULL;

    return res;
}

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

void destroyList(lt list){
    if (list->next != NULL){
        destroyList(list->next);
    }
    free(list);
}

void afficherList(lt list){
    printf("Valeur : %c, Occurence : %d\n", list->val->val, list->val->occ);
    if (list->next != NULL){
        afficherList(list->next);
    }
}