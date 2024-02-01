#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lse.h"
#include "avl.h"
#include "login.h"

#define TAM_ARQUIVOS 32
#define TAM_LINHA (TAM_LOGIN + 2)
#define DADOS "dados.txt"
#define DADOS_ORD "dados_ord.txt"
#define TESTES "testes.txt"
#define RESULTADOS "resultados.txt"

FILE *carrega_arq_leitura(char nome[]);
FILE *cria_arq_escrita(char nome[]);
FILE *carrega_arq_escrita(char nome[]);
Login monta_login(char linha[]);
LSE *lse_carrega(LSE *l, char nome_dados[], char nome_resultados[], float *tempo);
void lse_avalia(LSE *l, char nome_testes[], char nome_resultados[], float *tempo);
AVL *avl_carrega(AVL *t, char nome_dados[], char nome_resultados[], float *tempo);
void avl_avalia(AVL *t, char nome_testes[], char nome_resultados[], float *tempo);

#endif