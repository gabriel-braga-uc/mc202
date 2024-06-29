#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i)
#define FilhoDireito(i) (2*i+1)
typedef enum{false,true} Boolean;
typedef struct _heap {
  int *info;              /* informação e prioridade ao mesmo tempo */
  float *lat;
  char ** ip;
  int  nelems, maxsize;   /* número de elementos no heap e o tamanho do vetor */
} Heap;

Heap *CriaHeap(int maxsize);
void ImprimeHeap(Heap *H, int indice, int nivel);

void DesceHeap (Heap *H, int i)
{ 
    int     maior,esq,dir;
    Boolean continua=true;

    while (continua) { 

        esq = FilhoEsquerdo(i);
        dir = FilhoDireito(i);
    // if(H->info[esq] == H->info[dir] && H->lat[esq] < H->lat[dir])
    if ((esq < H->nelems) && ((H->info[esq] > H->info[i]) || ((H->info[esq] == H->info[dir] && H->lat[esq] < H->lat[i]))))
        maior = esq;
    else
        maior = i;

    if ((dir < H->nelems) && ((H->info[dir] > H->info[maior]) || ((H->info[maior] == H->info[dir] && H->lat[maior] > H->lat[dir]))))
        maior = dir;

    if (maior != i){
        int    aux1     =   H->info[i];
        float  aux2     =   H->lat[i];
        char * aux3     =   H->ip[i];
        H->info[i]      =   H->info[maior];
        H->lat[i]       =   H->lat[maior];
        H->ip[i]        =   H->ip[maior];
        H->info[maior]  =   aux1;
        H->lat[maior]   =   aux2;
        H->ip[maior]    =   aux3;
        i = maior;
    }else
        continua = false;
    }
}
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

    char*  tempstr2  = (char*)calloc(31, sizeof(char));
    char*  ip       = (char*)calloc(31, sizeof(char));
    for(int i = 1; i < maxsize; i++){
        
        ip = strtok(fgets(tempstr2, 31, fp), " ");
        info = atoi(strtok(NULL, " "));
        lat  = strtof(strtok(NULL, " "), NULL);

        p->ip[i]    = strcpy(p->ip[i], ip);
        p->info[i]  = info;
        p->lat[i]   = lat;

    }

    printf("1) Sequencia Lida\n");
    for(int i = 1; i < maxsize; i++){
        p->nelems++;
        printf("%s %d %.2f\n", p->ip[i], p->info[i], p->lat[i]);
    }
    fclose(fp);
    for(int k = 0; k < 100; k++){
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
//
                    p->info[FilhoEsquerdo(i)] = aux1;
                    p->lat[FilhoEsquerdo(i)]  = aux2;
                    p->ip[FilhoEsquerdo(i)]   = aux3;                
//
                } else if((FilhoEsquerdo(i) >= maxsize && FilhoDireito(i) < maxsize)  && p->info[FilhoDireito(i)] > p->info[i]){
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];
//
                        p->info[i] = p->info[FilhoDireito(i)];
                        p->lat[i]  = p->lat[FilhoDireito(i)];
                        p->ip[i]   = p->ip[FilhoDireito(i)];
//
                        p->info[FilhoDireito(i)] = aux1;
                        p->lat[FilhoDireito(i)]  = aux2;
                        p->ip[FilhoDireito(i)]   = aux3;                
//
                } else if(FilhoEsquerdo(i) < maxsize && FilhoDireito(i) < maxsize){
                    if((p->info[FilhoEsquerdo(i)] == p->info[FilhoDireito(i)])){
                        if(p->info[FilhoEsquerdo(i)] >= p->info[i]){
                            if(p->lat[FilhoEsquerdo(i)] < p->lat[FilhoDireito(i)]){
                                int    aux1 = p->info[i];
                                float  aux2 = p->lat[i];
                                char * aux3 = p->ip[i];
//      
                                p->info[i] = p->info[FilhoEsquerdo(i)];
                                p->lat[i]  = p->lat[FilhoEsquerdo(i)];
                                p->ip[i]   = p->ip[FilhoEsquerdo(i)];
//      
                                p->info[FilhoEsquerdo(i)] = aux1;
                                p->lat[FilhoEsquerdo(i)]  = aux2;
                                p->ip[FilhoEsquerdo(i)]   = aux3;
                            } else{
                                int    aux1 = p->info[i];
                                float  aux2 = p->lat[i];
                                char * aux3 = p->ip[i];
//      
                                p->info[i] = p->info[FilhoDireito(i)];
                                p->lat[i]  = p->lat[FilhoDireito(i)];
                                p->ip[i]   = p->ip[FilhoDireito(i)];
//      
                                p->info[FilhoDireito(i)] = aux1;
                                p->lat[FilhoDireito(i)]  = aux2;
                                p->ip[FilhoDireito(i)]   = aux3;
                            }
                        }
                    } else if((p->info[FilhoEsquerdo(i)] > p->info[FilhoDireito(i)]) && p->info[FilhoEsquerdo(i)] > p->info[i]){
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];
//
                        p->info[i] = p->info[FilhoEsquerdo(i)];
                        p->lat[i]  = p->lat[FilhoEsquerdo(i)];
                        p->ip[i]   = p->ip[FilhoEsquerdo(i)];
//
                        p->info[FilhoEsquerdo(i)] = aux1;
                        p->lat[FilhoEsquerdo(i)]  = aux2;
                        p->ip[FilhoEsquerdo(i)]   = aux3;
                    }else if((p->info[FilhoEsquerdo(i)] < p->info[FilhoDireito(i)]) && p->info[FilhoDireito(i)] > p->info[i]){
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];
//
                        p->info[i] = p->info[FilhoDireito(i)];
                        p->lat[i]  = p->lat[FilhoDireito(i)];
                        p->ip[i]   = p->ip[FilhoDireito(i)];
//
                        p->info[FilhoDireito(i)] = aux1;
                        p->lat[FilhoDireito(i)]  = aux2;
                        p->ip[FilhoDireito(i)]   = aux3;
                    }else if(p->info[FilhoEsquerdo(i)] == p->info[i]){
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];
//
                        p->info[i] = p->info[FilhoEsquerdo(i)];
                        p->lat[i]  = p->lat[FilhoEsquerdo(i)];
                        p->ip[i]   = p->ip[FilhoEsquerdo(i)];
//
                        p->info[FilhoEsquerdo(i)] = aux1;
                        p->lat[FilhoEsquerdo(i)]  = aux2;
                        p->ip[FilhoEsquerdo(i)]   = aux3;
                    }else if(p->info[FilhoDireito(i)] == p->info[i]){
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];
//
                        p->info[i] = p->info[FilhoDireito(i)];
                        p->lat[i]  = p->lat[FilhoDireito(i)];
                        p->ip[i]   = p->ip[FilhoDireito(i)];
//
                        p->info[FilhoDireito(i)] = aux1;
                        p->lat[FilhoDireito(i)]  = aux2;
                        p->ip[FilhoDireito(i)]   = aux3;
                    }
                }
            }
        }
    }
//
    /*DEBUG*/
    //printf("\n - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - \n\n");
    //for(int i = 1; i < maxsize; i++){
    //    printf("%s %d %.2f\n", p->ip[i], p->info[i], p->lat[i]);
    //}
    printf("\n2) Heap maximo construido\nImprimindo heap\n");
    ImprimeHeap(p, 1, 0);
    //printf("%d\n", maxsize);
    printf("3) Removendo elementos do heap por ordem de prioridade e restricao de latencia\n");
    int esq, dir;
    for(int i = 1; i < maxsize; i++){
        printf("Removido elemento de prioridade %d com valor de latencia %f e valor de IP %s\n", p->info[1], p->lat[1], p->ip[1]);
        
        //int    aux1 = p->info[1];
        //float  aux2 = p->lat[1];
        //char * aux3 = p->ip[1];
        p->info[1]  = p->info[p->nelems];
        p->lat[1]   = p->lat[p->nelems];
        p->ip[1]    = p->ip[p->nelems];
        
       // for(int k = 0; k < 11; k++){
       //     for(int i = 1; i < p->nelems; i++){
                DesceHeap(p, 1);
        //    }
        //}
        p->nelems--;
        if (p->nelems > 0){
            printf("Imprimindo heap\n");
        }
        for(int k = 0; k < 3; k++){
            for(int i = 1; i < p->nelems; i++){
                esq = FilhoEsquerdo(i);
                dir = FilhoDireito(i);
                if(esq <= p->nelems){
                    if((p->info[esq] == p->info[i]) && p->lat[i] > p->lat[esq]){
                        //printf("    UJBLBIHJSUFEDLBJFIHSEWLBIGFWEALBGFBLUIWELBIJUGHF");
                        int    aux1 = p->info[i];
                        float  aux2 = p->lat[i];
                        char * aux3 = p->ip[i];

                        p->info[i] = p->info[FilhoEsquerdo(i)];
                        p->lat[i]  = p->lat[FilhoEsquerdo(i)];
                        p->ip[i]   = p->ip[FilhoEsquerdo(i)];

                        p->info[FilhoEsquerdo(i)] = aux1;
                        p->lat[FilhoEsquerdo(i)]  = aux2;
                        p->ip[FilhoEsquerdo(i)]   = aux3;
                    }
                }
                if(dir <= p->nelems){
                    if((p->info[dir] == p->info[i]) && p->lat[i] > p->lat[dir]){
                        //printf("    UJBLBIHJSUFEDLBJFIHSEWLBIGFWEALBGFBLUIWELBIJUGHF");
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
        ImprimeHeap(p, 1, 0);
    }
    return 0;
}