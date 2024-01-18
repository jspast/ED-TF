#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lse.h"
#include "rn.h"
#include "senha.h"

#define TAM_ARQUIVO 32
#define TAM_LINHA (TAM_LOGIN + 2)

FILE *carrega_arquivo(char nome[]);
Login monta_login(char linha[]);
LSE *lse_carrega(LSE *l, char nome[], double *tempo);

#endif