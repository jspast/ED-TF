#ifndef SENHA_H
#define SENHA_H

#define TAM_USR 10
#define TAM_SENHA 32
#define TAM_LOGIN (TAM_USR + TAM_SENHA)

typedef struct TipoLogin Login;

struct TipoLogin {
    int usr;
    char senha[TAM_SENHA];
};

#endif