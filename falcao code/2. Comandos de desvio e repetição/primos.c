#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char Primo(int x)
{
  int  y = (int)sqrt(x);
  while (y >= 2){
    if ((x % y)==0)
      return(0); /* false */
    y--;
  }
  return(1); /* true */
}

void PrimosMenoresOuIguais(int N)
{
  if (N < 2){
    printf("Número inválido\n"); exit(1);
  }

  int x = N;
  while (x > 2) {
    if (Primo(x)) {
      printf("%d, ",x);
    }
    x = x - 1;
  }
  printf("2.\n");
}

int main()
{
  int N;

  printf("Entre com o valor de N: ");
  scanf("%d",&N);
  printf("\n");
  PrimosMenoresOuIguais(N);
  
  return(0);
}

