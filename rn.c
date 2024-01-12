#include <stdio.h>
#include <stdlib.h>
#include "rn.h"

RNtree* Insere(RNtree* t, int key) 
{
            RNtree* x = t;
            
            if(t == NULL)  {
                 // aloca��o de espa�o
                 NodoNULL = (RNtree*) malloc(sizeof(RNtree));
                 x = (RNtree*) malloc(sizeof(RNtree));
                 //inicializa��es
                 // NULL
                 NodoNULL->red = 0; // null � preto;
                 NodoNULL->esq = NodoNULL;
                 NodoNULL->dir = NodoNULL;
                 NodoNULL->key = 32000;
                 NodoNULL->pai = NodoNULL;
                 // Raiz
                 x->key = key;
                 x->esq = x->dir = NodoNULL;
                 x->red = 0;
                 x->pai = NodoNULL;
                 return x;
            }
           
            RNtree* p= x->pai; // pai
            RNtree* v= p->pai; // vo
            

            while( x != NodoNULL )  /* desce na �rvore */
            {
              v = p; p = x;
              if( key < x->key ) x = x->esq;
              else x = x->dir;
            };
           
            if(x != NodoNULL) return t; // Nodo Ja Existe
                
            x = (RNtree*) malloc(sizeof(RNtree));
            x->key = key;
            x->esq = x->dir = NodoNULL;
            x->pai = p;
            x->red = 1;
            
            if( key < p->key)
                p->esq = x;
            else
                p->dir = x;
            
            // Nodo Foi Inserido mas pode ter modificado as regras ent�o temos que verificar.

            return VerificaRN(t, key);
};

int Consulta(int X, RNtree* T )
{
  if( T == NodoNULL ) return 0;
  if(X == T->key) return 1;
  else if( X < T->key ) return Consulta( X, T->esq );
       else if( X > T->key ) return Consulta( X, T->dir );
            else return 0;
};
     
        
RNtree* Remove(RNtree* t, int key)
{
  RNtree* x = t;
  RNtree* y;
  RNtree* p = x->pai;
  RNtree* v = p->pai;
  
  NodoNULL->key = key;
  while(x->key != key)  /* desce na �rvore */
  {
   v = p; p = x;
   if( key < x->key ) x = x->esq;
   else x = x->dir;
  };
  if(x == NodoNULL) return t;
  if(x->red) // nodo � vermelho
  {
    if((x->esq == NodoNULL) && (x->dir == NodoNULL)) // nodo folha
    {
      if(x->key < p->key) p->esq = NodoNULL;
      else p->dir = NodoNULL;
      free(x);
      return t;
    };
    if(x->key < p->key) 
    {
     y = Menor(t->dir);
     p->esq = y;
     y->esq = x->esq;
     y->dir = x->dir;
     free(x);
    } else
      {
        y = Maior(t->esq);
        p->dir = y;
        y->dir = x->dir;
        y->esq = x->esq;
        free(x);
      }; 
  }
  else // nodo � preto
  {
    if(x->key < p->key) // filho a esquerda
    {
      if((p->dir->red == 0) && ((x->esq->red == 0) && (x->dir->red == 0))) // irm�o preto e dois filhos pretos
      {
        if(p->red) p->red = 0; // troca a cor do pai 
        else p->red = 1;
        p->dir->red = 1; // troca a cor do irmao 
        y = Menor(t->dir);
        p->esq = y;
        y->esq = x->esq;
        y->dir = x->dir;
        free(x);
      } else if ((p->dir->red == 0) && ((x->esq->red != 0) || (x->dir->red != 0)))
        {
         y = Menor(t->dir);
         p->esq = y;
         y->esq = x->esq;
         y->dir = x->dir;
         RotacaoSimplesDir(p);
         if(x->red) x->red = 0; // troca a cor do nodo 
         else x->red = 1;
         free(x);
        }else // irm�o vermelho
          {
            if(p->dir->red) 
            {
               y = Menor(t->dir);
               p->esq = y;
               y->esq = x->esq;
               y->dir = x->dir;
               RotacaoSimplesDir(p);
               free(x);
            };
          };
    } else // filho a direita
      {
      if((p->esq->red == 0) && ((x->esq->red == 0) && (x->dir->red == 0))) // irm�o preto e dois filhos pretos
      {
        if(p->red) p->red = 0; // troca a cor do pai 
        else p->red = 1;
        p->dir->red = 1; // troca a cor do irmao 
        y = Maior(t->esq);
        p->dir = y;
        y->dir = x->dir;
        y->esq = x->esq;
        free(x);
      } else if ((p->dir->red == 0) && ((x->esq->red != 0) || (x->dir->red != 0)))
        {
         y = Maior(t->esq);
        p->dir = y;
        y->dir = x->dir;
        y->esq = x->esq;
         RotacaoSimplesEsq(p);
         if(x->red) x->red = 0; // troca a cor do nodo 
         else x->red = 1;
         free(x);
        } else // irm�o vermelho
          {
            if(p->esq->red) 
            {
               y = Maior(t->esq);
               p->dir = y;
               y->dir = x->dir;
               y->esq = x->esq;
               RotacaoSimplesEsq(p);
               free(x);
            };
          };
    };
  };
  VerificaRN(t,key); 
  return t;
};

void Destroi(RNtree* t)
{
  
};

RNtree* VerificaRN(RNtree* t,int key)
{
  RNtree* x = t;
  RNtree* p = x->pai;
  RNtree* v = p->pai;
  while( x->key != key )  /* desce na �rvore */
  {
    v = p; p = x;
    if( key < x->key ) x = x->esq;
    else x = x->dir;
  };
  // x cont�m o novo e p o pai do novo.
  
  /* if(p->red == 0) - caso 1
     insere vermelho mas j� t� ent�o n�o precisa modificar.
  */
  // caso 2
  if(p->red)
  {
    if( v != NodoNULL) // pai n�o � raiz
    {
      if( p-> key < v->key) // p � filho a esquerda
      {
        // Caso 2.1
        if(v->dir->red) // tio � vermelho
        {
          v->dir->red =0; // tio vira preto
          if(p->red) p->red = 0; // troca a cor do pai 
          else p->red = 1;
          if(v->pai == NodoNULL) // av� � raiz
          {
            p->dir->red = 0;
            p->red = 0;
            v->red = 0;
          };         
        } else 
          {
            if((x->key < p->key) && (p->key < v->key)) // Caso 2.2(A)
            {
              // rotacao a direita
              RotacaoSimplesDir(v);
              if(p->red) p->red = 0; // troca a cor do pai 
              else p->red = 1;
              if(v->red) v->red = 0; // troca a cor do vo 
              else v->red = 1;
            } else
              {
                if((x->key > p->key) && (p->key > v->key)) // Caso 2.2(B)
                {
                  RotacaoSimplesEsq(v);
                  if(p->red) p->red = 0; // troca a cor do pai 
                  else p->red = 1;
                  if(v->red) v->red = 0; // troca a cor do vo 
                  else v->red = 1;
                } else 
                  {
                    if(p->key < v->key)  // Caso 2.2(C)
                    {
                      RotacaoSimplesEsq(p);
                      RotacaoSimplesDir(v); // rotacao Dupla a direita
                      if(x->red) x->red = 0; // troca a cor do novo 
                      else x->red = 1;
                      if(v->red) v->red = 0; // troca a cor do vo 
                      else v->red = 1;
                    } else        // Caso 2.2(D)
                      {
                        RotacaoSimplesDir(p);
                        RotacaoSimplesEsq(v); // rotacao Dupla a esquerda
                        if(x->red) x->red = 0; // troca a cor do novo 
                        else x->red = 1;
                        if(v->red) v->red = 0; // troca a cor do vo 
                        else v->red = 1;
                      };   
                  };
              };
          };
      } else 
        {
        // Caso 2.1
        if(v->esq->red) // tio � vermelho
        {
          v->esq->red =0; // tio vira preto
          if(p->red) p->red = 0; // troca a cor do pai 
          else p->red = 1;
          if(v->pai == NodoNULL) // av� � raiz
          {
            p->dir->red = 0;
            p->red = 0;
            v->red = 0;
          };         
        } else 
          {
            if((x->key < p->key) && (p->key < v->key)) // Caso 2.2(A)
            {
              // rotacao a direita
              RotacaoSimplesDir(v);
              if(p->red) p->red = 0; // troca a cor do pai 
              else p->red = 1;
              if(v->red) v->red = 0; // troca a cor do vo 
              else v->red = 1;
            } else
              {
                if((x->key > p->key) && (p->key > v->key)) // Caso 2.2(B)
                {
                  RotacaoSimplesEsq(v); // --- aqui
                  if(p->red) p->red = 0; // troca a cor do pai 
                  else p->red = 1;
                  if(v->red) v->red = 0; // troca a cor do vo 
                  else v->red = 1;
                } else 
                  {
                    if(p->key < v->key)  // Caso 2.2(C)
                    {
                      RotacaoSimplesEsq(p);
                      RotacaoSimplesDir(v); // rotacao Dupla a direita
                      if(x->red) x->red = 0; // troca a cor do novo 
                      else x->red = 1;
                      if(v->red) v->red = 0; // troca a cor do vo 
                      else v->red = 1;
                    } else        // Caso 2.2(D)
                      {
                        RotacaoSimplesDir(p);
                        RotacaoSimplesEsq(v); // rotacao Dupla a esquerda
                        if(x->red) x->red = 0; // troca a cor do novo 
                        else x->red = 1;
                        if(v->red) v->red = 0; // troca a cor do vo 
                        else v->red = 1;
                      };   
                  };
              };
          };
      };
    };
  }; 
  t->red = 0;
  x->red = 1;
  return t;
};
        
RNtree* RotacaoSimplesDir( RNtree* t )
        {
            RNtree* aux;

            aux = t->esq;
            t->esq = aux->dir;
            aux->dir = t;

            return aux;  /* nova raiz */
        };

        
RNtree* RotacaoSimplesEsq( RNtree* t )
        {
            RNtree* aux;

            aux = t->dir;
            t->dir = aux->esq;
            aux->esq = t;

            return aux;   /* nova raiz */
        };

void Desenha(RNtree* t , int nivel)
{
int x;

 if (t !=NodoNULL)
 {
   for (x=1; x<=nivel; x++)
      printf("=");
   if(t->red) printf("%d Red\n", t->key);
   else printf("%d Black\n", t->key);
   if (t->esq != NodoNULL) Desenha(t->esq, (nivel+1));
   if (t->dir != NodoNULL) Desenha(t->dir, (nivel+1));
 }
 else printf("Arvore Vazia\n");
};


RNtree* Maior(RNtree* t) 
{
 while (t != NodoNULL) t = t->dir;
 return t->pai;
};


RNtree* Menor(RNtree* t)
{
  while (t != NodoNULL) t = t->esq;
  return t->pai;
};
