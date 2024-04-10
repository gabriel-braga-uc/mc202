#include "banda.h"

Banda *CriaBanda(int nlin, int ncol)
{
  Banda *banda = (Banda *)calloc(1,sizeof(Banda));

  banda->val = (float **) calloc(nlin,sizeof(float *));
  for (int lin = 0; lin < nlin; lin++)
    banda->val[lin] = (float *) calloc(ncol,sizeof(float));

  banda->nlin = nlin;
  banda->ncol = ncol;

  return(banda);
}

void DestroiBanda(Banda **banda)
{
  Banda *aux = *banda;

  if (aux != NULL) {
    for (int lin=0; lin < aux->nlin; lin++)
      free(aux->val[lin]);
    free(aux->val);
    free(aux);
    (*banda) = NULL;
  }
}
  
