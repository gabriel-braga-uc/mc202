/**
 * banda.h
 * Estrutura de dados e funções que manipulam matrizes (bandas de uma imagem de cor)
 *
 */

#ifndef BANDA_H
#define BANDA_H

#include <malloc.h>

typedef struct _banda {
  float **val;
  int nlin, ncol;
} Banda, Matriz;

Banda *CriaBanda(int nlin, int ncol);
void   DestroiBanda(Banda **banda);

#endif
