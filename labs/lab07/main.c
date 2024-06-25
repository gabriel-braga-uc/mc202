#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct _point {
    char nome;
    int x;
    int y;
} ponto;
float distancia(float x1, float y1, float x2, float y2);
void dijkstras(int nnos, float ** custo, float * D, int * pai, bool * visitado);
int encontraProximo(int nnos, bool * visitado, float * D);

int retornaIndice(float lista[100], int nnos, int indexban);

int retornaIndice(float lista[100], int nnos, int indexban){
    int index;
    float min = 999;
    for(int i = 1; i <= nnos; i++){
        if (lista[i] < min && lista[i] != 999){
            min = lista[i];
            index = i; 
        }
    }
    return index;
}

int encontraProximo(int nnos, bool * visitado, float * D){
    int minimoV = 999;
    int minimoN = 0;
    for(int i = 1; i <= nnos; i++){
        if(!visitado[i] && D[i] < minimoV){
            minimoV = D[i];
            minimoN = i;
        }
    }
    return minimoN;
}
void dijkstras(int nnos, float ** custo, float * D, int * pai, bool * visitado){
    for(int i = 1; i <= nnos; i++){
        int proximoNaoVisitado = encontraProximo(nnos, visitado, D);
        visitado[proximoNaoVisitado] = true;

        for(int adj = 1; adj <= nnos; adj++){
            if(custo[proximoNaoVisitado][adj] != 999 && D[adj] > D[proximoNaoVisitado] + custo[proximoNaoVisitado][adj]){
                D[adj] = D[proximoNaoVisitado] + custo[proximoNaoVisitado][adj];
                pai[adj] = proximoNaoVisitado;
            }
        }
    }
}

float distancia(float x1, float y1, float x2, float y2){
    return(sqrt(pow((x2-x1), 2) + pow((y2-y1), 2)));
}

int main(int argc, char * argv[]){

    char * tempstr = (char*)calloc(32, sizeof(char));
    FILE * fp;
    fp = fopen(argv[1], "r");
    int nnos;
    fscanf(fp, "%d\n", &nnos);
    // printf("%d\n", nnos); /*debug*/
    float ** ymatriz = (float**)calloc(nnos, sizeof(float*));
    ponto * pontos = (ponto*)calloc(nnos+1, sizeof(ponto));
    for(int i = 0; i <= nnos; i++){
        ymatriz[i] = (float*)calloc(nnos+1, sizeof(float));
    }
    for(int i = 1; i <= nnos; i++){
        fscanf(fp, "%c %d %d\n", &pontos[i].nome, &pontos[i].x, &pontos[i].y);

        //ymatriz[0][i] = (float)*noNome;
        //ymatriz[i][0] = (float)*noNome;
    }
    float tempdist;
    
    /*debug*/
    //for(int i = 1; i <= nnos; i++){
    //    printf("%c x:%d y:%d\n", pontos[i].nome, pontos[i].x, pontos[i].y);
    //}

    for(int i = 1; i <= nnos; i++){
        for(int j = 1; j <= nnos; j++){
            //printf("%f \n", tempdist);
            tempdist = distancia((float)pontos[i].x, (float)pontos[i].y, (float)pontos[j].x, (float)pontos[j].y);
            if(tempdist <= 2){
                ymatriz[i][j] = tempdist;
            }else if (tempdist > 2){
                ymatriz[i][j] = 999;
            }
        }
    }
    printf("Matriz de adjacencia:\n");
    for(int i = 0; i <= nnos; i++){
        for(int j = 0; j <= nnos; j++){
            if(i == 0 && j == 0){
            } else if(i == 0 || j == 0){
                if(i == 0){
                    printf("\t%c", (int)ymatriz[0][j]);
                }
                if(j == 0){
                    printf("%c", (int)ymatriz[i][0]);
                }
            } else {
                if(ymatriz[i][j] == 0){
                    printf("\t%d", (int)(ymatriz[i][j]));
                } else{
                    if(ymatriz[i][j] == 999){
                        printf("\t0");
                    } else {
                        printf("\t%.3f", ymatriz[i][j]);
                    }
                }
            }
        }
        printf("\n");
    }
    int componentes = 1;
    printf("Percurso mínimo:\n");

    int raiz;
    int * paiDijkstra = (int*)calloc(50, sizeof(int));
    float * distanciaDijkstra = (float*)calloc(50, sizeof(float));
    float * distanciaDijkstraClone = (float*)calloc(50, sizeof(float));
    bool * visitadoDijkstra = (bool*)calloc(50, sizeof(bool));
    for(int k = 1; k <= nnos; k++){
        for(int i = 1; i <= nnos; i++){
            distanciaDijkstra[i] = 999;
        }
        distanciaDijkstra[k] = 0;
        
        dijkstras(nnos, ymatriz, distanciaDijkstra, paiDijkstra, visitadoDijkstra);
        for(int i = 1; i <= nnos; i++){
            distanciaDijkstraClone[i] = distanciaDijkstra[i];
        }

        printf("Percurso [No %c]:", pontos[k].nome);
        int indextemp;
        for(int i = 1; i <= nnos; i++){
            indextemp = retornaIndice(distanciaDijkstraClone, nnos, i);
            //printf("%d, ", indextemp);
            if((int)ymatriz[0][k] != (int)ymatriz[0][indextemp])
                printf(" (%c %f) ", (int)ymatriz[0][indextemp], distanciaDijkstraClone[indextemp]);
            distanciaDijkstraClone[indextemp] = 999;
        }
        printf("\n");
    }
    fclose(fp);
    printf("Grafo tem %d componentes", componentes);
    return 0;
}