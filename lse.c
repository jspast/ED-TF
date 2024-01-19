#include <stdio.h>
#include <stdlib.h> //necessaria para o malloc
#include <string.h> //necessaria para o strcmp

#include "lse.h"

LSE *lse_cria_lista(void)
{
    return NULL;
}

// Insere sempre no início (mais eficiente) porque a ordem não importa
LSE *lse_insere(LSE *l, Login dados) {
    LSE *novo = (LSE *)malloc(sizeof(LSE)); // Aloca memória para o novo nó
    
    novo->info = dados;
    novo->prox = l;

    return novo;
}

char *lse_consulta(LSE *l, int usr) {
    LSE *ptaux = l;  // ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux != NULL && (ptaux->info.usr != usr))
        ptaux = ptaux->prox;

    /*verifica se achou*/
    if (ptaux == NULL)
        return NULL;
    else
        return ptaux->info.senha;
}

LSE *lse_remove(LSE *l, int usr) {
    LSE *ant = NULL; // ponteiro auxiliar para a posição anterior
    LSE *ptaux = l;  // ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux != NULL && (ptaux->info.usr != usr)) {
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

LSE *lse_destroi(LSE *l) {
    LSE *ptaux; // ponteiro auxiliar para percorrer a lista
    while (l != NULL) {
        ptaux = l;
        l = l->prox;
        free(ptaux);
    }
    free(l);
    return NULL;
}