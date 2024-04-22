#include <stdio.h>
#include <stdarg.h>

/* Para compilar:

gcc funcao_arg_variavel.c -o funcao_arg_variavel

*/

double multiplica(int num_args, ...);

double multiplica(int num_args, ...) {
  double result = 1.0;
   va_list args; /* lista de argumentos */
   int i;

   va_start(args, num_args); /* prepara a lista para recuperar
				argumentos após num_args */
   for(i = 0; i < num_args; i++) {
     result *= va_arg(args, double); /* recupera o próximo na lista */
   }
   va_end(args); /* finaliza o processo de recuperação */
 
   return(result);
}

int main () {
  
  printf("Resultado da multiplicação %.2lf\n",  multiplica(5,1.5,2.0,3.5,4.4,5.1) );
   
  return 0;
}

