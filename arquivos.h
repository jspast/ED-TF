#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lse.h"
#include "rn.h"
#include "senha.h"

FILE *carrega_arquivo(char nome[]);
Login monta_login(char linha[]);
LSE *lse_carrega(LSE *l, char nome[], double *tempo);

#endif