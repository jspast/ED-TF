typedef struct TipoInfoNo InfoNo;
typedef struct TipoPtNo PtNo;

struct TipoInfoNo {
    int num;
    char senha[32];
};

struct TipoPtNo {
    InfoNo info;
    PtNo *prox;
};

PtNo *lse_cria_lista(void);
PtNo *lse_insere(PtNo *l, InfoNo dados);
void lse_imprime(PtNo *l);
PtNo *lse_remove(PtNo *l, int num);
PtNo *lse_destroi(PtNo *l);