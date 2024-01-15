#include "senha.h"

typedef struct TipoPtNo PtNo;

struct TipoPtNo {
    InfoNo info;
    PtNo *prox;
};

PtNo *lse_cria_lista(void);
PtNo *lse_insere(PtNo *l, InfoNo dados);
void lse_imprime(PtNo *l);
char *lse_consulta(PtNo *l, int num);
PtNo *lse_remove(PtNo *l, int num);
PtNo *lse_destroi(PtNo *l);