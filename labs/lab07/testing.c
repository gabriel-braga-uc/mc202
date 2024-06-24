#include <stdlib.h>
#include <stdio.h>


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

int main(){
    float lista[] = {0, 10, 11, 14, 11, 8, 9, 8};
    int nnos = 7;
    for(int i = 1; i <= nnos; i++){
        int indextemp = retornaIndice(lista, nnos);
        printf("[%d, %.2f]", indextemp, lista[indextemp]);
        lista[indextemp] = 999;
    }
    return 0;
}