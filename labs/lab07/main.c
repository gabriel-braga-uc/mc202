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

float distancia(int x1, int y1, int x2, int y2);
void dijkstras(int nnos, float ** custo, float * D, int * pai, bool * visitado);
int encontraProximo(int nnos, bool * visitado, float * D);

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

float distancia(int x1, int y1, int x2, int y2){
    return(sqrt(pow((x2-x1), 2) + pow((y2-y1), 2)));
}

int main(int argc, char * argv[]){

    char * tempstr = (char*)calloc(32, sizeof(char));
    FILE * fp;
    fp = fopen(argv[1], "r");
    int nnos = atoi(fgets(tempstr, 32, fp));
    // printf("%d\n", nnos); /*debug*/
    float ** ymatriz = (float**)calloc(nnos, sizeof(float*));
    ponto * pontos = (ponto*)calloc(nnos, sizeof(ponto));
    for(int i = 0; i <= nnos; i++){
        ymatriz[i] = (float*)calloc(nnos, sizeof(float));
    }
    free(tempstr);
    for(int i = 1; i <= nnos; i++){
        char * tempstr = (char*)calloc(32, sizeof(char));
        tempstr = (fgets(tempstr, 32, fp));
        char * noNome = strtok(tempstr, " ");
        int noX = atoi(strtok(NULL, " "));
        int noY = atoi(strtok(NULL, " "));
        pontos[i].x = noX;
        pontos[i].y = noY;
        pontos[i].nome = noNome[0];

        /*debug*/
        //printf("%f, %d, %d\n", (float)*noNome, noX, noY); /*debug*/

        ymatriz[0][i] = (float)*noNome;
        ymatriz[i][0] = (float)*noNome;
        free(tempstr);
    }
    float tempdist;
    
    /*debug*/
    //for(int i = 1; i <= nnos; i++){
    //    printf("%c x:%d y:%d\n", pontos[i].nome, pontos[i].x, pontos[i].y);
    //}

    for(int i = 1; i <= nnos; i++){
        for(int j = 1; j <= nnos; j++){
            tempdist = distancia(pontos[i].x, pontos[i].y, pontos[j].x, pontos[j].y);
            if(tempdist <= 2){
                ymatriz[i][j] = tempdist;
            }else if (tempdist > 2){
                ymatriz[i][j] = 999;
            }
        }
    }
    fclose(fp);
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

    int * paiDijkstra = (int*)calloc(100, sizeof(int));
    float * distanciaDijkstra = (float*)calloc(100, sizeof(float));
    bool * visitadoDijkstra = (bool*)calloc(100, sizeof(bool));

    int raiz;
    for(int k = 1; k <= nnos; k++){
        raiz = k;
        for(int i = 1; i <= nnos; i++){
            distanciaDijkstra[i] = 999;
            distanciaDijkstra[raiz] = 0;
        }
        dijkstras(nnos, ymatriz, distanciaDijkstra, paiDijkstra, visitadoDijkstra);
        printf("%c", )
    }
    printf("Grafo tem %d componentes", componentes);
    return 0;
}