#include <stdlib.h>
#include <stdio.h>

int **CriaMatrizInt(int nlin, int ncol);
int * MAX(int * N, int ** A);
int **CriaMatrizInt(int nlin, int ncol)
{
  int **m = (int **)calloc(nlin,sizeof(int *));
  
  for (int l=0; l < nlin; l++)
    m[l] = (int *)calloc(ncol,sizeof(int));
  return(m);
}
int * MAX(int * N, int ** A){
    int * respostas = calloc(3, sizeof(int));
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

int main(){
    int n;
    n = 2;
    int** A = CriaMatrizInt(n, n);
    A[0][0] = 5;
    A[0][1] = 44;
    A[1][0] = 66;
    A[1][1] = 33;
    int * exc1 = MAX(&n, A);
    printf("Teste exercício 1: \n Os valores do exercício 1 foram: \n k=%i, l=%i, c=%i\n", exc1[0], exc1[1], exc1[2]);

    return(0);
}
