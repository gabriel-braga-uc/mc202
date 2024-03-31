#include <stdio.h>
#include <stdlib.h>
typedef struct _ponto{
  float x, y;
} Ponto;
typedef struct _circulo{
  Ponto centro;
  float raio;
} Circulo;
void TransladaCirculo(Circulo *C, float Dx, float Dy){
  C->centro.x += Dx;
  C->centro.y += Dy;
}
int main(){
  Ponto arbitro;
  printf("Insira as coordenadas do centro de seu circulo\n");
  printf("Insira o valor de x: ");
  scanf("%f", &arbitro.x);
  printf("\nInsira o valor de y: ");
  scanf("%f", &  arbitro.y);
  printf("\nA seu ponto tem coordenadas: x = %f, y = %f\n", arbitro.x, arbitro.y);
  Circulo circulo_arbitro;
  circulo_arbitro.centro.x = arbitro.x;
  circulo_arbitro.centro.y = arbitro.y;
  int deslocar;
  printf("Deseja deslocar seu circulo? Atualmente ele esta em (%f, %f).\nResponda com 0 para nao ou com 1 para sim: ", circulo_arbitro.centro.x, circulo_arbitro.centro.y);
  scanf("%i", &deslocar);
  if(deslocar == 1){
    float Dx, Dy;
    printf("Insira o valor que quer deslocar seu circulo a seguir.\n No eixo x: ");
    scanf("%f", &Dx);
    printf("\n No eixo y: ");
    scanf("%f", &Dy);
    printf("Dx: %f, Dy: %f\n", Dx, Dy);
    TransladaCirculo(&circulo_arbitro, Dx, Dy);
    printf("Novo x: %f, Novo y: %f", circulo_arbitro.centro.x, circulo_arbitro.centro.y);
  }
  return(0);
}