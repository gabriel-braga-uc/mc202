#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX(a,b) ((a > b)?a:b)
#define TAM_MAX 100

typedef struct NoAVL {  /* Registro que representa n� em �rvore
			   bin�ria */
  int info;
  int bal; /* 0: subarvores esquerda e direita de mesma altura, -1: esquerda mais alta, e +1: direita mais alta. */
  char ip[30];
  struct NoAVL *esq, *dir;
} NoAVL, AVL;
NoAVL *CriaNovoNo(int info, char ip[30]); 
void InsereValor(AVL **ab, int valor, char *mais_alta, char ip[30]); 
void TrataAumentoArvoreDireita(AVL **ab, char *mais_alta);
void RotacaoSimplesEsquerda(AVL **ab);
void AjusteBalancoSimplesInsercao(NoAVL *A, NoAVL *B);
void TrataAumentoArvoreEsquerda(AVL **ab, char *mais_alta);
void AjusteBalancoDuplaInsercao(NoAVL *A, NoAVL *B, NoAVL *C);
void RotacaoSimplesDireita(AVL **ab);
void RotacaoDuplaDireita(AVL **ab);
void RotacaoDuplaEsquerda(AVL **ab);
void VisitaPreOrdem(AVL *ab);
int Altura(AVL *ab);
void RemoveDeFato(AVL **ab, char *mais_baixa);

void AjusteBalancoDuplaRemocao(NoAVL *A, NoAVL *B, NoAVL *C);
void AjusteBalancoRotacaoDireitaSimplesRemocao(NoAVL *A, NoAVL *B, char *mais_baixa);
void AjusteBalancoRotacaoEsquerdaSimplesRemocao(NoAVL *A, NoAVL *B, char *mais_baixa);

char RemoveNoGrau0ou1(AVL **ab, char *mais_baixa);
void SubstituiRemoveMenorSucessor(AVL **ab, AVL **maisesq, char *mais_baixa);
void TrataReducaoArvoreEsquerda(AVL **ab, char *mais_baixa);
void TrataReducaoArvoreDireita(AVL **ab, char *mais_baixa);


void RotacaoSimplesDireita(AVL **ab)
{
  AVL *filho_esq = (*ab)->esq; /* salva filho a esquerda */

  (*ab)->esq     = filho_esq->dir; 
  filho_esq->dir = (*ab); 
  (*ab)          = filho_esq;

}

void AjusteBalancoDuplaInsercao(NoAVL *A, NoAVL *B, NoAVL *C)
{
  switch(C->bal) {
  case -1:
    A->bal = 1;
    B->bal = 0;
    break;
  case 0:
    A->bal = 0;
    B->bal = 0;
    break;
  case +1:
    A->bal =  0;
    B->bal = -1;
    break;
  }
  C->bal = 0;
}

void AjusteBalancoRotacaoDireitaDuplaRemocao(NoAVL *A, NoAVL *B, NoAVL *C)
{
  switch(C->bal) {
  case -1:
    A->bal = 1;
    B->bal = 0;
    break;
  case 0:
    A->bal =  0;
    B->bal =  0;
    break;
  case +1:
    A->bal =  0;
    B->bal = -1;
    break;
  }
  C->bal = 0;
}

void AjusteBalancoRotacaoEsquerdaDuplaRemocao(NoAVL *A, NoAVL *B, NoAVL *C)
{
  switch(C->bal) {
  case -1:
    A->bal = 0;
    B->bal = 1;
    break;
  case 0:
    A->bal = 0;
    B->bal = 0;
    break;
  case +1:
    A->bal = -1;
    B->bal =  0;
    break;
  }
  C->bal = 0;
}

void SubstituiRemoveMenorSucessor(AVL **ab, AVL **maisesq, char *mais_baixa)
{ 
  if ((*maisesq)->esq == NULL){ 
    (*ab)->info = (*maisesq)->info; /* substitui valor */
    RemoveNoGrau0ou1(maisesq,mais_baixa); /* remove no */
  } else { /* busca sucessor */
    SubstituiRemoveMenorSucessor(ab,&((*maisesq)->esq),mais_baixa);
    if (*mais_baixa)
      TrataReducaoArvoreEsquerda(maisesq,mais_baixa); /* corrige balan�o
							 da arvore do
							 pai do
							 sucessor */
  }
}

char RemoveNoGrau0ou1(AVL **ab, char *mais_baixa)
{
  AVL *aux;

  if ((*ab)->esq == NULL){ /* (*ab) eh folha ou tem unico filho */
    aux   = (*ab);
    (*ab) = (*ab)->dir;
    free(aux);
  } else {
    if ((*ab)->dir == NULL){ /* (*ab) eh folha ou tem unico filho */
      aux   = (*ab);
      (*ab) = (*ab)->esq;
      free(aux);
    } else {
      return(0);
    }
  }
  *mais_baixa = 1;
  return(1);
}

void TrataAumentoArvoreEsquerda(AVL **ab, char *mais_alta){
  NoAVL *A,*B,*C;

  A = (*ab); 
  B = (*ab)->esq;
  C = B->dir;

  switch(A->bal) {
  case -1: /* arvore perdeu o balanceamento */
    if (B->bal == -1){ /* rebalancear com rotacao
			  simples a direita, pois o novo
			  no foi inserido a esquerda do
			  filho esquerdo */
      RotacaoSimplesDireita(ab);
      AjusteBalancoSimplesInsercao(A,B);
    }else{ /* entao B->bal == +1, rebalancear com rotacao dupla
	      a direita, pois o novo no foi inserido a direita
	      do filho esquerdo */
      RotacaoDuplaDireita(ab);
      AjusteBalancoDuplaInsercao(A,B,C); 
    }
    (*mais_alta) =  0;
    break;
  case 0: 
    (*ab)->bal   = -1;
    (*mais_alta) =  1; 	

    break;
  case 1:
    (*ab)->bal   =  0;
    (*mais_alta) =  0;
    break;
  }
}

void RotacaoDuplaEsquerda(AVL **ab)
{
  RotacaoSimplesDireita(&(*ab)->dir);
  RotacaoSimplesEsquerda(ab);
}

void RotacaoDuplaDireita(AVL **ab)
{
  RotacaoSimplesEsquerda(&(*ab)->esq);
  RotacaoSimplesDireita(ab);
}

void RotacaoSimplesEsquerda(AVL **ab)
{
  AVL *filho_dir = (*ab)->dir; /* salva filho a direita */

  (*ab)->dir     = filho_dir->esq; 
  filho_dir->esq = (*ab); 
  (*ab)          = filho_dir;

}

void TrataAumentoArvoreDireita(AVL **ab, char *mais_alta)
{
  NoAVL *A,*B,*C;

  A = (*ab);
  B = (*ab)->dir;
  C = B->esq;
  
  switch(A->bal) {
  case 1: /* arvore perdeu o balanceamento */
    if (B->bal == 1){ /* rebalancear com rotacao
			 simples a esquerda, pois o
			 novo no foi inserido a direira
			 do filho direito */
      RotacaoSimplesEsquerda(ab);
      AjusteBalancoSimplesInsercao(A,B); 
    }else{ /* entao B->bal == -1, rebalancear com
	      rotacao dupla a esquerda, pois o novo no foi
	      inserido a esquerda do filho direito */
      RotacaoDuplaEsquerda(ab);
      AjusteBalancoDuplaInsercao(B,A,C); /* troca A e B para usar a
					    mesma funcao */
    }	  
    *mais_alta   = 0;
    break;
  case 0:
    A->bal       = 1;
    (*mais_alta) = 1; 	
    break;
  case -1:
    A->bal       = 0;
    (*mais_alta) = 0; 	
    break;
  }
}

NoAVL *CriaNovoNo(int info, char ipfun[30]) {

  NoAVL *p = (NoAVL *)calloc(1,sizeof(NoAVL));
  p->esq   = NULL;
  p->dir   = NULL;
  p->bal   = 0;
  p->info  = info;
  strcpy(p->ip, ipfun);
  return(p);
  
} /* NovoNo */

void InsereValor(AVL **ab, int valor, char *mais_alta, char ip[30])
{

  if ((*ab) == NULL) { 
    (*ab)      = CriaNovoNo(valor, ip);
    *mais_alta = 1;
  } else { 
    if ((*ab)->info <= valor){ /* insercao a direita */
      InsereValor(&((*ab)->dir),valor,mais_alta, ip);
      if ((*mais_alta)==1){ /* subarvore direita voltou mais alta */
	TrataAumentoArvoreDireita(ab,mais_alta);
      }
    }else{ /* insercao a esquerda */
      InsereValor(&((*ab)->esq),valor,mais_alta, ip);
      if ((*mais_alta)==1){ /* subarvore esquerda voltou mais alta */	
	TrataAumentoArvoreEsquerda(ab,mais_alta);
      }	
    }
  }
}

void AjusteBalancoSimplesInsercao(NoAVL *A, NoAVL *B)
{
  A->bal = B->bal = 0;
}

int Altura(AVL *ab)
{
  if (ab != NULL) 
    return(1 + MAX(Altura(ab->esq),Altura(ab->dir)));
  else
    return(0);
}

void VisitaPreOrdem(AVL *ab)
{
  if (ab != NULL) {
    printf("- %s: %d\n", ab->ip, ab->info);
    VisitaPreOrdem(ab->esq);
    VisitaPreOrdem(ab->dir);
  }
}

void RemoveValor(AVL **ab, int valor, char *mais_baixa)
{
  if ((*ab) != NULL){  
    if ((*ab)->info != valor) {
      if ((*ab)->info <= valor) { 
	RemoveValor(&((*ab)->dir),valor,mais_baixa);
	if ((*mais_baixa)==1)
	  TrataReducaoArvoreDireita(ab,mais_baixa);
      } else {
	RemoveValor(&((*ab)->esq),valor,mais_baixa);
	if ((*mais_baixa)==1)
	  TrataReducaoArvoreEsquerda(ab,mais_baixa);
      }
    } else { /* (*ab)->info == valor */
      RemoveDeFato(ab,mais_baixa);
    }
  }
}

void TrataReducaoArvoreEsquerda(AVL **ab, char *mais_baixa)
{
  NoAVL *A,*B,*C;

  A = (*ab); 
  B = (*ab)->dir;

  switch(A->bal) {
  case  1: /* arvore perdeu o balanceamento */
    if (B->bal >= 0){ /* rebalancear com rotacao
			 simples a esquerda */
      RotacaoSimplesEsquerda(ab);
      AjusteBalancoRotacaoEsquerdaSimplesRemocao(A,B,mais_baixa);
      //printf("%d\n",*mais_baixa);
    }else{ /* entao B->bal == -1, rebalancear com rotacao dupla a
	      esquerda */
      C = B->esq;
      RotacaoDuplaEsquerda(ab);
      AjusteBalancoRotacaoEsquerdaDuplaRemocao(A,B,C);
      (*mais_baixa) =  1;
    }
    break;
  case 0: 
    A->bal        =  1;    
    (*mais_baixa) =  0;
    break;
  case -1:
    A->bal = 0;  
    (*mais_baixa) =  1;
    break;
  }
}

void RemoveDeFato(AVL **ab, char *mais_baixa)
{
  int bal;
  if (RemoveNoGrau0ou1(ab,mais_baixa)==0){ /* Remove no de grau 2 */
    bal = (*ab)->bal; /* salva balanco */
    SubstituiRemoveMenorSucessor(ab,&((*ab)->dir),mais_baixa);
    (*ab)->bal = bal; /* recupera balanco */	
    if (*mais_baixa)
      TrataReducaoArvoreDireita(ab,mais_baixa); /* corrige balan�o
						   da arvore direita
						   apos substituicao
						   pelo sucessor */
  }
}

void TrataReducaoArvoreDireita(AVL **ab, char *mais_baixa)
{
  NoAVL *A,*B,*C;

  A = (*ab); 
  B = (*ab)->esq;

  switch(A->bal) {
  case  -1: /* arvore perdeu o balanceamento */
    if (B->bal <= 0){ /* rebalancear com rotacao
			 simples a direita */
      RotacaoSimplesDireita(ab);
      AjusteBalancoRotacaoDireitaSimplesRemocao(A,B,mais_baixa); 
    }else{ /* B->bal == 1, rebalancear com rotacao dupla a direita */
      C = B->dir;
      RotacaoDuplaDireita(ab);
      AjusteBalancoRotacaoDireitaDuplaRemocao(A,B,C);
      (*mais_baixa) =  1;
    }
    break;
  case 0: 
    (*ab)->bal    =  -1;
    (*mais_baixa) =   0;
    break;
  case 1:
    (*ab)->bal    =  0;
    (*mais_baixa) =  1;
    break;
  }
}

void AjusteBalancoRotacaoDireitaSimplesRemocao(NoAVL *A, NoAVL *B, char *mais_baixa)
{
  if (B->bal == -1){ 
    A->bal =  0;
    B->bal =  0;
    *mais_baixa = 1;
  } else { /* B->bal == 0 */
    A->bal = -1;
    B->bal =  1;
    *mais_baixa = 0;
  }
}

void AjusteBalancoRotacaoEsquerdaSimplesRemocao(NoAVL *A, NoAVL *B, char *mais_baixa)
{
  if (B->bal == 1){ 
    A->bal =  0;
    B->bal =  0;
    *mais_baixa = 1;
  } else { /* B->bal == 0 */
    A->bal =  1;
    B->bal = -1;
    *mais_baixa = 0;
  }
}


int main(int argc,char *argv[]){
    char t;
    char q;
    NoAVL * ab;
    FILE * fp;
    
    fp = fopen(argv[1], "r");
    if(fp != NULL){
      char * n = (char*)calloc(52, sizeof(char));
    fgets(n, 52, fp);
    int n1 = atoi(n);
  //  free(n);
    for(int i = 1; i <= n1; i++){
        char * n = (char*)calloc(52, sizeof(char));
        fgets(n, 52, fp);
        char * part1 = strtok(n, " ");
        char * part2 = strtok(NULL, " ");
        int n4 = atoi(part2);
        if(i == 1){
            ab = CriaNovoNo(n4, part1);
        } else{
            InsereValor(&ab, n4, &t, part1);
        }
       // free(n);
     //   free(part1);
      //  free(part2);
    }
    
    int maxcaminho1 = 1 + Altura(ab->dir) + Altura(ab->esq);
    printf("[INFO] Apos construcao:\n");
    VisitaPreOrdem(ab);
    if(Altura(ab)*12 != n1){
        printf("Arvore nao esta cheia\n");
    } else {
        printf("Arvore nao esta cheia\n");
    }
    printf("A rota mais longa possivel passa por %d nos\n", maxcaminho1);
//
    fp = fopen(argv[2], "r");
    char * n3 = (char*)calloc(52, sizeof(char));
    fgets(n3, 52, fp);
    int n2 = atoi(n3);
    for(int i = 1; i <= n2; i++){
        char * n = (char*)calloc(52, sizeof(char));
        fgets(n, 52, fp);
        char * part1 = strtok(n, " ");
        char * part2 = strtok(NULL, " ");
        char * part3 = strtok(NULL, " ");
        if(atoi(part1) == -1){
            RemoveValor(&ab, atoi(part3), &q);
        } else {
            InsereValor(&ab, atoi(part3), &t, part2);
        }
        //free(n); 
 //       free(part1); 
  //      free(part2); 
   //     free(part3);
    }
    fclose(fp);
    printf("\n[INFO] Apos atualizacao:\n");
    VisitaPreOrdem(ab);
    if(Altura(ab)*12 != n1){
        printf("Arvore nao esta cheia\n");
    } else {
        printf("Arvore nao esta cheia\n");
    }
    int maxcaminho2 = 1 + Altura(ab->dir) + Altura(ab->esq);
    printf("A rota mais longa possivel passa por %d nos\n", maxcaminho2);
    }
    return 0;
}