#include "testa_imagem.h"

/* Para compilar 
   
make testa_imagem

*/

int main(int argc, char **argv)
{
  Imagem *img = NULL, *oimg = NULL;
  Ponto centro;
  float raio;
  Circulo *C  = NULL;
  char **param_circulo = NULL;
  
  if (argc != 4){
    Erro("testa_imagem <nome da imagem de entrada (.ppm)> <x,y,raio do círculo> <nome da imagem saída (.ppm)","main"); 
  }

  img = LeImagemRGB(argv[1]);
  param_circulo = QuebraCadeia(argv[2],",");
  CadeiaParaNumero(param_circulo[1], "float", &centro.x);
  CadeiaParaNumero(param_circulo[2], "float", &centro.y);
  CadeiaParaNumero(param_circulo[3], "float", &raio);
  C = CriaCirculo(centro,raio);
  oimg = DesenhaCirculo(C,img,255,150,50);
  GravaImagemRGB(oimg,argv[3]);
  DestroiImagem(&img);
  DestroiImagem(&oimg);
  DestroiCirculo(&C);
  
  return(0);
}
