
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int tamanhoCheia(int termo){
    if(termo == 1){
        return 0;
    }
    else{
        return(tamanhoCheia(termo-1)+pow(2, termo-2));
    }
}
int main(){
    int termo = 2;
    printf("%d", tamanhoCheia(termo));
    return 0;
}