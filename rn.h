#include <stdlib.h>

#include "senha.h"

typedef struct RNnodo RNtree;

struct RNnodo {
    InfoNo info;
    int red; /* se red=0 então o nodo é preto */
    struct RNnodo *esq;
    struct RNnodo *dir;
    struct RNnodo *pai;
};

// declarar o nodo NULL
static RNtree *NodoNULL = NULL;

// Definições das Funções
RNtree *rn_insere(RNtree *t, InfoNo dados);
char *rn_consulta(RNtree *t, int num);
RNtree *rn_remove(RNtree *t, int num);
void rn_destroi(RNtree *t);

// Funções Auxiliares
RNtree *VerificaRN(RNtree *t, int num);
RNtree *RotacaoSimplesEsq(RNtree *t);
RNtree *RotacaoSimplesDir(RNtree *t);
void Desenha(RNtree *t, int nivel);
RNtree *Maior(RNtree *t);
RNtree *Menor(RNtree *t);