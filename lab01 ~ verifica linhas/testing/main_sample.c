#include <stdio.h>
#include <stdlib.h>
/* Algoritmo para desenhar linhas em uma matriz e verificar linhas que
se interceptam. -- variáveis compostas e homogêneas. */
/*
Cabeçalho: Implemente um programa que:

- Receba os parâmetros de duas retas (x1 y1 x2 y2) (x3 y3 x4 y4)
- Desenhe essas duas linhas em uma matriz de [100, 100]
- Verifique se elas se interceptam, e caso se interceptem, exiba o ponto de interseção (Dentro da Matriz).
- Por fim, exiba a matriz, utilizando a função Printmatriz
*/
typedef struct ponto {
  int x, y;
} Ponto;
// y = mx + n
typedef struct reta
{
  Ponto inicio, fim;
  float coeficiente_angular; // m
  float coeficiente_linear; // n
} Reta;

void ExibeMatriz(int **matriz, int altura, int largura);
int **CriaMatriz(int altura, int largura);
void DestroiMatriz(int **matriz, int altura);
void DesenhaLinhas(int **matriz, int altura, int largura, Reta reta);
int VerificaInterseccao(Reta reta_1, Reta reta_2, Ponto *interseccao);
void ConfiguraCoeficientesReta(Reta *reta);


void ConfiguraCoeficientesReta(Reta *reta) {
  float m, n;
  float x_1, x_2, y_1, y_2;
  x_1 = (float)(reta->inicio.x);
  y_1 = (float)(reta->inicio.y);
  x_2 = (float)(reta->fim.x);
  y_2 = (float)(reta->fim.y);
  if (x_2-x_1 != 0){
    m = ((y_2-y_1)/(x_2-x_1));
  } else{
    m = 0;
  }
  n = (y_1-(m*x_1));
  reta->coeficiente_angular = m;
  reta->coeficiente_linear = n;
}
int VerificaInterseccao(Reta reta_1, Reta reta_2, Ponto *interseccao) {
  printf("1n: %f,  2n: %f\n", reta_1.coeficiente_linear, reta_2.coeficiente_linear);
  printf("1m: %f,  2m %f\n", reta_1.coeficiente_angular, reta_2.coeficiente_angular);
  if(reta_1.coeficiente_angular == reta_2.coeficiente_angular){
      if((reta_1.coeficiente_linear == reta_2.coeficiente_linear && (reta_1.coeficiente_angular != 0 || (reta_1.inicio.y == reta_2.inicio.y && reta_1.fim.y == reta_2.inicio.y && reta_1.fim.y == reta_2.fim.y && reta_1.inicio.y == reta_2.fim.y))) || (reta_1.inicio.x == reta_2.inicio.x && reta_1.fim.x == reta_2.fim.x && reta_1.inicio.x == reta_2.fim.x && reta_1.fim.x == reta_2.inicio.x)){
        return(2);
      }
      else{
        return(0);
      }
    }
    else{
      float A_1, A_2, B_1, B_2, C_1, C_2, r_1_x_1, r_1_x_2, r_1_y_1, r_1_y_2, r_2_x_1, r_2_x_2, r_2_y_1, r_2_y_2, det;
      
      r_1_x_1 = (float)(reta_1.inicio.x);
      r_1_x_2 = (float)(reta_1.fim.x);
      r_1_y_1 = (float)(reta_1.inicio.y);
      r_1_y_2 = (float)(reta_1.fim.y);
      r_2_x_1 = (float)(reta_2.inicio.x);
      r_2_x_2 = (float)(reta_2.fim.x);
      r_2_y_1 = (float)(reta_2.inicio.y);
      r_2_y_2 = (float)(reta_2.fim.y);
      
      A_1 = r_1_y_1 - r_1_y_2;
      A_2 = r_2_y_1 - r_2_y_2;
      B_1 = r_1_x_2 - r_1_x_1;
      B_2 = r_2_x_2 - r_2_x_1;
      C_1 = r_1_x_1*r_1_y_2 - r_1_x_2*r_1_y_1;
      C_2 = r_2_x_1*r_2_y_2 - r_2_x_2*r_2_y_1;

      det = A_1*B_2-A_2*B_1;
      float intersec_x = (B_1*C_2-B_2*C_1)/det;
      float intersec_y = (C_1*A_2-C_2*A_1)/det;
      interseccao->x = (int)(intersec_x);
      interseccao->y = (int)(intersec_y);
      return(1);
  }
}
void DesenhaLinhas(int **matriz, int altura, int largura, Reta reta) {
  float m, n;
  m = reta.coeficiente_angular;
  n = reta.coeficiente_linear;
  int tx, ty;
  if(reta.fim.x-reta.inicio.x != 0){
    for(float i = 0;i < 100; i++){
      tx = (int)(i);
      ty = (int)(i*m + n);
      if(tx<100 && tx>=0 && ty<100 && ty>=0){
          if((((reta.inicio.x <= tx) && (reta.fim.x >= tx)) || ((reta.fim.x <= tx) && (reta.inicio.x >= tx))) && (((reta.inicio.y <= ty) && (reta.fim.y >= ty)) || ((reta.fim.y <= ty) && (reta.inicio.y >= ty)))){
            matriz[99-ty][tx] = 1;
        }
      }
    }
  }else{
    if(reta.fim.y > reta.inicio.y)
    {
      for(int i = reta.inicio.y;i < reta.fim.y; i++)
      {
        matriz[99-i][reta.inicio.x] = 1;
      }
    }
    else if (reta.fim.y < reta.inicio.y)
    {
      for(int i = reta.fim.y; i < reta.inicio.y; i++)
      {
        matriz[99-i][reta.inicio.x] = 1;
      }

    }
    
  }
}


void ExibeMatriz(int **matriz, int altura, int largura) {
  for (int linha = 0; linha < altura; linha++) {
    printf("[ ");
    for (int coluna = 0; coluna < largura; coluna++) {
      printf("%d ", matriz[linha][coluna]);
    }
    printf("]\n");
  }
}
int **CriaMatriz(int altura, int largura) {
  int **matriz = (int **)calloc(altura, sizeof(int *));
  // Para cada linha, aloca memória para suas colunas
  for (int linha = 0; linha < altura; linha++) {
    matriz[linha] = (int *)calloc(largura, sizeof(int));
    // Inicializa os valores da linha
    for (int coluna = 0; coluna < largura; coluna++) {
      matriz[linha][coluna] = 0;
    }
  }

  return matriz;
}
void DestroiMatriz(int **matriz, int altura) {
  if (matriz != NULL) {
    for (int i = 0; i < altura; i++) {
      if (matriz[i] != NULL) {
        free(matriz[i]);
      }
    }
    free(matriz);
  }
}
int main(int argc, char *argv[]) {
  Reta reta_1, reta_2;

  // Read file
  FILE *fp = fopen(argv[1], "r");
  fscanf(
    fp, "(%d %d %d %d) ",
    &reta_1.inicio.x, &reta_1.inicio.y, &reta_1.fim.x, &reta_1.fim.y
  );
  fscanf(
    fp, "(%d %d %d %d)",
    &reta_2.inicio.x, &reta_2.inicio.y, &reta_2.fim.x, &reta_2.fim.y
  );
  fclose(fp);

  int largura = 100, altura = 100;
  int **matriz = CriaMatriz(altura, largura);
  ConfiguraCoeficientesReta(&reta_1);
  ConfiguraCoeficientesReta(&reta_2);
  DesenhaLinhas(matriz, altura, largura, reta_1);
  DesenhaLinhas(matriz, altura, largura, reta_2);
  Ponto interseccao;
  int status = VerificaInterseccao(reta_1, reta_2, &interseccao);
  if (status == 0) {
    printf("Retas são paralelas\n");
  } else if (status == 1) {
    printf("Retas são concorrentes\n");
    if (
      (interseccao.x > 0 && interseccao.x < largura) &&
      (interseccao.y > 0 && interseccao.y < altura)
    ) {
      printf("Intersecção ocorre na matriz\n");
      // Marca o ponto de intersecção com 2
      matriz[99 - interseccao.y][interseccao.x] = 2;
    }
    else {
      printf("Intersecção ocorre fora da matriz\n");
    }
    printf("Intersecção: (%d, %d)\n", interseccao.x, interseccao.y);

  } else if (status == 2) {
    printf("Retas são coincidentes\n");
  }

  ExibeMatriz(matriz, altura, largura);
  DestroiMatriz(matriz, altura);

  return 0;
}