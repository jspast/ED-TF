typedef struct TipoInfoNo InfoNo;
typedef struct TipoPtNo PtNo;

struct TipoInfoNo{
       char titulo[20];
       char distr[20];
       char diretor[20];
       };

struct TipoPtNo{
       InfoNo info;
       PtNo *prox;
       };

PtNo* cria_lista(void);
PtNo* insere_ord (PtNo *l, InfoNo dados);
void imprime(PtNo* l);
PtNo* remover(PtNo* l, char titulo[]);
PtNo* destroi(PtNo* l);
