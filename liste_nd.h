#include "noeud.h"

typedef struct ltest* lt;
typedef struct ltest{
    nd val;
    lt next;
};


lt create(nd);
void addToList(lt, char);
void suppressNode(lt*,nd);
void afficherList(lt);
void destroyList(lt);
//void fuse(lt**, lt**);