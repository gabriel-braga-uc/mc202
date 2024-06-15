#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i+1)
#define FilhoDireito(i) (2*i+2)

typedef enum{false,true} Boolean;

typedef struct _heap {
  int *info;              /* informação e prioridade ao mesmo tempo */
  int  nelems, maxsize;   /* número de elementos no heap e o tamanho do vetor */
  char ** ip;
  float *lat;
} Heap;

Heap   *CriaHeap(int maxsize);
void    DestroiHeap(Heap **H);
void    InsereHeap(Heap *H, int info, char * ip, float lat);
int     RemoveHeap(Heap *H);
Boolean HeapCheio(Heap *H);
Boolean HeapVazio(Heap *H);
void    ImprimeHeap(Heap *H, int indice, int nivel);
void    ConstroiHeap1(Heap *H);
void    ConstroiHeap2(Heap *H);
void    HeapSort(Heap *H);
void    SobeHeap(Heap *H, int i);
void    DesceHeapRecursivo(Heap *H, int i);
void    DesceHeap(Heap *H, int i);
void    Troca(int *x, int *y);


Heap *CriaHeap(int maxsize)
{
  Heap *H = (Heap *)calloc(1,sizeof(Heap));
  
  H->maxsize = maxsize;
  H->nelems  = 0;
  H->info    = (int *)calloc(H->maxsize,sizeof(int));
  H->ip      = (char**)calloc(H->maxsize, sizeof(char*));
  H->lat      = (float *)calloc(H->maxsize, sizeof(float));
  return(H);
}

void DestroiHeap(Heap **H)
{
  if (*H != NULL){
    free((*H)->info);
    free(*H);
    *H = NULL;
  }
}

void Troca(int *x, int *y)
{ 
  int aux;

  aux = *x;  *x   = *y;  *y   = aux;

}

/*   O (logn) */

void DesceHeapRecursivo (Heap *H, int i)
{ 
 int maior,esq,dir;

 esq = FilhoEsquerdo(i);
 dir = FilhoDireito(i);

 if ((esq < H->nelems)&&(H->info[esq] > H->info[i]))
   maior = esq;
 else
   maior = i;

 if ((dir < H->nelems)&&(H->info[dir] > H->info[maior]))
   maior = dir;

 if (maior != i){
   Troca(&H->info[i],&H->info[maior]);
   DesceHeapRecursivo(H,maior);		
 }

}

/*   O (logn) */

void DesceHeap (Heap *H, int i)
{ 
 int     maior,esq,dir;
 Boolean continua=true;

 while (continua) { 

   esq = FilhoEsquerdo(i);
   dir = FilhoDireito(i);

   if ((esq < H->nelems)&&(H->info[esq] > H->info[i]))
     maior = esq;
   else
     maior = i;

   if ((dir < H->nelems)&&(H->info[dir] > H->info[maior]))
     maior = dir;

   if (maior != i){
     Troca(&H->info[i],&H->info[maior]);
     i = maior;
   }else
     continua = false;
 }

}

/* O (logn) - Iterativo */

void SobeHeap(Heap *H, int i)
{
  int pai;

  pai = Pai(i);
  
  while ((pai >= 0) && (H->info[pai] < H->info[i])){
    Troca(&H->info[i],&H->info[pai]);
    i   = pai;
    pai = Pai(i);
  }

}

Boolean HeapCheio(Heap *H)
{
  if (H->nelems >= H->maxsize)
    return true;
  else
    return false;
}

Boolean HeapVazio(Heap *H)
{
  if (H->nelems <= 0)
    return true;
  else
    return false;
}

void ImprimeHeap(Heap *H, int indice, int nivel)
{ 
  int i;

  if (indice < H->nelems){ 
    ImprimeHeap(H,FilhoDireito(indice),nivel+1);
    for (i=0; i < nivel; i++) 
      printf("   ");
    printf("%03d",H->info[indice]);
    for (i=0; i <= (int)log2(H->nelems)-nivel; i++) 
      printf("---");
    printf("\n");
    ImprimeHeap(H,FilhoEsquerdo(indice),nivel+1);
  }
}


/*   O (logn) */

void InsereHeap(Heap *H, int info, char * ip, float lat) 
{ 
  if (!HeapCheio(H)) {
    H->nelems += 1;
    H->info[H->nelems-1] = info;
    H->lat[H->nelems-1] = lat;
    H->ip[H->nelems-1] = ip;
    SobeHeap(H,H->nelems-1);
  }

}

/*   O (logn) */

int RemoveHeap(Heap *H)
{
  int info;

  if (!HeapVazio(H)) {
    info        = H->info[0];
    Troca(&(H->info[0]),&(H->info[H->nelems-1]));
    H->nelems--;
    DesceHeap(H,0);
  }

  return(info);
}

/* O(nlogn): A cada iteracao garante um heap do indice 0 ate o indice
   i, para i = 1, 2, ..., nelems-1 */

void ConstroiHeap1(Heap *H)
{
  int i;
  for(i=1;i<H->nelems;i++) { 
    SobeHeap(H,i); 
  }
}

/* O(n): a cada iteraçao garante o heap a partir do nivel i
   (direita e depois esquerda) para i = h-1 ate 0 */

void ConstroiHeap2 (Heap *H)
{ 
  int i,n;

  n = Pai(H->nelems-1);
  for (i=n; i >= 0; i--){ 
    DesceHeap(H,i); 
  }
}


/* Heapsort O(nlog(n)): Constrói o heap, caso os elementos em H não
   formem um heap binário, depois aplica as remoções de todos os
   elementos, sabendo que os elementos removidos ficam na verdade no
   vetor do heap em ordem crescente. Por fim, retoma-se o tamanho
   original do vetor. */

void HeapSort(Heap *H)
{
 int i,n = H->nelems;

 ConstroiHeap2(H);
 for (i=0; i < n; i++)
   RemoveHeap(H);
 H->nelems = n;
 
}

int main(int argc,char * argv[]){
    char * tempstr = (char*)calloc(32, sizeof(char));
    int nips;
    FILE * fp;
    fp = fopen(argv[1], "r");
    nips = atoi(fgets(tempstr, 32, fp));
    free(tempstr);
    Heap * p = CriaHeap(nips);
    printf("\n%d\n", nips);
    for(int i = 1; i <= nips; i++){
        char * tempstr = (char*)calloc(32, sizeof(char));
        tempstr = fgets(tempstr, 32, fp);
        char * ip = strtok(tempstr, " ");
        char * prio = strtok(NULL, " ");
        char * lat = strtok(NULL, " ");
        InsereHeap(p, atoi(prio), ip, strtof(lat, NULL));
        printf("%s %d %s", ip, atoi(prio), lat);
        free(ip); free(prio); free(lat);
        printf("\n%d\n", i);
    }
    printf("%s\n", p->ip[0]);
    printf("%s\n", p->ip[1]);
    printf("%s\n", p->ip[2]);
    printf("%s\n", p->ip[3]);
    printf("%s\n", p->ip[4]);
    printf("%s\n", p->ip[5]);
    printf("%s\n", p->ip[6]);
    printf("%s\n", p->ip[7]);
    printf("%s\n", p->ip[8]);
    printf("%s\n", p->ip[9]);
    printf("%s\n", p->ip[10]);
    printf("%s\n", p->ip[11]);
    fclose(fp);
    return 0;
}