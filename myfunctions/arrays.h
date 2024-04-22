#ifndef arrays
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* criaCadeia(long tamanho){    
  char *cadeia = (char *)calloc(tamanho+1,sizeof(char));
  cadeia[tamanho]='\0';
  return(cadeia);
}
char* invSeqChar(char *s){
    unsigned int len = strlen(s);
    char* inv_s = criaCadeia(len);
    for(int i = 0; i < len; i++){
        inv_s[i] = s[(len-1) - i];
    }
    return(inv_s);
}
int isPalindrome(char *s){
    char* s_inv = invSeqChar(s);
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        if(s[i] != s_inv[i]){
            return(0);
        }
    }
    return(1);
}

#endif
    //char inv_s[len];
    //inv_s[len] = '\0';
    //for(unsigned int i = 0; i < len; i++){
    //    inv_s[len-(i+1)] = s[i];
    //}
    //return(*inv_s);