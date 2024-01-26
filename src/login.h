#ifndef LOGIN_H
#define LOGIN_H

#define TAM_USR 10
#define TAM_SENHA 32
#define TAM_MAX_SENHA TAM_SENHA + 1
#define TAM_LOGIN (TAM_USR + 1 + TAM_MAX_SENHA)

typedef struct TipoLogin Login;

struct TipoLogin {
    int usr;
    char senha[TAM_MAX_SENHA];
};

char* generate_random_string(unsigned length);
void gera_dados_ord(char nome_dados[], int n);
void shuffle_data(Login* array, int n);
void gera_dados(char nome_dados[], int n);
void gera_testes(char nome_dados[], char nome_testes[], int nd, int n, int p);
char* get_string_for_id(char nome_dados[], int id);

#endif