#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char str[] = "M-C-2-0-2";
    /* Retorna o primeiro token, mas cuidado: troca o delimitador por
       '\0', então se imprimir str sairá M. */
    char* token = strtok(str, "-");

    /* Para acessar e imprimir os demais caracteres, usa-se NULL no
       lugar da string para achar o próximo delimitador -- totalmente
       não intuitiva. */

    while (token != NULL) {
        printf(" %s\n", token);
        token = strtok(NULL, "-");
    }

    return 0;
}
