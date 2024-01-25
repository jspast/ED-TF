#ifndef AVL_H
#define AVL_H

#include "login.h"

typedef struct AVLnodo AVL;

struct AVLnodo{
   Login info;
   int FB;
   struct AVLnodo *esq;
   struct AVLnodo *dir;
};

AVL * avl_insere (AVL * a, Login x, int *ok);
char *avl_consulta(AVL *t, int usr);
AVL * rotacao_direita(AVL * pt);
AVL * rotacao_esquerda(AVL * pt);
AVL * rotacao_dupla_direita (AVL * pt);
AVL * rotacao_dupla_esquerda (AVL * pt);
AVL * Caso1 (AVL * a , int *ok);
AVL * Caso2 (AVL * a , int *ok);

#endif