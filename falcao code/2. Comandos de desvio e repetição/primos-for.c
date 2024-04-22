#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char Primo(int x)
{
  for (int  y = (int)sqrt(x); (y >= 2); y--){
    if ((x % y)==0)
      return(0); /* false */
  }
  return(1); /* true */
}

void PrimosMenoresOuIguais(int N)
{
  if (N < 2){
    printf("Número inválido\n"); exit(1);
  }

  for (int x = N; (x > 2); x=x-1){
    if (Primo(x)) {
      printf("%d, ",x);
    }
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

