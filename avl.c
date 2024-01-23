#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

AVL *avl_insere(AVL *a, Login x, int *ok) {
    /* Insere nodo em uma Árvore AVL, onde A representa a raiz da Árvore,
      x, a ch.usrave a ser inserida e h a altura da Árvore */

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
        a = rotacao_direita(a);
    } else {
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
        a = rotacao_esquerda(a);
    } else {
        a = rotacao_dupla_esquerda(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}