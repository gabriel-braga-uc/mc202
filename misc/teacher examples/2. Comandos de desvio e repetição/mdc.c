#include <stdio.h>
#include <stdlib.h>

int MDC(int m, int n)
{
  if ((m <= 0)||(n <= 0)){
    printf("valores inválidos\n");
    exit(1);
  }
    
  int x = m, y = n, r; 
  do {
    r = x % y;
    x = y; y = r;
  } while (r != 0);

  return(x);
}

int main()
{
  int m, n;

  printf("Entre com os valores m n: ");
  scanf("%d %d",&m,&n);
  printf("\n");
  int res = MDC(m,n);
  printf("MDC(%d,%d) = %d\n",m,n,res);

  return(0);
}

