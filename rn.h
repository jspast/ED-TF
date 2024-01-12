typedef struct  RNnodo RNtree;

struct RNnodo {
  int key;
  int red; /* se red=0 ent�o o nodo � preto */
  struct RNnodo* esq;
  struct RNnodo* dir;
  struct RNnodo* pai;
};

// declarar o nodo NULL
static RNtree* NodoNULL = NULL;

// Defini��es das Fun��es
RNtree* Insere(RNtree* t, int key);
int Consulta(int X, RNtree* T );
RNtree* Remove(RNtree* t, int key);
void Destroi(RNtree* t);

// Fun��es Auxiliares
RNtree* VerificaRN(RNtree* t, int key);
RNtree* RotacaoSimplesEsq(RNtree* t);
RNtree* RotacaoSimplesDir(RNtree* t);
void Desenha(RNtree* t , int nivel);
RNtree* Maior(RNtree* t);
RNtree* Menor(RNtree* t);
