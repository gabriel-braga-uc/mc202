#include<stdlib.h>
#include<stdio.h>

typedef struct NoSimples{
    int content;
    struct NoSimples * prox;
} NoSimples;

NoSimples * criaNoSimples();
void insereNoSimplesFinal(NoSimples **P, int x);
void insereNoSimplesInicio(NoSimples **P, int x);
void removeInicio(NoSimples **inicio);

NoSimples * criaNoSimples(int x){
    NoSimples * no = (NoSimples *)calloc(1, sizeof(NoSimples));
    no->content = x;
    no->prox = NULL;
    return(no);
}
void removeInicio(NoSimples **inicio){
    NoSimples * P = *inicio;
    *inicio = ((*inicio)->prox);
    free(P);
}
void insereNoSimplesFinal(NoSimples **inicio, int x){
    while((*inicio)->prox != NULL){
       inicio = &((*inicio)->prox);
    }
    NoSimples * inserindo = criaNoSimples(x);
    (*inicio)->prox = inserindo;
}
void insereNoSimplesInicio(NoSimples **inicio, int x){
    NoSimples * inserindo = criaNoSimples(x);
    inserindo->prox = *inicio;
    (*inicio) = inserindo;
}

int main(){
    NoSimples * P = criaNoSimples(1);
    insereNoSimplesFinal(&P, 2);
    removeInicio(&P);
    return 0;
}