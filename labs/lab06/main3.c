#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i)
#define FilhoDireito(i) (2*i+1)

typedef struct _heap {
  int *info;              /* informação e prioridade ao mesmo tempo */
  float *lat;
  char ** ip;
  int  nelems, maxsize;   /* número de elementos no heap e o tamanho do vetor */
} Heap;

Heap *CriaHeap(int maxsize);
void ImprimeHeap(Heap *H, int indice, int nivel);

void ImprimeHeap(Heap *H, int indice, int nivel)
{ 
  int i;

  if (indice <= H->nelems){ 
    ImprimeHeap(H,FilhoDireito(indice),nivel+1);
    printf("         ");
    for (i=0; i < nivel; i++) 
      printf("         ");
    printf("[%d](%s)[%.2f]", H->info[indice], H->ip[indice], H->lat[indice]);
    for (i=0; i+1 <= (int)log2(H->nelems)-nivel; i++) 
      printf("---");
    printf("\n");
    ImprimeHeap(H,FilhoEsquerdo(indice),nivel+1);
  }
}
Heap *CriaHeap(int maxsize)
{
    Heap *H = (Heap *)calloc(1,sizeof(Heap));

    H->maxsize = maxsize;
    H->nelems  = 0;
    H->info    = (int *)calloc(H->maxsize, sizeof(int));
    H->lat     = (float *)calloc(H->maxsize, sizeof(float));
    H->ip      = (char **)calloc(H->maxsize, sizeof(char*));
    for(int i = 1; i < maxsize; i++){
        H->ip[i] = (char*)calloc(50, sizeof(char));
    } 
    return(H);
}

int main(int argc,char * argv[]){
    int    maxsize;
    int    info;
    float  lat;

    FILE * fp;
    fp = fopen(argv[1], "r");

    char* tempstr = (char*)calloc(51, sizeof(char));
    maxsize = atoi(fgets(tempstr, 5, fp)) + 1;
    Heap * p = CriaHeap(maxsize);
    free(tempstr);

    for(int i = 1; i < maxsize; i++){
        char*  tempstr  = (char*)calloc(31, sizeof(char));
        char*  ip       = (char*)calloc(31, sizeof(char));
        
        ip = strtok(fgets(tempstr, 31, fp), " ");
        info = atoi(strtok(NULL, " "));
        lat  = strtof(strtok(NULL, " "), NULL);

        p->ip[i]    = strcpy(p->ip[i], ip);
        p->info[i]  = info;
        p->lat[i]   = lat;

        free(ip);
        free(tempstr);
    }
    fclose(fp);

    printf("1) Sequencia Lida\n");
    for(int i = 1; i < maxsize; i++){
        p->nelems++;
        printf("%s %d %.2f\n", p->ip[i], p->info[i], p->lat[i]);
    }
    //printf("NELEMS: %d", p->nelems);
    for(int k = 0; k < 10; k++){
        for(int i = maxsize-1; i > 0; i--){
            //printf("%d\n", i);
            //printf("%s %d %.2f\n", p->ip[i], p->info[i], p->lat[i]);
            //printf("%d %d\n", FilhoEsquerdo(i), FilhoDireito(i));
            if(FilhoDireito(i) < maxsize || FilhoEsquerdo(i) < maxsize){
                if((FilhoEsquerdo(i) < maxsize && FilhoDireito(i) >= maxsize) && p->info[FilhoEsquerdo(i)] > p->info[i]){
                    int    aux1 = p->info[i];
                    float  aux2 = p->lat[i];
                    char * aux3 = p->ip[i];
                    
                    p->info[i]  = p->info[FilhoEsquerdo(i)];
                    p->lat[i]   = p->lat[FilhoEsquerdo(i)];
                    p->ip[i]    = p->ip[FilhoEsquerdo(i)];

                    p->info[FilhoEsquerdo(i)] = aux1;
                    p->lat[FilhoEsquerdo(i)]  = aux2;
                    p->ip[FilhoEsquerdo(i)]   = aux3;                

                } else if((FilhoEsquerdo(i) >= maxsize && FilhoDireito(i) < maxsize)  && p->info[FilhoDireito(i)] > p->info[i]){
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];

                        p->info[i] = p->info[FilhoDireito(i)];
                        p->lat[i]  = p->lat[FilhoDireito(i)];
                        p->ip[i]   = p->ip[FilhoDireito(i)];

                        p->info[FilhoDireito(i)] = aux1;
                        p->lat[FilhoDireito(i)]  = aux2;
                        p->ip[FilhoDireito(i)]   = aux3;                

                } else if(FilhoEsquerdo(i) < maxsize && FilhoDireito(i) < maxsize){
                    if((p->info[FilhoEsquerdo(i)] > p->info[FilhoDireito(i)]) && p->info[FilhoEsquerdo(i)] > p->info[i]){
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];

                        p->info[i] = p->info[FilhoEsquerdo(i)];
                        p->lat[i]  = p->lat[FilhoEsquerdo(i)];
                        p->ip[i]   = p->ip[FilhoEsquerdo(i)];

                        p->info[FilhoEsquerdo(i)] = aux1;
                        p->lat[FilhoEsquerdo(i)]  = aux2;
                        p->ip[FilhoEsquerdo(i)]   = aux3;
                    }else if((p->info[FilhoEsquerdo(i)] < p->info[FilhoDireito(i)]) && p->info[FilhoDireito(i)] > p->info[i]){
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];

                        p->info[i] = p->info[FilhoDireito(i)];
                        p->lat[i]  = p->lat[FilhoDireito(i)];
                        p->ip[i]   = p->ip[FilhoDireito(i)];

                        p->info[FilhoDireito(i)] = aux1;
                        p->lat[FilhoDireito(i)]  = aux2;
                        p->ip[FilhoDireito(i)]   = aux3;
                    }
                }
            }
        }
    }

    /*DEBUG*/
    //printf("\n - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - \n\n");
    //for(int i = 1; i < maxsize; i++){
    //    printf("%s %d %.2f\n", p->ip[i], p->info[i], p->lat[i]);
    //}
    printf("\n2) Heap maximo construido\nImprimindo heap\n");
    ImprimeHeap(p, 1, 0);

    return 0;
}