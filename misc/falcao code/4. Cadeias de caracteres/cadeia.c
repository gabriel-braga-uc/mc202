#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *s1   = "MC202"; // cadeia no heap para leitura apenas
  char s2[6] = {'M','C','2','0','2','\0'}; // na pilha
  char *s3 = (char *)calloc(6,sizeof(char)); // no heap
  char  s4[] = "MC202"; // na pilha
  
  // s3 = "MC202"; /* O mesmo que s3 = s1, não deve ser feito. */
  s3[0]='M'; s3[1]='C'; s3[2]='2'; s3[3]='0'; s3[4]='2'; s3[5]='\0';
  
  printf("%s %s %s %s\n",s1,s2,s3,s4);

  return(0);
}

