
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char test[] = "53.134.145.253 1";
    char * piece = strtok(test, " ");
    printf("%s\n", piece);
    piece = strtok(NULL, " ");
    printf("%s\n", piece);
    return 0;
}