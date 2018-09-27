#include "liste_nd.h"
#include <string.h>

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
    //printf("Valeur : %c, Occurence : %d\n", list->val->val, list->val->occ);
    if (list->next != NULL){
        afficherList(list->next);
    }
}

/*
void fuse(lt **node1, lt **node2){
    //printf("&node2 : %p, node2 : %p, (*node2) : %p\n", &node2, node2, (*node2));
    nd fusion = creer_noeud(NULL, (**node1)->val->occ + (**node2)->val->occ);
    fusion->gauche = (**node2)->val;
    fusion->droite = (**node1)->val;
    (**node1)->val = fusion;
    lt temp = (*node2);
    (*node2) = (**node2)->next;
    free(temp);

}
*/
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

        nd fusion = creer_noeud(NULL, (*curNode1)->val->occ + (*curNode2)->val->occ);
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