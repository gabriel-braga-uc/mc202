#include <stdio.h>

void TrocaValor(int *a, int *b)
{
  int c = *a;
  *a = *b;
  *b = c;
}

int main()
{
  int a, b;

  printf("Entre com a e b: ");
  scanf("%d %d",&a,&b);
  TrocaValor(&a,&b);
  printf("Valores trocados: a=%d b=%d\n",a,b);
  return(0);
}


