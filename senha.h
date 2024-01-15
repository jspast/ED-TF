#ifndef SENHA_H
#define SENHA_H

typedef struct TipoLogin Login;

struct TipoLogin {
    int usr;
    char senha[32];
};

#endif