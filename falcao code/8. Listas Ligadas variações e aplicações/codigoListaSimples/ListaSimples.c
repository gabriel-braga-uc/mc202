#include "ListaSimples.h"

bool ListaSimplesVazia(ListaSimples* inicio)
{
  if (inicio == NULL)
    return (true);
  else
    return (false);
}
void ImprimeListaSimples(ListaSimples* inicio)
{

  while (!ListaSimplesVazia(inicio))
  {
    printf("%d -->", inicio->elem);
    inicio = inicio->prox;
  }
}

// VVV ??? para que serve o pos e ant?? falta fazer
bool BuscaElementoListaSimples(ListaSimples* inicio, int elem, NoListaSimples** pos, NoListaSimples** ant)
{
  if(ListaSimplesVazia(&(*inicio) == true)){
    return(false);
  } else {
    while((*inicio)->prox != elem);
  }
}

bool BuscaUltimoElementoListaSimples(ListaSimples* inicio, NoListaSimples** pos, NoListaSimples** ant)
{

  *ant = NULL;
  *pos = inicio;

  if (ListaSimplesVazia(*pos))
    return (false);

  while (!ListaSimplesVazia((*pos)->prox))
  {
    *ant = (*pos);
    *pos = (*pos)->prox;
  }

  return (true);
}
NoListaSimples* CriaNoSimples(int elem)
{
  NoListaSimples* no = (NoListaSimples*)calloc(1, sizeof(NoListaSimples));

  no->elem = elem;
  no->prox = NULL;

  return (no);
}
void InsereInicioListaSimples(ListaSimples** inicio, int elem)
{
  while ((*inicio)->prox != NULL)
  {
    inicio = &((*inicio)->prox);
  }
  NoListaSimples* inserindo = criaNoSimples(elem);
  (*inicio)->prox = inserindo;
}
void InsereFimListaSimples(ListaSimples** inicio, int elem)
{
  while ((*inicio)->prox != NULL)
  {
    inicio = &((*inicio)->prox);
  }
  ListaSimples* inserindo = (ListaSimples*)calloc(1, sizeof(ListaSimples));
  inserindo->elem = elem;
  (*inicio)->prox = inserindo;
}

// VVV ??? chave é indice ou elemento a procurar? (fazendo como elemento) ja funciona
bool InsereElementoAntesDaChaveListaSimples(ListaSimples** inicio, int elem, int chave)
{
  if(ListaSimplesVazia(&(*inicio) == true)){
    return(false);
  }
  ListaSimples* inserindo = CriaNoSimples(elem);
  while((*inicio)->elem != elem){
    *inicio = (*inicio)->prox;
  }
  inserindo->prox = (*inicio)->prox;
  (*inicio)->prox = inserindo;
}

// VVV falta fazer
bool RemoveInicioListaSimples(ListaSimples** inicio, int* elem)
{
  if (ListaSimplesVazia(&(*inicio)) == true)
  {
    return (false);
  }
  else
  {
    NoListaSimples* P = *inicio;
    *inicio = ((*inicio)->prox);
    free(P);
    return (true);
    // Falta colocar o *elem (retornar o que deletou pra variavel na main) e o false (vazio) e true (deletou) no return()
  }
}

bool RemoveElementoListaSimples(ListaSimples** inicio, int elem)
{
  if (ListaSimplesVazia(&(*inicio)) == true) {
    return(false);
  }
  else {
    while ((*inicio)->elem != elem) {
      inicio = &((*inicio)->prox);
    }
    ListaSimples* aux = *inicio;
    *inicio = (*inicio)->prox;
    free(aux);
    return(true);
  }
}
bool RemoveFimListaSimples(ListaSimples** inicio, int* elem)
{
  if (ListaSimplesVazia(&(*inicio)) == true)
  {
    return (false);
  }
  else
  {
    while ((*inicio)->prox != NULL)
    {
      inicio = &((*inicio)->prox);
    }
    *elem = (*inicio)->elem;
    free((*inicio)->prox);
    (*inicio)->prox = NULL;
    return (true);
  }
}

void DestroiListaSimples(ListaSimples** inicio)
{
  int elem;
  while (!ListaSimplesVazia(*inicio))
    RemoveInicioListaSimples(inicio, &elem);
}
