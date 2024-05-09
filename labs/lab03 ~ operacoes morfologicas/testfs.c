#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct no_lista_simples{
    int valor;
    struct no_lista_simples *proximo;
} ListaSimples, NoListaSimples;
ListaSimples *noAtual = NULL;


// IMPLEMENTAÇÕES (5/12) 

/*1*/   bool ListaSimplesVazia(ListaSimples *inicio);
/*2*/   bool BuscaUltimoElementoListaSimples(ListaSimples *inicio, NoListaSimples **pos, NoListaSimples **ant);
/*3*/   NoListaSimples *CriaNoSimples(int elem);
/*4*/   void InserirElementoNoFimLista(ListaSimples **inicio, int valor);
/*5*/   bool RemoveInicioListaSimples(ListaSimples **inicio, int *elem);
/*6*/   void DestroiListaLigada(ListaSimples **inicio);
/*7*/   NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice);
//*8*/   Pixel *ObterAdjacentes(Pixel P);
//*9*/   void Dilatacao(NoListaSimples **noAtual, int n, int m);
//*10*/  void Erosao(NoListaSimples **noAtual, int n, int m) ;
//*11*/  void Abertura(NoListaSimples **noAtual, int n, int m);
//*12*/  void Fechamento(NoListaSimples **noAtual, int n, int m);

//1 Função para verificar se Lista Ligada Simples possui Nó (Só funciona para ponteiros inicializados)
bool ListaSimplesVazia(ListaSimples *inicio){
    if(inicio == NULL){
        return true;
    }else{
        return false;
    }
}
//3 Cria Lista/No Simples
NoListaSimples *CriaNoSimples(int elem){
    ListaSimples * p = (ListaSimples*)calloc(1, sizeof(ListaSimples));
    p->valor = elem;
    p->proximo = NULL;
    return p;
}
//4 Insere nó no fim da lista
void InserirElementoNoFimLista(ListaSimples **inicio, int valor){
    while((*inicio)->proximo != NULL){
        inicio = &((*inicio)->proximo);
    }
    (*inicio)->proximo = CriaNoSimples(valor);
}
//5 Remove Inicio Lista Simples
bool RemoveInicioListaSimples(ListaSimples **inicio, int *elem){
    NoListaSimples *p = *inicio;
    *elem = (*inicio)->valor;
    *inicio = (*inicio)->proximo; 
    free(p);
    return(true);
}
//6 destroi lista
void DestroiListaLigada(ListaSimples **inicio){
    int elem;
    while (!ListaSimplesVazia(*inicio))
        RemoveInicioListaSimples(inicio, &elem);
}
//2 Busca ultimo elemento
bool BuscaUltimoElementoListaSimples(ListaSimples *inicio, NoListaSimples **pos, NoListaSimples **ant){
    *pos = inicio;
    *ant = NULL;
    if (ListaSimplesVazia(inicio))
        return(false);
    while (((*pos)->proximo != NULL)){ /* busca o ultimo elemento */
        (*ant) = (*pos);
        (*pos) = (*pos)->proximo;
    }
    return(true);
}
// 7
NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice){
    
}

bool BuscaElementoListaSimples(ListaSimples *inicio, int elem, NoListaSimples **pos, NoListaSimples **ant){
    *ant = NULL; *pos = inicio;
    while (!ListaSimplesVazia(*pos)){
        if ((*pos)->valor == elem){
          return(true);
        } 
    *ant = (*pos);
    *pos = (*pos)->proximo;    
    }
    return(false);
}


int main(){
    

    ListaSimples * p = CriaNoSimples(1);
    InserirElementoNoFimLista(&p, 2);
    InserirElementoNoFimLista(&p, 3);
    InserirElementoNoFimLista(&p, 4);
    InserirElementoNoFimLista(&p, 5);
    ListaSimples *pos, *ant;
    bool found = BuscaElementoListaSimples(p, 4, &pos, &ant);
    bool found2 = BuscaUltimoElementoListaSimples(p, &pos, &ant);
    int removido = RemoveInicioListaSimples(&p, &removido);
    DestroiListaLigada(&p);
    return 0;
}