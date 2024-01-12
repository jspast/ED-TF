#include <stdio.h>
#include <stdlib.h>  //necessaria para o malloc
#include <string.h> //necessaria para o strcmp
#include "lse.h"

PtNo* cria_lista(void)
{
       return NULL;
}

PtNo* insere_ord (PtNo* l, InfoNo dados)
{
       PtNo *novo; //novo elemento
       PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
       PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (PtNo*) malloc(sizeof(PtNo));

       /*insere a informação no novo nodo*/
       novo->info = dados;


       /*procurando a posição de inserção*/
       while ((ptaux!=NULL) && (strcmp(ptaux->info.titulo,dados.titulo)<0)) //se info.titulo < dados.titulo então strcmp retorna um valor menor que zero
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }

       /*encaeia o elemento*/
       if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
       {
             //  puts("inserindo primeiro");
               novo->prox = l;
               l = novo;
       }
       else /*elemento inserido no meio da lista*/
       {
            novo->prox = ant->prox;
            ant->prox = novo;
       }

       return l;
}
void imprime(PtNo* l)
{
     PtNo* ptaux;
     if (l == NULL)
        puts("lista vazia");
     else
     for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox)
         printf("\nTitulo = %s Distribuidor = %s Diretor = %s\n",ptaux->info.titulo,ptaux->info.distr,ptaux->info.diretor);
}

PtNo* remover(PtNo* l, char titulo[20])
{
     PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
     PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

     /*procura o elemento na lista*/
     while (ptaux !=NULL && (strcmp(ptaux->info.titulo, titulo)))
     {
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

PtNo* destroi(PtNo* l)
{
   PtNo *ptaux; //ponteiro auxiliar para percorrer a lista
   while (l != NULL)
   {
         ptaux = l;
         l = l->prox;
         free(ptaux);
   }
   free(l);
   return NULL;
}
