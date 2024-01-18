#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lse.h"
#include "rn.h"
#include "senha.h"

#define TAM_ARQUIVOS 32
#define TAM_LINHA (TAM_LOGIN + 2)
#define DADOS "dados.txt"
#define TESTES "testes.txt"
#define RESULTADOS "resultados.txt"

FILE *carrega_arquivo(char nome[]);
FILE *carrega_resultados2(char nome[]);
FILE *carrega_resultados1(char nome[]);
Login monta_login(char linha[]);
LSE *lse_carrega(LSE *l, char nome[], double *tempo);
RNtree *rn_carrega(RNtree *t, char nome[], double *tempo);
void lse_avalia(LSE *l, char nome_testes[], char nome_resultados[], double *tempo);
void rn_avalia(RNtree *t, char nome_testes[], char nome_resultados[], double *tempo);

#endif