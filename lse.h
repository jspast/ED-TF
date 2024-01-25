#ifndef LSE_H
#define LSE_H

#include "login.h"

typedef struct LSEnodo LSE;

struct LSEnodo {
    Login info;
    LSE *prox;
};

LSE *lse_cria_lista(void);
LSE *lse_insere(LSE *l, Login dados);
void lse_imprime(LSE *l);
char *lse_consulta(LSE *l, int usr);
LSE *lse_remove(LSE *l, int usr);
LSE *lse_destroi(LSE *l);

#endif