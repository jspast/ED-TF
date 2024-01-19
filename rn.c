#include <stdio.h>
#include <stdlib.h>

#include "rn.h"

RNtree *rn_insere(RNtree *t, Login dados)
{
    RNtree *x = t;

    if (t == NULL) {
        // alocação de espaço
        NodoNULL = (RNtree *)malloc(sizeof(RNtree));
        x = (RNtree *)malloc(sizeof(RNtree));
        
        // inicializações
        //  NULL
        NodoNULL->red = 0; // null é preto;
        NodoNULL->esq = NodoNULL;
        NodoNULL->dir = NodoNULL;
        NodoNULL->info.usr = 32000;
        NodoNULL->pai = NodoNULL;

        // Raiz
        x->info = dados;
        x->esq = x->dir = NodoNULL;
        x->red = 0;
        x->pai = NodoNULL;

        return x;
    }

    RNtree *p = x->pai; // pai

    while (x != NodoNULL) /* desce na árvore */
    {
        p = x;
        if (dados.usr < x->info.usr)
            x = x->esq;
        else
            x = x->dir;
    }

    if (x != NodoNULL)
        return t; // Nodo Ja Existe

    x = (RNtree *)malloc(sizeof(RNtree));
    x->info = dados;
    x->esq = x->dir = NodoNULL;
    x->pai = p;
    x->red = 1;

    if (dados.usr < p->info.usr)
        p->esq = x;
    else
        p->dir = x;

    // Nodo Foi Inserido mas pode ter modificado as regras então temos que
    // verificar.
    return VerificaRN(t, dados.usr);
}

// Função otimizada pelo Github Copilot
char *rn_consulta(RNtree *t, int usr)
{
    if (t == NULL)
        return NULL;

    while (t != NodoNULL) {
        if (usr == t->info.usr) {
            return t->info.senha;
        } else if (usr < t->info.usr) {
            t = t->esq;
        } else {
            t = t->dir;
        }
    }
    return NULL;
}

RNtree *rn_remove(RNtree *t, int usr) {
    RNtree *x = t;
    RNtree *y;
    RNtree *p = x->pai;

    NodoNULL->info.usr = usr;
    while (x->info.usr != usr) /* desce na árvore */
    {
        p = x;
        if (usr < x->info.usr)
            x = x->esq;
        else
            x = x->dir;
    }
    if (x == NodoNULL)
        return t;
    if (x->red) // nodo é vermelho
    {
        if ((x->esq == NodoNULL) && (x->dir == NodoNULL)) // nodo folha
        {
            if (x->info.usr < p->info.usr)
                p->esq = NodoNULL;
            else
                p->dir = NodoNULL;
            free(x);
            return t;
        }
        if (x->info.usr < p->info.usr) {
            y = Menor(t->dir);
            p->esq = y;
            y->esq = x->esq;
            y->dir = x->dir;
            free(x);
        } else {
            y = Maior(t->esq);
            p->dir = y;
            y->dir = x->dir;
            y->esq = x->esq;
            free(x);
        }
    } else // nodo é preto
    {
        if (x->info.usr < p->info.usr) // filho a esquerda
        {
            if ((p->dir->red == 0) &&
                ((x->esq->red == 0) &&
                 (x->dir->red == 0))) // irmão preto e dois filhos pretos
            {
                if (p->red)
                    p->red = 0; // troca a cor do pai
                else
                    p->red = 1;
                p->dir->red = 1; // troca a cor do irmao
                y = Menor(t->dir);
                p->esq = y;
                y->esq = x->esq;
                y->dir = x->dir;
                free(x);
            } else if ((p->dir->red == 0) &&
                       ((x->esq->red != 0) || (x->dir->red != 0))) {
                y = Menor(t->dir);
                p->esq = y;
                y->esq = x->esq;
                y->dir = x->dir;
                RotacaoSimplesDir(p);
                if (x->red)
                    x->red = 0; // troca a cor do nodo
                else
                    x->red = 1;
                free(x);
            } else // irmão vermelho
            {
                if (p->dir->red) {
                    y = Menor(t->dir);
                    p->esq = y;
                    y->esq = x->esq;
                    y->dir = x->dir;
                    RotacaoSimplesDir(p);
                    free(x);
                }
            }
        } else // filho a direita
        {
            if ((p->esq->red == 0) &&
                ((x->esq->red == 0) &&
                 (x->dir->red == 0))) // irmão preto e dois filhos pretos
            {
                if (p->red)
                    p->red = 0; // troca a cor do pai
                else
                    p->red = 1;
                p->dir->red = 1; // troca a cor do irmao
                y = Maior(t->esq);
                p->dir = y;
                y->dir = x->dir;
                y->esq = x->esq;
                free(x);
            } else if ((p->dir->red == 0) &&
                       ((x->esq->red != 0) || (x->dir->red != 0))) {
                y = Maior(t->esq);
                p->dir = y;
                y->dir = x->dir;
                y->esq = x->esq;
                RotacaoSimplesEsq(p);
                if (x->red)
                    x->red = 0; // troca a cor do nodo
                else
                    x->red = 1;
                free(x);
            } else // irmão vermelho
            {
                if (p->esq->red) {
                    y = Maior(t->esq);
                    p->dir = y;
                    y->dir = x->dir;
                    y->esq = x->esq;
                    RotacaoSimplesEsq(p);
                    free(x);
                }
            }
        }
    }
    VerificaRN(t, usr);
    return t;
}
/*
void rn_destroi(RNtree *t){

}
*/

// Função corrigida(!) e otimizada pelo Github Copilot
RNtree *VerificaRN(RNtree *t, int usr) {
    RNtree *x = t;
    RNtree *p = NULL;
    RNtree *v = NULL;

    while (x != NULL && x->info.usr != usr) {
        v = p;
        p = x;
        if (usr < x->info.usr)
            x = x->esq;
        else
            x = x->dir;
    }

    if (x == NULL) {
        // Node with given usr not found
        return t;
    }

    if (p != NULL && p->red) {
        if (v != NULL) {
            if (p == v->esq) {
                if (v->dir != NULL && v->dir->red) {
                    v->dir->red = 0;
                    p->red = 0;
                    v->red = 1;
                } else {
                    if (x == p->esq && p == v->esq) {
                        t = RotacaoSimplesDir(v);
                    } else if (x == p->dir && p == v->dir) {
                        t = RotacaoSimplesEsq(v);
                    } else if (x == p->dir && p == v->esq) {
                        t = RotacaoSimplesEsq(p);
                        t = RotacaoSimplesDir(v);
                    } else {
                        t = RotacaoSimplesDir(p);
                        t = RotacaoSimplesEsq(v);
                    }
                    x->red = 0;
                    v->red = 1;
                }
            } else {
                if (v->esq != NULL && v->esq->red) {
                    v->esq->red = 0;
                    p->red = 0;
                    v->red = 1;
                } else {
                    if (x == p->esq && p == v->esq) {
                        t = RotacaoSimplesDir(v);
                    } else if (x == p->dir && p == v->dir) {
                        t = RotacaoSimplesEsq(v);
                    } else if (x == p->dir && p == v->esq) {
                        t = RotacaoSimplesEsq(p);
                        t = RotacaoSimplesDir(v);
                    } else {
                        t = RotacaoSimplesDir(p);
                        t = RotacaoSimplesEsq(v);
                    }
                    x->red = 0;
                    v->red = 1;
                }
            }
        }
    }

    t->red = 0;
    x->red = 1;
    return t;
}

// Função otimizada pelo Github Copilot
RNtree *RotacaoSimplesDir(RNtree *t) {
    RNtree *aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
    return aux; // new root
}

// Função otimizada pelo Github Copilot
RNtree *RotacaoSimplesEsq(RNtree *t) {
    RNtree *aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
    return aux; // new root
}

void Desenha(RNtree *t, int nivel) {
    int x;

    if (t != NodoNULL) {
        for (x = 1; x <= nivel; x++)
            printf("=");
        if (t->red)
            printf("%d Red\n", t->info.usr);
        else
            printf("%d Black\n", t->info.usr);
        if (t->esq != NodoNULL)
            Desenha(t->esq, (nivel + 1));
        if (t->dir != NodoNULL)
            Desenha(t->dir, (nivel + 1));
    } else
        printf("Arvore Vazia\n");
}

RNtree *Maior(RNtree *t) {
    while (t != NodoNULL)
        t = t->dir;
    return t->pai;
}

RNtree *Menor(RNtree *t) {
    while (t != NodoNULL)
        t = t->esq;
    return t->pai;
}