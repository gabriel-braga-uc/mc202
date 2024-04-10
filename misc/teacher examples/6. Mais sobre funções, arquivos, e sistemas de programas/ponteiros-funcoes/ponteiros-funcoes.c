#include <stdio.h>
#include <stdarg.h>

typedef float (*Operacao)(float v1, float v2);

float Soma(float v1, float v2)
{
  return(v1+v2);
}

float Produto(float v1, float v2)
{
  return(v1*v2);
}

float ExecutaOperacao(float v1, float v2, Operacao calcula)
{
  return(calcula(v1,v2));
}

int main()
{
  float v1, v2;
  char oper;
  
  printf("Entre com os dois valores e a operação: ");
  scanf("%f %f %c",&v1,&v2,&oper);
  if (oper == '+')
    printf("%f + %f = %f\n",v1,v2,ExecutaOperacao(v1,v2,Soma));
  else /* assumir que é '*' */
    printf("%f + %f = %f\n",v1,v2,ExecutaOperacao(v1,v2,Produto));
    
  return(0);
}
