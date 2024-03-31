#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
  Reta reta_1, reta_2;
  // Read file
  scanf("%d %d %d %d", &reta_1.inicio.x, &reta_1.inicio.y, &reta_1.fim.x, &reta_1.fim.y);
  scanf("%d %d %d %d", &reta_2.inicio.x, &reta_2.inicio.y, &reta_2.fim.x, &reta_2.fim.y);
  printf("Reta1 Inicio X: %i, Reta1 Inicio Y: %i, Reta1 Fim X: %i, Reta1 Fim Y: %i\n", reta_1.inicio.x, reta_1.inicio.y, reta_1.fim.x, reta_1.fim.y);
  printf("Reta2 Inicio X: %i, Reta2 Inicio Y: %i, Reta2 Fim X: %i, Reta2 Fim Y: %i", reta_2.inicio.x, reta_2.inicio.y, reta_2.fim.x, reta_2.fim.y);
  return(0);
}
