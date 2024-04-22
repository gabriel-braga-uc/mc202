#include <stdio.h>
#include <stdlib.h>

float Operacao(float x, float y, char o)
{
  switch(o) {
  case '*':
    return(x*y); 
  case '/':
    if ((-0.00001 < y) && (y < 0.00001)){
      printf("Divisão indefinida\n"); exit(1);
    } else {
      return(x/y);
    }
  case '+':
    return(x+y); 
  case '-':
    return(x-y);
  default:
    printf("Operação não implementada"); exit(2);
  }  
}

int main()
{
  float x,y,res;
  char  o;

  printf("Entre com a operação em {+,-,*,/} e os valores x y: ");
  scanf("%c %f %f",&o,&x,&y);
  printf("\n");
  res = Operacao(x,y,o);
  printf("%.2f %c %.2f = %.2f\n",x,o,y,res);

  return(0);
}

