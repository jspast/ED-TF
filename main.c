#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lse.h"
#include "rn.h"
#include "senha.h"

int main(int argc, char *argv[])
{
    LSE *l;
    RNtree *t = NodoNULL;

    // Teste LSE
    l = lse_cria_lista();
    l = lse_insere(l, (Login){1, "teste"});
    if(strcmp(lse_consulta(l, 1), "teste") == 0)
        puts("Teste LSE: Senha correta!");

    // Teste RN
    t = rn_insere(t, (Login){1, "teste"});
    if(strcmp(rn_consulta(t, 1), "teste") == 0)
        puts("Teste RN: Senha correta!");

    return 0;
}