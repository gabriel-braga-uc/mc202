#include <stdlib.h>
#include <stdio.h>


int retornaIndice(float lista[100], int nnos, float banished[100]){
    int index;
    int min;
    for(int i = 1; i <= nnos; i++){
        for(int j = 0; i < nnos; i++){
            if(i != banished[j]){
                min = lista[i];
                index = i;
            }
        }
    }
    for(int i = 1; i <= nnos; i++){
        if (lista[i] < min){
            min = lista[i];
            index = i; 
        }
    }
    return index;
}

int main(){
    float lista[] = {0, 10, 11, 14, 11, 8, 9, 8};
    float banished[100];
    int nnos = 7;
    printf("%d", retornaIndice(lista, nnos, banished));
    return 0;
}