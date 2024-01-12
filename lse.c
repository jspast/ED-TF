#include <stdio.h>
#include <stdlib.h> //necessaria para o malloc
#include <string.h> //necessaria para o strcmp

#include "lse.h"

PtNo *lse_cria_lista(void)
{
    return NULL;
}

PtNo *lse_insere(PtNo *l, InfoNo dados) {
    PtNo *novo;       // novo elemento
    PtNo *ant = NULL; // ponteiro auxiliar para a posição anterior
    PtNo *ptaux = l;  // ponteiro auxiliar para percorrer a lista

    /*aloca um novo nodo */
    novo = (PtNo *)malloc(sizeof(PtNo));

    /*insere a informação no novo nodo*/
    novo->info = dados;

    /*procurando a posição de inserção*/
    while (ptaux != NULL)
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /*encaeia o elemento*/
    if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na
                        primeira posição*/
    {
        //  puts("inserindo primeiro");
        novo->prox = l;
        l = novo;
    } else /*elemento inserido no meio da lista*/
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return l;
}
void lse_imprime(PtNo *l) {
    PtNo *ptaux;
    if (l == NULL)
        puts("lista vazia");
    else
        for (ptaux = l; ptaux != NULL; ptaux = ptaux->prox)
            printf("\nNumero = %d Senha = %s\n",
                   ptaux->info.num, ptaux->info.senha);
}

PtNo *lse_remove(PtNo *l, int num) {
    PtNo *ant = NULL; // ponteiro auxiliar para a posição anterior
    PtNo *ptaux = l;  // ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux != NULL && (ptaux->info.num == num)) {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /*verifica se achou*/
    if (ptaux == NULL)
        return l; /*retorna a lista original*/

    if (ant == NULL) /*vai remover o primeiro elemento*/
        l = ptaux->prox;
    else /*vai remover do meio ou do final*/
        ant->prox = ptaux->prox;

    free(ptaux); /*libera a memória alocada*/

    return l;
}

PtNo *lse_destroi(PtNo *l) {
    PtNo *ptaux; // ponteiro auxiliar para percorrer a lista
    while (l != NULL) {
        ptaux = l;
        l = l->prox;
        free(ptaux);
    }
    free(l);
    return NULL;
}