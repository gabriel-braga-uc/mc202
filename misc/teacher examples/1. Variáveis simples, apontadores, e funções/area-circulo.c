#include <stdio.h>

#define PI 3.141592653589793

float AreaCirculo(float raio)
{
  float area = PI*raio*raio;
  return(area);
}

int main()
{
  float raio, area;

  printf("Entre com o raio (cm): ");
  scanf("%f",&raio);
  area = AreaCirculo(raio);
  printf("Área do círculo: %.2fcm2\n",area);
  return(0);
}

