#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lse.h"
#include "rn.h"
#include "senha.h"

int main(int argc, char *argv[])
{
    PtNo *l;
    RNtree *t = NodoNULL;

    // Teste LSE
    l = lse_cria_lista();
	l = lse_insere(l, (InfoNo){1, "teste"});
    if(strcmp(lse_consulta(l, 1), "teste") == 0)
        puts("Teste LSE: Senha correta!");

    // Teste RN
    t = rn_insere(t, (InfoNo){1, "teste"});
    if(strcmp(rn_consulta(t, 1), "teste") == 0)
        puts("Teste RN: Senha correta!");

	return 0;
}