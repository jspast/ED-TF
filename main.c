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
    char nome_arquivo[TAM_ARQUIVO];
    double tempo;

    if(argc == 1) {
        puts("Digite o nome do arquivo da base de dados");
        scanf("%s", nome_arquivo);
    } else {
        strcpy(nome_arquivo, argv[1]);
    }

    // Teste LSE
    l = lse_carrega(l, nome_arquivo, &tempo);
    if (l == NULL)
        return 0;
    if(strcmp(lse_consulta(l, 1), "teste") == 0)
        puts("Teste LSE: Senha correta!");
    else
        puts("Teste LSE: Senha incorreta!");

    printf("Tempo de carregamento LSE: %.0lf segundos\n", tempo);

    // Teste RN
    t = rn_carrega(t, nome_arquivo, &tempo);
    if (t == NULL)
        return 0;
    t = rn_insere(t, (Login){1, "test"});
    if(strcmp(rn_consulta(t, 1), "teste") == 0)
        puts("Teste RN: Senha correta!");
    else
        puts("Teste RN: Senha incorreta!");

    printf("Tempo de carregamento RN: %.0lf segundos\n", tempo);

    return 0;
}