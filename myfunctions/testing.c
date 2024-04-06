#include "math.h"
#include "arrays.h"
int main(){
    //int n = 5;
    //char s[] = "Pizzaria";
    //printf("Fatorial de '%llu' é '%llu'.\n", n, fat(n));
    char s[] = "ooowoo08";
    char* s_inv = invSeqChar(s);
    printf("%s\n", invSeqChar(s));
    printf("%i\n", isPalindrome(s));
    return(0);
}