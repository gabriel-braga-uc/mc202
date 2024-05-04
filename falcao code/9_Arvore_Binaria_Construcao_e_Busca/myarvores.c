#include <stdlib.h>
#include <stdio.h>

typedef struct _ArvoreBinaria{
    char info;
    struct _ArvoreBinaria *dir, *esq;
} ArvoreBin, NoArvoreBin;

ArvoreBin *CriaArvoreBin(char s);
void InsereNoArvoreBin(ArvoreBin **p, char s);
int BuscaArvoreBinIterativo(char s, ArvoreBin **p);
int BuscaArvoreBinRecursivo(char s, ArvoreBin **p);


ArvoreBin *CriaArvoreBin(char s){
    ArvoreBin *no = (ArvoreBin*)calloc(1, sizeof(ArvoreBin));
    no->info = s;
    return(no);
}

void InsereNoArvoreBin(ArvoreBin **p, char s){
    *p = CriaArvoreBin(s);
}

int BuscaArvoreBinIterativo(char s, ArvoreBin **p){
    
}


int main(){
    ArvoreBin *p = CriaArvoreBin('B');
    InsereNoArvoreBin(&(p->esq), 'A');
    InsereNoArvoreBin(&(p->dir), 'C');
    InsereNoArvoreBin(&(p->esq->esq), 'D');
    return 0;
}