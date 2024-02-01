#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lse.h"
#include "avl.h"
#include "login.h"
#include "arquivos.h"

FILE *carrega_arq_leitura(char nome[])
{
    FILE *arq1;     //arquivo com os logins
    if (!(arq1 = fopen(nome,"r"))) {     // abertura para leitura
        puts("Erro na leitura de arquivos");
        arq1 = NULL;
    }
    return arq1;
}

FILE *cria_arq_escrita(char nome[])
{
    FILE *arq3;     //arquivo com os resultados
    if (!(arq3 = fopen(nome,"w"))) {     // abertura para escrita
        puts("Erro na criacao de arquivo");
        arq3 = NULL;
    }
    return arq3;
}

FILE *carrega_arq_escrita(char nome[])
{
    FILE *arq3;     //arquivo com os resultados
    if (!(arq3 = fopen(nome,"a"))) {     // abertura para escrita
        puts("Erro na escrita do arquivo de resultados");
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

LSE *lse_carrega(LSE *l, char nome_dados[], char nome_resultados[], float *tempo)
{
    FILE *arq1 = carrega_arq_leitura(nome_dados);
    if (arq1 == NULL)
        return NULL;

    FILE *arq3 = cria_arq_escrita(nome_resultados);
    if (arq3 == NULL)
        return NULL;
    
    fprintf(arq3, "Testes com LSE:\n");

    clock_t time;
    time = clock();

    char linha[TAM_LINHA];

    while (!feof(arq1))
        if (fgets(linha, TAM_LINHA, arq1) != NULL)
            l = lse_insere(l, monta_login(linha));

    time = clock() - time;
    *tempo = (float)time / (CLOCKS_PER_SEC);

    fprintf(arq3, "Tempo de carregamento: %f segundos\n", *tempo);

    fclose(arq1);
    fclose(arq3);
    return l;
}

void lse_avalia(LSE *l, char nome_testes[], char nome_resultados[], float *tempo)
{
    FILE *arq2 = carrega_arq_leitura(nome_testes);
    if (arq2 == NULL)
        return;

    FILE *arq3 = carrega_arq_escrita(nome_resultados);
    if (arq3 == NULL)
        return;

    clock_t time;
    time = clock();

    char linha[TAM_LINHA];

    while (!feof(arq2)) {
        if (fgets(linha, TAM_LINHA, arq2) != NULL) {
            Login login = monta_login(linha);
            if(login.usr < 1000)    // Garante que todas linhas do arquivo de resultados fiquem alinhadas
                fprintf(arq3, "%d\t\t%s\t", login.usr, login.senha);
            else
                fprintf(arq3, "%d\t%s\t", login.usr, login.senha);
            if (strcmp(lse_consulta(l, login.usr), login.senha) == 0)
                fprintf(arq3, "OK\n");
            else
                fprintf(arq3, "ERRO\n");
        }
    }

    time = clock() - time;
    *tempo = (float)time / (CLOCKS_PER_SEC);

    fprintf(arq3, "Tempo de consulta: %f segundos\n", *tempo);
    fclose (arq2);
    fclose (arq3);
    return;
}

AVL *avl_carrega(AVL *t, char nome_dados[], char nome_resultados[], float *tempo)
{
    FILE *arq1 = carrega_arq_leitura(nome_dados);
    if (arq1 == NULL)
        return NULL;

    FILE *arq3 = carrega_arq_escrita(nome_resultados);
    if (arq3 == NULL)
        return NULL;
    
    fprintf(arq3, "\nTestes com AVL:\n");

    clock_t time;
    time = clock();

    char linha[TAM_LINHA];
    int ok = 0;

    while (!feof(arq1))
        if (fgets(linha, TAM_LINHA, arq1) != NULL)
            t = avl_insere(t, monta_login(linha), &ok);

    time = clock() - time;
    *tempo = (float)time / (CLOCKS_PER_SEC);

    fprintf(arq3, "Tempo de carregamento: %f segundos\n", *tempo);
    fclose(arq1);
    fclose(arq3);
    return t;
}

void avl_avalia(AVL *t, char nome_testes[], char nome_resultados[], float *tempo)
{
    FILE *arq2 = carrega_arq_leitura(nome_testes);
    if (arq2 == NULL)
        return;

    FILE *arq3 = carrega_arq_escrita(nome_resultados);
    if (arq3 == NULL)
        return;

    clock_t time;
    time = clock();

    char linha[TAM_LINHA];

    while (!feof(arq2)) {
        if (fgets(linha, TAM_LINHA, arq2) != NULL) {
            Login login = monta_login(linha);
            if(login.usr < 1000)    // Garante que todas linhas do arquivo de resultados fiquem alinhadas
                fprintf(arq3, "%d\t\t%s\t", login.usr, login.senha);
            else
                fprintf(arq3, "%d\t%s\t", login.usr, login.senha);
            if (strcmp(avl_consulta(t, login.usr), login.senha) == 0)
                fprintf(arq3, "OK\n");
            else
                fprintf(arq3, "ERRO\n");
        }
    }
    time = clock() - time;
    *tempo = (float)time / (CLOCKS_PER_SEC);

    fprintf(arq3, "Tempo de consulta: %f segundos\n", *tempo);
    fclose (arq2);
    fclose (arq3);
    return;
}