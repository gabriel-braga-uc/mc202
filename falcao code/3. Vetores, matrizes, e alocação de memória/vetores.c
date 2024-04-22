#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>


/* Cria vetor de reais do tipo float com n elementos */

float *CriaVetorFloat(int n)
{
  float *v = (float *)calloc(n,sizeof(float));
  return(v);
}

/* Libera a memória no heap, reinicializando o ponteiro para NULL */

void DestroiVetorFloat(float **v)
{
  if ((*v) != NULL){
    free(*v);
    *v = NULL;
  }
}

/* Gera número real aleatório em [min,max] */

double NumeroAleatorio(float min, float max) {
  double d;
  d = ((double) rand()) / (double) RAND_MAX;
  return(min + d * (max - min));
}

/* Cria vetor com n números aleatórios em [min,max] */

float *VetorFloatAleatorio(int n, float min, float max)
{
  float *v = CriaVetorFloat(n);
  for (int i=0; i < n; i++)
    v[i] = (float) NumeroAleatorio(min,max);
  return(v);
}

/* Imprime vetor */

void ImprimeVetorFloat(float *v, int n)
{
  for(int i=0; i < n; i++)
    printf("%.2f ",v[i]);
  printf("\n");
}

int main()
{
  float *v = NULL;
  int n    = 5;

  srand(time(NULL));
  v = VetorFloatAleatorio(n,0,100);
  ImprimeVetorFloat(v,n);
  DestroiVetorFloat(&v);
  
  return(0);
}
  
