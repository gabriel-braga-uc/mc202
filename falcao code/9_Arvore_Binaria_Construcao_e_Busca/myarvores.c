#include <stdlib.h>
#include <stdio.h>

typedef struct _ArvoreBinaria{
    char info;
    struct _ArvoreBinaria *dir, *esq;
} ArvoreBin, NoArvoreBin;

ArvoreBin *CriaArvoreBin(char s);
void InsereNoArvoreBin(ArvoreBin **p, char s);
int BuscaArvoreBinRecursivo(char s, ArvoreBin **p);


ArvoreBin *CriaArvoreBin(char s){
    ArvoreBin *no = (ArvoreBin*)calloc(1, sizeof(ArvoreBin));
    no->info = s;
    return(no);
}

void InsereNoArvoreBin(ArvoreBin **p, char s){
    *p = CriaArvoreBin(s);
}

int BuscaArvoreBinRecursivo(char s, ArvoreBin **p){
    if((*p)->info == s){
        return(1);
    }else if((*p)->esq == NULL && (*p)->esq == NULL){
        return(0);
    }else{
        int a, b;
        if((*p)->esq != NULL){
            a = BuscaArvoreBinRecursivo(s, &((*p)->esq));
        }
        if((*p)->dir != NULL){
            b = BuscaArvoreBinRecursivo(s, &((*p)->esq));   
        }
        if(a == 1 || b == 1){
            return(1);
        }
        else{
            return(0);
        }
    }
}


int main(){
    ArvoreBin *p = CriaArvoreBin('B');
    InsereNoArvoreBin(&(p->esq), 'A');
    InsereNoArvoreBin(&(p->dir), 'C');
    InsereNoArvoreBin(&(p->esq->esq), 'D');
    InsereNoArvoreBin(&(p->esq->esq->dir), 'W');
    printf("%d", BuscaArvoreBinRecursivo('W', &p));
    return 0;
}