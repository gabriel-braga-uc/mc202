#ifndef Ponteiros
#define PONTEIROS_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

/*Exercício 1*/
int * MAX(int * N, int ** A){
    int * respostas = (int*)calloc(3, sizeof(int));
    int k, l, c;
    int biggest = 0;
    for(int i = 0; i < *N; i++){
        for(int j = 0; j < *N; j++){
            if (A[i][j] > biggest){
                biggest = A[i][j];
                k = biggest;
                l = j + 1;
                c = i + 1;
            } 
        }
    }
    respostas[0] = k;
    respostas[1] = l;
    respostas[2] = c;
    return(respostas);
}

#endif