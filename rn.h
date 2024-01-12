#include <stdlib.h>

typedef struct RNnodo RNtree;

struct RNnodo {
    int num;
    char senha[32];
    int red; /* se red=0 então o nodo é preto */
    struct RNnodo *esq;
    struct RNnodo *dir;
    struct RNnodo *pai;
};

// declarar o nodo NULL
static RNtree *NodoNULL = NULL;

// Definições das Funções
RNtree *rn_insere(RNtree *t, int num);
int rn_consulta(int X, RNtree *T);
RNtree *rn_remove(RNtree *t, int num);
void rn_destroi(RNtree *t);

// Funções Auxiliares
RNtree *VerificaRN(RNtree *t, int num);
RNtree *RotacaoSimplesEsq(RNtree *t);
RNtree *RotacaoSimplesDir(RNtree *t);
void Desenha(RNtree *t, int nivel);
RNtree *Maior(RNtree *t);
RNtree *Menor(RNtree *t);