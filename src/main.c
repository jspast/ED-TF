#include <stdio.h>
#include <string.h>

#include "lse.h"
#include "avl.h"
#include "arquivos.h"
#include "login.h"

#define NOME_EXEC argv[0]

int main(int argc, char *argv[])
{
    LSE *l = lse_cria_lista();
    AVL *t = NULL;
    char nome_dados[TAM_ARQUIVOS] = DADOS;
    char nome_testes[TAM_ARQUIVOS] = TESTES;
    char nome_resultados[TAM_ARQUIVOS] = RESULTADOS;
    int numero_logins_dados, numero_logins, porcentagem_erros;
    long tempo;

    // Verifica argumentos de inicialização
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0) {
            printf("Uso:\t%s [nome_dados] [nome_testes] [nome_resultados]\n\t%s [opcao]\n", NOME_EXEC, NOME_EXEC);
            puts("Opcoes:");
            puts("-d: Usa nomes de arquivos default (dados.txt, testes.txt, resultados.txt)");
            puts("-gd: Gera arquivos da base de dados");
            puts("-gt: Gera arquivos da base de testes");
            puts("-h: Mostra esta mensagem de ajuda");
            return 0;

        } else if (strcmp(argv[1], "-gd") == 0) {
            puts("Gerando arquivos da base de dados");
            puts("Digite o numero de logins da base de dados:");
            scanf("%d", &numero_logins);
            puts("Digite o nome do arquivo da base de dados não ordenada:");
            scanf("%s", nome_dados);
            gera_dados(nome_dados, numero_logins);
            puts("Digite o nome do arquivo da base de dados ordenada:");
            scanf("%s", nome_dados);
            gera_dados_ord(nome_dados, numero_logins);
            return 0;

        } else if (strcmp(argv[1], "-gt") == 0) {
            puts("Gerando arquivos da base de dados");
            puts("Digite o nome do arquivo da base de dados para basear os testes:");
            scanf("%s", nome_dados);
            puts("Digite o numero de logins da base de dados:");
            scanf("%d", &numero_logins_dados);
            puts("Digite o nome do arquivo da base de testes:");
            scanf("%s", nome_testes);
            puts("Digite o numero de logins da base de testes:");
            scanf("%d", &numero_logins);
            puts("Digite a porcentagem de erros nos logins da base de testes:");
            scanf("%d", &porcentagem_erros);
            gera_testes(nome_dados, nome_testes, numero_logins_dados, numero_logins, porcentagem_erros);
            return 0;

        } else if (strcmp(argv[1], "-d") == 0) {
            puts("Usando nomes de arquivos default");
            
        } else {
            if (argc <= 1) {
                puts("Digite o nome do arquivo da base de dados:");
                scanf("%s", nome_dados);
            } else {
                strcpy(nome_dados, argv[1]);
            }
            if (argc <= 2) {
                puts("Digite o nome do arquivo da base de testes:");
                scanf("%s", nome_testes);
            } else {
                strcpy(nome_testes, argv[2]);
            }
            if (argc <= 3) {
                puts("Digite o nome do arquivo dos resultados:");
                scanf("%s", nome_resultados);
            } else {
                strcpy(nome_resultados, argv[3]);
            }
        }   
    }

    // Teste LSE
    l = lse_carrega(l, nome_dados, nome_resultados, &tempo);
    if (l == NULL)
        return 0;
    printf("Tempo de carregamento LSE: %.0ld milisegundos\n", tempo);

    lse_avalia(l, nome_testes, nome_resultados, &tempo);
    printf("Tempo de consulta LSE: %.0ld milisegundos\n", tempo);


    // Teste AVL
    t = avl_carrega(t, nome_dados, nome_resultados, &tempo);
    if (t == NULL)
        return 0;
    printf("Tempo de carregamento AVL: %.0ld milisegundos\n", tempo);
    
    avl_avalia(t, nome_testes, nome_resultados, &tempo);
    printf("Tempo de consulta AVL: %.0ld milisegundos\n", tempo);

    return 0;
}