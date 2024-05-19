#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct _node_ {
    char in;
    int grau;
    struct _node_ *esq;
    struct _node_ *dir;
} node;

node * createNode(char in);
void CreateNodePutLeft(char in, node ** root);
void CreateNodePutRight(char in, node ** root);
node *CreateFromPreAndIn(node ** p, char *pre, char *in);
int altura(node *T);
void VisitaOrdemSimetrica(node *T, char **s);


void VisitaOrdemSimetrica(node *T, char **s){
  if (T != NULL) {
    VisitaOrdemSimetrica(T->esq, s);
    printf("\n%c: %d", T->in, T->grau);
    (*s) = (*s) + strlen(*s);
    VisitaOrdemSimetrica(T->dir, s);
  }
}
node * createNode(char c){
    node * p = (node*)calloc(1, sizeof(node));
    p->grau = 0;
    p->dir = NULL;
    p->esq = NULL;
    p->in = c;
    return p;
}

void CreateNodePutRight(char in, node ** root){
    node * inserindo = createNode(in);
    (*root)->dir = inserindo;
}
void CreateNodePutLeft(char in, node ** root){
    node * inserindo = createNode(in);
    (*root)->esq = inserindo;
}
node *CreateFromPreAndIn(node ** p, char *pre, char *in){
    node * root = createNode(pre[0]);
    if(strlen(pre) == 0 || strlen(in) == 0){
        return NULL;
    }
    int mid = 0;
    int aux = strlen(pre);
    for(int i = 0; i < aux; i++){
        if(in[i] == pre[0]){
            mid = i;
            break;
        }
    }
    char * out1 = (char*)calloc(aux/2 + 1, sizeof(char));
    char * out2 = (char*)calloc(aux/2 + 1, sizeof(char));
    char * out3 = (char*)calloc(aux/2 + 1, sizeof(char));
    char * out4 = (char*)calloc(aux/2 + 1, sizeof(char));
    for(int i = 0; i < mid; i++){
          out1[i] = pre[i+1];
    }
    for(int i = 0; i < mid; i++){
          out2[i] = in[i];
    }
    aux = aux - 1;
    for(int i = 0; i+mid < aux; i++){
          out3[i] = pre[mid + i + 1];
    }
    for(int i = 0; i+mid < aux; i++){
          out4[i] = in[mid + i + 1];
    }
    root->esq = CreateFromPreAndIn(&root, out1, out2);
    root->dir = CreateFromPreAndIn(&root, out3, out4);
    if(root->dir != NULL){
        root->grau++;
    }
    if(root->esq != NULL){
        root->grau++;
    }
    return root;
}
int altura(node * root) {
    // Get the height of the tree
    if (root == NULL)
        return 0;
    else {
        int hesq = altura(root->esq);
        int hdir = altura(root->dir);
        if (hesq >= hdir)
            return hesq + 1;
        else
            return hdir + 1;
    }
}
int main(int argc,char *argv[]){
    FILE * fp;
    fp = fopen(argv[1], "r");
    char * n = (char*)calloc(52, sizeof(char));
    fgets(n, 52, fp);
    char * pre = (char*)calloc(52, sizeof(char));
    fgets(pre, 52, fp);
    fclose(fp);
    FILE * fp2;
    fp = fopen(argv[2], "r");
    char * a = (char*)calloc(52, sizeof(char));
    fgets(a, 52, fp);
    free(a);
    char * in = (char*)calloc(52, sizeof(char));
    fgets(in, 52, fp);
    fclose(fp);
    int n2 = atoi(n);
    node * p = CreateFromPreAndIn(&p, pre, in);
    //printf("%c\n", p->esq->dir->dir->in); 
    printf("Altura da arvore: %d\nGrau de cada nó em percurso simétrico:", altura(p));
    VisitaOrdemSimetrica(p, &in);
    return 0;
}
