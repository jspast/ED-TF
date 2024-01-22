#ifndef AVL_H
#define AVL_H

#include "senha.h"

typedef struct AVLnodo AVL;

struct AVLnodo{
   Login info;
   int FB;
   struct AVLnodo *esq;
   struct AVLnodo *dir;
};

AVL * avl_insere_arvore(AVL * a, Login ch);
char *avl_consulta(AVL *t, int usr);
int Altura (AVL * a);
int Calcula_FB(AVL * a);
void Desenha(AVL * a , int nivel);
int is_avl(AVL * a);
AVL * rotacao_direita(AVL * pt);
AVL * rotacao_esquerda(AVL * pt);
AVL * rotacao_dupla_direita (AVL * pt);
AVL * rotacao_dupla_esquerda (AVL * pt);
AVL * Caso1 (AVL * a , int *ok);
AVL * Caso2 (AVL * a , int *ok);
AVL * avl_insere (AVL * a, Login x, int *ok);

#endif