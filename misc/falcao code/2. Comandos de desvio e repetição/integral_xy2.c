#include <stdio.h>

#define DELTA 0.0001

float integral_xy2(float x1,float x2, float y1, float y2)
{
  float area = 0.0, dx = DELTA, dy = DELTA;
  
  for (float y=y1; y <= y2-dy/2; y+=dy){
    float da=0.0;
    for (float x=x1; x <= x2-dx/2; x+=dx){
      da += ((x+dx/2)*(y+dy/2)*(y+dy/2)*dx);
    }
    area += da*dy;
  }
  return(area);
}

int main()
{
  float x1,y1,x2,y2;
  
  printf("Entre com os valores de x1 x2 y1 y2: ");
  scanf("%f %f %f %f",&x1,&x2,&y1,&y2);
  printf("\n");

  printf("Area %f\n",integral_xy2(x1,x2,y1,y2));
  
}
