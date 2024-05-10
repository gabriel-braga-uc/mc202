#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct no_lista_simples{
    int valor;
    struct no_lista_simples *proximo;
} ListaSimples, NoListaSimples;
ListaSimples *noAtual = NULL;

NoListaSimples *CriaNoSimples(int elem);
void InserirElementoNoFimLista(ListaSimples **inicio, int valor);
NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice);

NoListaSimples *CriaNoSimples(int elem){
    ListaSimples * p = (ListaSimples*)calloc(1, sizeof(ListaSimples));
    p->valor = elem;
    p->proximo = NULL;
    return p;
}
void InserirElementoNoFimLista(ListaSimples **inicio, int valor){
    while((*inicio)->proximo != NULL){
        inicio = &((*inicio)->proximo);
    }
    (*inicio)->proximo = CriaNoSimples(valor);
}
NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice){
    for(int aux = 0; aux < indice; aux++){
        noAtual = &(*noAtual->proximo);
    }
    return noAtual;
}

int main(){
    ListaSimples * p = CriaNoSimples(1);
    ListaSimples * noAtual = p;
    InserirElementoNoFimLista(&p, 2);
    InserirElementoNoFimLista(&p, 3);
    InserirElementoNoFimLista(&p, 4);
    InserirElementoNoFimLista(&p, 5);
    ListaSimples *qual = ObterNo(&(*noAtual), 0);
    printf("dlasdsa:  %d", qual->valor);
    return 0;
}