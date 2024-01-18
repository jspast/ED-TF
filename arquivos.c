#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lse.h"
#include "rn.h"
#include "senha.h"

#define TAM_LINHA (TAM_LOGIN + 2)

FILE *carrega_arquivo(char nome[])
{
    FILE *arq1;     //arquivo com os logins
    if(!(arq1 = fopen(nome,"r"))) {     // abertura para leitura
        printf("Erro na abertura do arquivo da base de dados\n");
        arq1 = NULL;
    }
    return arq1;
}

Login monta_login(char linha[])
{
    int usr;
    char senha[TAM_SENHA];

    usr = atoi(strtok(linha,","));
    strcpy(senha, strtok(NULL,","));

    return (Login){usr, {senha[TAM_SENHA]}};
}

LSE *lse_carrega(LSE *l, char nome[], double *tempo)
{
    FILE *arq1 = carrega_arquivo(nome);
    if (arq1 == NULL)
        return 0;

    time_t tempo_inicio, tempo_fim;
    time(&tempo_inicio);

    char linha[TAM_LINHA];
    l = lse_cria_lista();

    while (!feof(arq1))
        if(fgets(linha, TAM_LINHA, arq1) != NULL)
            l = lse_insere(l, monta_login(linha));

    time(&tempo_fim);
    *tempo = difftime(tempo_fim, tempo_inicio);
    fclose (arq1);
    return l;
}