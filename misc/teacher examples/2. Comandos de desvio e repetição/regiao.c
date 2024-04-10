#include <stdio.h>

int Regiao(float x1, float x2, float y1, float y2, float x, float y)
{
  if ((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)){
    return(3);
  } else {
    if (((x < x1)  && (y1 <= y) && (y <= y2)) ||
	((x > x2)  && (y1 <= y) && (y <= y2)) ||
	((y < y1)  && (x1 <= x) && (x <= x2)) ||
	((y > y2)  && (x1 <= x) && (x <= x2)) ) {
      return(2);
    } else { /* R1 */
      return(1);
    }
  }
}

int main()
{
  float x,y,x1,x2,y1,y2;
  int regiao;

  printf("Entre com os valores x y do ponto: ");
  scanf("%f %f",&x,&y);
  printf("\n");
  printf("Entre com os valores de x1 x2 y1 y2: ");
  scanf("%f %f %f %f",&x1,&x2,&y1,&y2);
  printf("\n");
  regiao = Regiao(x1,x2,y1,y2,x,y);
  printf("(%.2f,%.2f) está na região R%d\n",x,y,regiao);

  return(0);
}

