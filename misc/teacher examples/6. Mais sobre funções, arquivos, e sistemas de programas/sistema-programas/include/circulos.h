/**
 * circulos.h
 * Estrutura de dados e funções que manipulam círculos
 *
 */

#ifndef CIRCULOS_H
#define CIRCULOS_H

#include <malloc.h>

typedef struct _ponto {
  float x, y;
} Ponto;

typedef struct _circulo {
  Ponto centro;
  float raio;
} Circulo;

Circulo *CriaCirculo(Ponto P, float raio);
void     DestroiCirculo(Circulo **C);

#endif
