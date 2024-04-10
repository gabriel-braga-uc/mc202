#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

/* Cria matriz de inteiros com nlin x ncol elementos */

int **CriaMatrizInt(int nlin, int ncol)
{
  int **m = (int **)calloc(nlin,sizeof(int *));
  
  for (int l=0; l < nlin; l++)
    m[l] = (int *)calloc(ncol,sizeof(int));
  return(m);
}

/* Libera a memória no heap, reinicializando o ponteiro para NULL */

void DestroiMatrizInt(int ***m, int nlin)
{
  if ((*m) != NULL){
    for (int l=0; l < nlin; l++)
      free((*m)[l]);
    free(*m);
    *m = NULL;
  }
}

/* Gera número real aleatório em [min,max] */

double NumeroAleatorio(float min, float max) {
  double d;
  d = ((double) rand()) / (double) RAND_MAX;
  return(min + d * (max - min));
}

/* Cria matriz com n números aleatórios em [min,max] */

int **MatrizIntAleatorio(int nlin, int ncol, int min, int max)
{
  int **m = CriaMatrizInt(nlin,ncol);
  for(int l=0; l < nlin; l++){
    for(int c=0; c < ncol; c++)
      m[l][c] = (int) NumeroAleatorio(min,max);
  }
  return(m);
}
  
/* Imprime matriz */

void ImprimeMatrizInt(int **m, int nlin, int ncol)
{
  for(int l=0; l < nlin; l++){
    for(int c=0; c < ncol; c++)
      printf("%03d ",m[l][c]);
    printf("\n");
  }
}

int main()
{
  int **m = NULL, nlin = 3, ncol = 4;
  
  srand(time(NULL));
  m = MatrizIntAleatorio(nlin, ncol,0,100);
  ImprimeMatrizInt(m,nlin,ncol);
  DestroiMatrizInt(&m, nlin);
  
  return(0);
}
  
