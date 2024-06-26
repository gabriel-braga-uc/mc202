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

int retornaIndice(float lista[100], int nnos);

int retornaIndice(float lista[100], int nnos){
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
    int proximoNaoVisitado;
    for(int i = 1; i <= nnos; i++){
        proximoNaoVisitado = encontraProximo(nnos, visitado, D);
        visitado[proximoNaoVisitado] = true;

        for(int adj = 1; adj <= nnos; adj++){
            if((int)custo[proximoNaoVisitado][adj] != 999 && D[adj] > D[proximoNaoVisitado] + custo[proximoNaoVisitado][adj]){
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

    bool testailha;
    bool pode;

    int asciisumold = 0;
    int asciisumnew = 0;
    int componentes = 0;
    int nnos;
    int * blacklist = (int*)calloc(50, sizeof(int));

    float tempdist;
    

    FILE * fp;
    fp = fopen(argv[1], "r");

    fscanf(fp, "%d\n", &nnos);
    float ** ymatriz = (float**)calloc(nnos, sizeof(float*));
    ponto * pontos = (ponto*)calloc(nnos+1, sizeof(ponto));

    for(int i = 0; i <= nnos; i++){
        ymatriz[i] = (float*)calloc(nnos+1, sizeof(float));
    }

    for(int i = 1; i <= nnos; i++){
        fscanf(fp, "%c %d %d\n", &pontos[i].nome, &pontos[i].x, &pontos[i].y);
        ymatriz[0][i] = 64 + (float)i;
        ymatriz[i][0] = 64 + (float)i;
    }
    fclose(fp);
    
    for(int i = 1; i <= nnos; i++){
        for(int j = 1; j <= nnos; j++){
            tempdist = distancia((float)pontos[i].x, (float)pontos[i].y, (float)pontos[j].x, (float)pontos[j].y);
            if(tempdist <= 2){
                ymatriz[i][j] = tempdist;
            }else if (tempdist > 2){
                ymatriz[i][j] = 123; // Valor coringa pra identificar depois na parte do Dijkstra
            }
        }
    }

    printf("Matriz de adjacencia:\n");
    printf("	");
    for(int i = 1; i <= nnos-1; i++){
        printf("%c 	", pontos[i].nome);
    }
    printf("%c\n", pontos[nnos].nome);
    for(int i = 1; i <= nnos; i++){
        for(int j = 0; j <= nnos; j++){
            if(i == 0 && j == 0){
            } else if(i == 0 || j == 0){
                if(i == 0){
                    printf("\t%c", (int)ymatriz[0][j]);
                }
                if(j == 0){
                    printf("%c", pontos[i].nome);
                }
            } else {
                if(ymatriz[i][j] == 0){
                    printf("\t%d", (int)(ymatriz[i][j]));
                } else{
                    if(ymatriz[i][j] == 123){
                        printf("\t0");
                    } else {
                        printf("\t%.3f", ymatriz[i][j]);
                    }
                }
            }
        }
        printf("\n");
    }

    printf("Percurso mínimo:\n");


    float * distanciaDijkstra = (float*)calloc(50, sizeof(float));
    float * distanciaDijkstraClone = (float*)calloc(50, sizeof(float));
    int * paiDijkstra = (int*)calloc(50, sizeof(int));
    bool * visitadoDijkstra = (bool*)calloc(50, sizeof(bool));

    int indextemp;
    for(int k = 1; k <= nnos; k++){

        bool * visitadoDijkstra = (bool*)calloc(50, sizeof(bool));

        for(int i = 1; i <= nnos; i++){
            distanciaDijkstra[i] = 999;
        }
        distanciaDijkstra[k] = 0;
        

        dijkstras(nnos, ymatriz, distanciaDijkstra, paiDijkstra, visitadoDijkstra);
        for(int i = 1; i <= nnos; i++){
            distanciaDijkstraClone[i] = distanciaDijkstra[i];
        }

        printf("Percurso [No %c]:", pontos[k].nome);
        testailha = true;
        asciisumnew = (int)(pontos[k].nome);
        for(int i = 1; i <= nnos; i++){
            indextemp = retornaIndice(distanciaDijkstraClone, nnos);
            //printf("%d, ", indextemp);
            if((int)(pontos[k].nome) != (int)(pontos[indextemp].nome) && distanciaDijkstraClone[indextemp] != 123){
                testailha = false;
                asciisumnew += (int)(pontos[indextemp].nome);
                printf(" (%c %f) ", pontos[indextemp].nome, distanciaDijkstraClone[indextemp]);
            }
            distanciaDijkstraClone[indextemp] = 999;
        }

        /*Conta componentes baseado no output do Dijkstra pela soma dos valores ascii dos rotulos dos nós printados a cada linha
        incluindo o nó raiz, esse valor não muda para nodos conexos. Na hora que muda o componente esse valor muda. Cada componente
        vai ter um valor unico asssociado a ele dessa maneira*/
        if(testailha){
            componentes++;
            printf(" E uma ilha");
        }else if(asciisumnew != asciisumold && !testailha){
            pode = true;
            for(int w = 0; w < 50; w++){
                if(blacklist[w] == asciisumnew){
                    pode = false;
                }
            }
            if(pode){
                componentes++;
            }
            blacklist[k] = asciisumnew;
        }
        asciisumold = asciisumnew;

        free(visitadoDijkstra);

        printf("\n");
    }
    printf("Grafo tem %d componentes", componentes);
    return 0;
}