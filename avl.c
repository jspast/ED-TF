#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

AVL *avl_insere_arvore(AVL *a, Login ch) {
  if (a == NULL) {
    a = (AVL *)malloc(sizeof(AVL));
    a->info = ch;
    a->esq = NULL;
    a->dir = NULL;
    a->FB = 0; // o nodo � sempre inserido como folha ent�o seu fator de
               // balanceamento � 0
  } else if (ch.usr < (a->info.usr))
    a->esq = avl_insere_arvore(a->esq, ch);
  else
    a->dir = avl_insere_arvore(a->dir, ch);
  return a;
}

// Função otimizada pelo Github Copilot
char *avl_consulta(AVL *t, int usr) {
  if (t == NULL)
    return "\0";

  while (t != NULL) {
    if (usr == t->info.usr) {
      return t->info.senha;
    } else if (usr < t->info.usr) {
      t = t->esq;
    } else {
      t = t->dir;
    }
  }
  return "\0";
}

int Altura(AVL *a) {
  int Alt_Esq, Alt_Dir;
  if (a == NULL)
    return 0;
  else {
    Alt_Esq = Altura(a->esq);
    Alt_Dir = Altura(a->dir);
    if (Alt_Esq > Alt_Dir)
      return (1 + Alt_Esq);
    else
      return (1 + Alt_Dir);
  }
}

int Calcula_FB(AVL *a) { return (Altura(a->esq) - Altura(a->dir)); }

void Desenha(AVL *a, int nivel) {
  int x;

  if (a != NULL) {
    for (x = 1; x <= nivel; x++)
      printf("=");
    printf("%d FB= %d\n", a->info.usr, Calcula_FB(a));
    if (a->esq != NULL)
      Desenha(a->esq, (nivel + 1));
    if (a->dir != NULL)
      Desenha(a->dir, (nivel + 1));
  }
}

int is_avl(AVL *a) {
  int alt_esq, alt_dir;

  if (a != NULL) {
    alt_esq = Altura(a->esq);
    alt_dir = Altura(a->dir);
    return ((alt_esq - alt_dir < 2) && (alt_dir - alt_esq < 2) &&
            (is_avl(a->esq)) && (is_avl(a->dir)));
  } else
    return 1;
}

AVL *rotacao_direita(AVL *pt) {
  AVL *ptu;

  ptu = pt->esq;
  pt->esq = ptu->dir;
  ptu->dir = pt;
  pt->FB = 0;
  pt = ptu;
  return pt;
}

AVL *rotacao_esquerda(AVL *pt) {
  AVL *ptu;

  ptu = pt->dir;
  pt->dir = ptu->esq;
  ptu->esq = pt;
  pt->FB = 0;
  pt = ptu;
  return pt;
}

AVL *rotacao_dupla_direita(AVL *pt) {
  AVL *ptu, *ptv;

  ptu = pt->esq;
  ptv = ptu->dir;
  ptu->dir = ptv->esq;
  ptv->esq = ptu;
  pt->esq = ptv->dir;
  ptv->dir = pt;
  if (ptv->FB == 1)
    pt->FB = -1;
  else
    pt->FB = 0;
  if (ptv->FB == -1)
    ptu->FB = 1;
  else
    ptu->FB = 0;
  pt = ptv;
  return pt;
}

AVL *rotacao_dupla_esquerda(AVL *pt) {
  AVL *ptu, *ptv;

  ptu = pt->dir;
  ptv = ptu->esq;
  ptu->esq = ptv->dir;
  ptv->dir = ptu;
  pt->dir = ptv->esq;
  ptv->esq = pt;
  if (ptv->FB == -1)
    pt->FB = 1;
  else
    pt->FB = 0;
  if (ptv->FB == 1)
    ptu->FB = -1;
  else
    ptu->FB = 0;
  pt = ptv;
  return pt;
}

AVL *Caso1(AVL *a, int *ok) {
  AVL *ptu;

  ptu = a->esq;
  if (ptu->FB == 1) {
    //printf("fazendo rotacao direita em %d\n", a->info.usr);
    a = rotacao_direita(a);
  } else {
    //printf("fazendo rotacao dupla direita em %d\n", a->info.usr);
    a = rotacao_dupla_direita(a);
  }

  a->FB = 0;
  *ok = 0;
  return a;
}

AVL *Caso2(AVL *a, int *ok) {
  AVL *ptu;

  ptu = a->dir;
  if (ptu->FB == -1) {
    //Desenha(a, 1);
    //printf("fazendo rotacao esquerda em %d\n", a->info.usr);
    a = rotacao_esquerda(a);
  } else {
    //Desenha(a, 1);
    //printf("fazendo rotacao dupla esquerda em %d\n", a->info.usr);
    a = rotacao_dupla_esquerda(a);
  }
  a->FB = 0;
  *ok = 0;
  return a;
}

AVL *avl_insere(AVL *a, Login x, int *ok) {
  /* Insere nodo em uma �rvore AVL, onde A representa a raiz da �rvore,
    x, a ch.usrave a ser inserida e h a altura da �rvore */

  if (a == NULL) {
    a = (AVL *)malloc(sizeof(AVL));
    a->info = x;
    a->esq = NULL;
    a->dir = NULL;
    a->FB = 0;
    *ok = 1;
  } else if (x.usr < a->info.usr) {
    a->esq = avl_insere(a->esq, x, ok);
    if (*ok) {
      switch (a->FB) {
      case -1:
        a->FB = 0;
        *ok = 0;
        break;
      case 0:
        a->FB = 1;
        break;
      case 1:
        a = Caso1(a, ok);
        break;
      }
    }
  } else {
    a->dir = avl_insere(a->dir, x, ok);
    if (*ok) {
      switch (a->FB) {
      case 1:
        a->FB = 0;
        *ok = 0;
        break;
      case 0:
        a->FB = -1;
        break;
      case -1:
        a = Caso2(a, ok);
        break;
      }
    }
  }
  return a;
}
