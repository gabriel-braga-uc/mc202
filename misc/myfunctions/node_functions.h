#include <stdlib.h>
#ifndef NODE_FUNCTIONS_H

typedef struct node{
  int a;
  struct node * up;
} node;

node * criaNodeSimlpes();

void insereCaudaListaSimples(node * P);
void insereCabecaListaSimples(node * P);

node * criaNodeSimlpes(){
  node * P = (node*)calloc(1, sizeof(node));
  P->up = NULL;
  return(P);
}

void insereCaudaListaSimples(node * P){
  if(P->up == NULL){
    P->up = criaNodeSimlpes();
  }
  else{
    insereCaudaListaSimples(P->up);
  }
}


#endif