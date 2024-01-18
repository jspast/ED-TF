#include <stdio.h>
#include <string.h>

#include "lse.h"
#include "rn.h"
#include "senha.h"
#include "arquivos.h"

int main(int argc, char *argv[])
{
    LSE *l = lse_cria_lista();
    RNtree *t = NodoNULL;
    char nome_arquivo[32];
    double tempo;

    puts("Digite o nome do arquivo da base de dados");
    scanf("%s", nome_arquivo);

    l = lse_carrega(l, nome_arquivo, &tempo);
    if(strcmp(lse_consulta(l, 1), "teste") == 0)
        puts("Teste LSE: Senha correta!");
    else
        puts("Teste LSE: Senha incorreta!");

    printf("Tempo: %lf\n", tempo);

    /*
    // Teste RN
    t = rn_insere(t, (Login){1, "test"});
    if(strcmp(rn_consulta(t, 1), "teste") == 0)
        puts("Teste RN: Senha correta!");
    else
        printf("Senha incorreta");
    */

    return 0;
}