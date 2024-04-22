#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct NoSimples {
    int content;
    struct NoSimples* prox;
} NoSimples;

void insereNoSimplesFinal(NoSimples** P, int x);
void insereNoSimplesInicio(NoSimples** P, int x);
NoSimples* criaNoSimples(int x);
void removeInicio(NoSimples** inicio);
bool ListaSimplesVazia(NoSimples* inicio);
bool RemoveFimListaSimples(NoSimples** inicio, int* elem);
bool RemoveElementoListaSimples(NoSimples** inicio, int elem);
bool InsereElementoAntesDaChaveListaSimples(NoSimples** inicio, int elem, int chave);

NoSimples* criaNoSimples(int x) {
    NoSimples* no = (NoSimples*)calloc(1, sizeof(NoSimples));
    no->content = x;
    no->prox = NULL;
    return (no);
}
bool RemoveElementoListaSimples(NoSimples** inicio, int elem)
{
    if (ListaSimplesVazia(&(*inicio)) == true) {
        return(false);
    }
    else {
        while ((*inicio)->content != elem) {
            inicio = &((*inicio)->prox);
        }
        NoSimples* aux = *inicio;
        *inicio = (*inicio)->prox;
        free(aux);
        return(true);
    }
}
void removeInicio(NoSimples** inicio) {
    NoSimples* P = *inicio;
    *inicio = ((*inicio)->prox);
    free(P);
}
void insereNoSimplesFinal(NoSimples** inicio, int x) {
    while ((*inicio)->prox != NULL) {
        inicio = &((*inicio)->prox);
    }
    NoSimples* inserindo = criaNoSimples(x);
    (*inicio)->prox = inserindo;
}
void insereNoSimplesInicio(NoSimples** inicio, int x) {
    NoSimples* inserindo = criaNoSimples(x);
    inserindo->prox = *inicio;
    (*inicio) = inserindo;
}
bool ListaSimplesVazia(NoSimples* inicio) {
    if (inicio == NULL)
        return (true);
    else
        return (false);
}
bool InsereElementoAntesDaChaveListaSimples(NoSimples** inicio, int elem, int chave)
{
    if (ListaSimplesVazia(inicio) == true) {
        return(false);
    }
    NoSimples* inserindo = criaNoSimples(elem);

    while ((*inicio)->prox->content != elem && (*inicio)->prox->prox != NULL) {
        inicio = &((*inicio)->prox);
    }

    inserindo->prox = (*inicio)->prox;
    (*inicio)->prox = inserindo;
    return(true);
}
// NAO FUNCIONA
//bool RemoveFimListaSimples(NoSimples** inicio, int* elem) {
//    if (ListaSimplesVazia(inicio) == true) {
//        return (false);
//    }
//    else {
//        while ((*inicio)->prox != NULL) {
//            inicio = &((*inicio)->prox);
//        }
//        *elem = (*inicio)->content;
//        free((*inicio)->prox);
//        (*inicio)->prox = NULL;
//        return (true);
//    }
//}


int main() {
    NoSimples* P = criaNoSimples(1);
    insereNoSimplesFinal(&P, 2);
    insereNoSimplesFinal(&P, 4);
    InsereElementoAntesDaChaveListaSimples(&P, 3, 4);
    int elem;
    //RemoveFimListaSimples(&P, &elem);
    return 0;
}