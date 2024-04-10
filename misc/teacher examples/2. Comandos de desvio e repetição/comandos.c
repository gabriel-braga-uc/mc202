#include <stdio.h>

int main()
{
  int a = 10;
  goto A;
  a = 20;
 A: printf("%d\n",a);
}

