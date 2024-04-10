#include "circulos.h"

Circulo *CriaCirculo(Ponto P, float raio)
{
  Circulo *C = (Circulo *)calloc(1,sizeof(Circulo));

  C->centro.x  = P.x;
  C->centro.y  = P.y;
  C->raio      = raio;

  return(C);
}

void DestroiCirculo(Circulo **C)
{
  Circulo *aux = *C;

  if (aux != NULL){
    free(aux);
    (*C) = NULL;
  }
}
  
  
