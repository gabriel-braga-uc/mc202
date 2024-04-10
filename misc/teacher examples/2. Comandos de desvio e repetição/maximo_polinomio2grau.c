#include <stdio.h>
#include <float.h>

#define DELTA 0.0001

float maximo_polinomio(float x1,float x2, float y1, float y2,float A, float B, float C, float D, float E, float F, float *xmax, float *ymax)
{
  float max = -FLT_MAX, dx = DELTA, dy = DELTA;
  
  for (float y=y1; y <= y2; y+=dy){
    for (float x=x1; x <= x2; x+=dx){
      float z = A*x*x + B*y*y + 2*C*x*y + D*x + E*y + F;
      if (z > max){
	*xmax = x; *ymax = y;
	max = z;
      }
    }
  }
  return(max);
}

int main()
{
  float x1,y1,x2,y2,xmax,ymax;
  float A, B, C, D, E, F;
  
  printf("Entre com os valores de x1 x2 y1 y2: ");
  scanf("%f %f %f %f",&x1,&x2,&y1,&y2);
  printf("\n");
  printf("Entre com os coeficientes do polinomio A B C D E F: ");
  scanf("%f %f %f %f %f %f",&A,&B,&C,&D,&E,&F);
  printf("\n");

  float max = maximo_polinomio(x1,x2,y1,y2,A,B,C,D,E,F,&xmax,&ymax);
  printf("Máximo %f ocorre em (%.2f,%.2f)\n",max,xmax,ymax);
  
}
