/**
 * imagem.h
 * Estrutura de dados e funções que manipulam matrizes (bandas de uma imagem de cor)
 *
 */

#ifndef IMAGEM_H
#define IMAGEM_H

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "banda.h"
#include "circulos.h"

typedef enum _cor { // associa valores 0, 1, 2
Vermelho, Verde, Azul 
  } Cor;

typedef struct _imagem {
Banda **banda;   // vetor de ponteiros para as bandas da imagem
int num_bandas;  // número de bandas é 3 se a imagem for de uma câmera
		 // RGB.
int nlin, ncol;  // tamanho da imagem.
} Imagem;

Imagem *CriaImagem(int nlin, int ncol, int num_bandas);
void    DestroiImagem(Imagem **img);
Imagem *LeImagemRGB(char *nomearq);
void    GravaImagemRGB(Imagem *img, char *nomearq);
Imagem *DesenhaCirculo(Circulo *C, Imagem *img, int vermelho, int verde, int azul);

#endif
