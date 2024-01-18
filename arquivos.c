#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lse.h"
#include "rn.h"
#include "senha.h"
#include "arquivos.h"

FILE *carrega_arquivo(char nome[])
{
    FILE *arq1;     //arquivo com os logins
    if (!(arq1 = fopen(nome,"r"))) {     // abertura para leitura
        printf("Erro na abertura de arquivos\n");
        arq1 = NULL;
    }
    return arq1;
}

FILE *carrega_resultados1(char nome[])
{
    FILE *arq3;     //arquivo com os resultados
    if (!(arq3 = fopen(nome,"w"))) {     // abertura para escrita
        printf("Erro na abertura de arquivos\n");
        arq3 = NULL;
    }
    return arq3;
}

FILE *carrega_resultados2(char nome[])
{
    FILE *arq3;     //arquivo com os resultados
    if (!(arq3 = fopen(nome,"a"))) {     // abertura para escrita
        printf("Erro na abertura de arquivos\n");
        arq3 = NULL;
    }
    return arq3;
}

Login monta_login(char linha[])
{
    Login login;

    login.usr = atoi(strtok(linha,","));
    strcpy(login.senha, strtok(NULL,","));
    login.senha[strcspn(login.senha, "\r\n")] = 0;  // revove o "\n" no final

    return login;
}

LSE *lse_carrega(LSE *l, char nome[], double *tempo)
{
    FILE *arq1 = carrega_arquivo(nome);
    if (arq1 == NULL)
        return NULL;

    time_t tempo_inicio, tempo_fim;
    time(&tempo_inicio);

    char linha[TAM_LINHA];

    while (!feof(arq1))
        if (fgets(linha, TAM_LINHA, arq1) != NULL)
            l = lse_insere(l, monta_login(linha));

    time(&tempo_fim);
    *tempo = difftime(tempo_fim, tempo_inicio);
    fclose(arq1);
    return l;
}

RNtree *rn_carrega(RNtree *t, char nome[], double *tempo)
{
    FILE *arq1 = carrega_arquivo(nome);
    if (arq1 == NULL)
        return NULL;

    time_t tempo_inicio, tempo_fim;
    time(&tempo_inicio);

    char linha[TAM_LINHA];

    while (!feof(arq1))
        if (fgets(linha, TAM_LINHA, arq1) != NULL)
            t = rn_insere(t, monta_login(linha));

    time(&tempo_fim);
    *tempo = difftime(tempo_fim, tempo_inicio);
    fclose(arq1);
    return t;
}

void lse_avalia(LSE *l, char nome_testes[], char nome_resultados[], double *tempo)
{
    FILE *arq2 = carrega_arquivo(nome_testes);
    if (arq2 == NULL)
        return;

    FILE *arq3 = carrega_resultados1(nome_resultados);
    if (arq3 == NULL)
        return;

    time_t tempo_inicio, tempo_fim;
    time(&tempo_inicio);

    char linha[TAM_LINHA];

    fprintf(arq3, "Testes com LSE:\n");
    while (!feof(arq2)) {
        if (fgets(linha, TAM_LINHA, arq2) != NULL) {
            Login login = monta_login(linha);
            fprintf(arq3, "%d\t%s\t", login.usr, login.senha);
            if (strcmp(lse_consulta(l, login.usr), login.senha) == 0)
                fprintf(arq3, "OK\n");
            else
                fprintf(arq3, "ERRO\n");
        }
    }

    time(&tempo_fim);
    *tempo = difftime(tempo_fim, tempo_inicio);
    fprintf(arq3, "Tempo de consulta: %.0lf segundos\n", *tempo);
    fclose (arq2);
    fclose (arq3);
    return;
}

void rn_avalia(RNtree *t, char nome_testes[], char nome_resultados[], double *tempo)
{
    FILE *arq2 = carrega_arquivo(nome_testes);
    if (arq2 == NULL)
        return;

    FILE *arq3 = carrega_resultados2(nome_resultados);
    if (arq3 == NULL)
        return;

    time_t tempo_inicio, tempo_fim;
    time(&tempo_inicio);

    char linha[TAM_LINHA];

    fprintf(arq3, "\nTestes com RN:\n");
    while (!feof(arq2)) {
        if (fgets(linha, TAM_LINHA, arq2) != NULL) {
            Login login = monta_login(linha);
            fprintf(arq3, "%d\t%s\t", login.usr, login.senha);
            if (strcmp(rn_consulta(t, login.usr), login.senha) == 0)
                fprintf(arq3, "OK\n");
            else
                fprintf(arq3, "ERRO\n");
        }
    }
    time(&tempo_fim);
    *tempo = difftime(tempo_fim, tempo_inicio);
    fprintf(arq3, "Tempo de consulta: %.0lf segundos\n", *tempo);
    fclose (arq2);
    fclose (arq3);
    return;
}