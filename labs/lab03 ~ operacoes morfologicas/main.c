#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

/*
Esse programa define uma imagem 2D binária com valores 0 e 1 como um array multidimensional 2D (ou matriz) representado por uma struct, cujos elementos da matriz são alocados como nós conectados sequencialmente
na Lista Ligada. O principal objetivo do programa é realizar operações sobre os valores desta imagem considerando seus elementos vizinhos ou adjacentes. A operação de Dilatação considera
o máximo nas comparações entre os valores localizados (ou até) na borda do desenho na matriz com seus valores adajcentes, enquanto a operação de Erosão considera o mínimo.
A combinação das operações de Dilatação e Erosão resultam nas outras operações chamadas Abertura e Fechamento.
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

typedef struct matrizesparsa {
  int    lin, col; /* vao de (0,0) a (nlin-1, ncol-1) */  
  float  valor;
  struct matrizesparsa *direita, *abaixo;
} NoMatrizEsparsa, MatrizEsparsa;

MatrizEsparsa   *LeMatrizEsparsa(char *arq);
MatrizEsparsa   *CriaMatrizEsparsa();
int              NumeroLinhasMatrizEsparsa(MatrizEsparsa *M);
int              NumeroColunasMatrizEsparsa(MatrizEsparsa *M);
bool             MatrizEsparsaVazia(MatrizEsparsa *M);
NoMatrizEsparsa *CriaNoMatrizEsparsa(int lin, int col, float valor);
bool             BuscaElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col, NoMatrizEsparsa **pos);
void             InsereElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col, float valor);
void             DestroiMatrizEsparsa(MatrizEsparsa **M);
void             ImprimeMatrizEsparsa(MatrizEsparsa *M); 


/* Exercicios */

float          RemoveElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col);
MatrizEsparsa *SomaMatrizesEsparsas(MatrizEsparsa *M1, MatrizEsparsa *M2);
MatrizEsparsa *MultiplicaMatrizesEsparsas(MatrizEsparsa *M1, MatrizEsparsa *M2);
MatrizEsparsa *TranspoeMatrizEsparsa(MatrizEsparsa *M);
/* Cria matriz de inteiros com nlin x ncol elementos */
void VerificaSePrecisaDeMaisNosCabecasNasColunas(MatrizEsparsa *M, int col);
void VerificaSePrecisaDeMaisNosCabecasNasLinhas(MatrizEsparsa *M, int lin);
bool BuscaColuna(NoMatrizEsparsa *inicio, NoMatrizEsparsa **pos, int col);
bool BuscaLinha(NoMatrizEsparsa *inicio, NoMatrizEsparsa **pos, int lin);
NoMatrizEsparsa *PosicaoInsercaoNaColuna(MatrizEsparsa *M, int lin, int col);
NoMatrizEsparsa *PosicaoInsercaoNaLinha(MatrizEsparsa *M, int lin, int col);
int **CriaMatrizInt(int nlin, int ncol)
{
  int **m = (int **)calloc(nlin,sizeof(int *));
  
  for (int l=0; l < nlin; l++)
    m[l] = (int *)calloc(ncol,sizeof(int));
  return(m);
}
float *CriaVetorFloat(int n)
{
  float *v = (float *)calloc(n,sizeof(float));
  return(v);
}

/* Libera a memória no heap, reinicializando o ponteiro para NULL */

void DestroiVetorFloat(float **v)
{
  if ((*v) != NULL){
    free(*v);
    *v = NULL;
  }
}

/* Gera número real aleatório em [min,max] */

//double NumeroAleatorio(float min, float max) {
//  double d;
//  d = ((double) rand()) / (double) RAND_MAX;
//  return(min + d * (max - min));
//}

/* Cria vetor com n números aleatórios em [min,max] */

float *VetorFloatAleatorio(int n, float min, float max)
{
  float *v = CriaVetorFloat(n);
  for (int i=0; i < n; i++)
    v[i] = (float) NumeroAleatorio(min,max);
  return(v);
}

/* Imprime vetor */

void ImprimeVetorFloat(float *v, int n)
{
  for(int i=0; i < n; i++)
    printf("%.2f ",v[i]);
  printf("\n");
}
/* Libera a memória no heap, reinicializando o ponteiro para NULL */

void DestroiMatrizInt(int ***m, int nlin)
{
  if ((*m) != NULL){
    for (int l=0; l < nlin; l++)
      free((*m)[l]);
    free(*m);
    *m = NULL;
  }
}

/* Gera número real aleatório em [min,max] */

double NumeroAleatorio(float min, float max) {
  double d;
  d = ((double) rand()) / (double) RAND_MAX;
  return(min + d * (max - min));
}

/* Cria matriz com n números aleatórios em [min,max] */

int **MatrizIntAleatorio(int nlin, int ncol, int min, int max)
{
  int **m = CriaMatrizInt(nlin,ncol);
  for(int l=0; l < nlin; l++){
    for(int c=0; c < ncol; c++)
      m[l][c] = (int) NumeroAleatorio(min,max);
  }
  return(m);
}
  
/* Imprime matriz */

void ImprimeMatrizInt(int **m, int nlin, int ncol)
{
  for(int l=0; l < nlin; l++){
    for(int c=0; c < ncol; c++)
      printf("%03d ",m[l][c]);
    printf("\n");
  }
}
FILE *arquivo_saida_ponteiro = NULL;

typedef struct no_lista_simples
{
    int valor;
    struct no_lista_simples *proximo;
} ListaSimples, NoListaSimples;

typedef struct _pixel
{
    int x;
    int y;
} Pixel;

typedef struct _imagem
{
    int **Posicao;
    int largura;
    int altura;
} Imagem;

// Definindo e inicializando uma variável nula do tipo no_lista_simples que vai auxiliar
// nas operações sobre a estrutura de dados Lista Ligada
ListaSimples *noAtual = NULL;

// Declaração de algumas funções (Opcional)
bool ListaSimplesVazia(ListaSimples *inicio);
bool BuscaElementoListaSimples(ListaSimples *inicio, int elem, NoListaSimples **pos, NoListaSimples **ant);
void InserirElementoNoFimLista(ListaSimples **inicio, int valor);
bool RemoveInicioListaSimples(ListaSimples **inicio, int *elem);
void DestroiListaLigada(ListaSimples **inicio);
NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice);
void Dilatacao(NoListaSimples **noAtual, int n, int m);
void Erosao(NoListaSimples **noAtual, int n, int m);
void Abertura(NoListaSimples **noAtual, int n, int m);
void Fechamento(NoListaSimples **noAtual, int n, int m);

// Função para mostrar erro no console e sair do programa
void Erro(char *msg, char *funcao, ...)
{
    va_list args; /* lista de argumentos */
    char msg_final[4096];

    va_start(args, funcao);         /* inicializa a lista args para recuperar
                           argumentos após o argumento funcao */
    vsprintf(msg_final, msg, args); /* envia a lista inteira de
                       argumentos em args para
                       formatação em msg_final */
    va_end(args);                   /* finaliza o processo de recuperação */

    printf("Erro em %s: %s\n", funcao, msg_final);
    fflush(stdout);
    exit(1);
}

// Função para ler imagem binária de arquivo e usar elementos obtidos na alocação dinâmica da struct apropriada
Imagem *LeImagem(char const *nomearquivo)
{
    FILE *arquivo_ponteiro = fopen(nomearquivo, "r");
    if (arquivo_ponteiro == NULL)
    {
        Erro("Erro na abertura do arquivo\n", "LeImagem", arquivo_ponteiro);
        return NULL;
    }
    Imagem *img = (Imagem *)calloc(1, sizeof(Imagem));

    fscanf(arquivo_ponteiro, "%d %d\n", &img->largura, &img->altura);

    img->Posicao = (int **)calloc(img->altura, sizeof(int *));
    for (int y = 0; y < img->altura; y++)
        img->Posicao[y] = (int *)calloc(img->largura, sizeof(int));

    for (int y = 0; y < img->altura; y++)
    {
        for (int x = 0; x < img->largura; x++)
        {
            char caractere_atual;
            fscanf(arquivo_ponteiro, "%c ", &caractere_atual);

            // precisamos converter os caracteres para um inteiros, então subtraimos por caractere '0' da tabela ASCII
            // Isso funciona porque o valor ASCII dos caracteres ‘0’ a ‘9’ são consecutivos.
            // Logo, subtraindo o valor ASCII de ‘0’ do valor ASCII de qualquer digito caractere deve resultar no equivalente inteiro do digito. Por exemplo,
            // o valor ASCII de ‘1’ é 49 e o valor ASCII de ‘0’ é 48, então 49 - 48 = 1, que é o equivalente inteiro do caractere ‘1’.
            img->Posicao[y][x] = (int)(caractere_atual - '0');
        }
        fscanf(arquivo_ponteiro, "\n");
    }

    fclose(arquivo_ponteiro);
    return (img);
}

// Função para verificar se Lista Ligada Simples possui Nó
bool ListaSimplesVazia(ListaSimples *inicio)
{
    // Área do código

    // Fim da área do código
}

// Função para buscar ultimo Nó dentro de uma Lista Ligada Simples
bool BuscaUltimoElementoListaSimples(ListaSimples *inicio, NoListaSimples **pos, NoListaSimples **ant)
{
    // Área do código

    // Fim da área do código
}

// Função para criar um novo Nó na Lista Ligada
NoListaSimples *CriaNoSimples(int elem)
{
    // Área do código

    // Fim da área do código
}

// Função para inserir um novo Nó depois do último Nó presente na Lista Ligada
void InserirElementoNoFimLista(ListaSimples **inicio, int valor)
{
    // Área do código

    // Fim da área do código
}

// Função para remover primeiro Nó na Lista Ligada
bool RemoveInicioListaSimples(ListaSimples **inicio, int *elem)
{
    // Área do código

    // Fim da área do código
}

// Função para esvaziar a Lista Ligada
void DestroiListaLigada(ListaSimples **inicio)
{
    // Área do código

    // Fim da área do código
}

// Função para desalocar a struct Imagem da memória
void DestroiImagem(Imagem **img)
{
    if ((*img) != NULL)
    {
        for (int y = 0; y < (*img)->altura; y++)
            free((*img)->Posicao[y]);
        free((*img)->Posicao);
        free((*img));
        (*img) = NULL;
    }
}

// Função para pegar um Nó localizado no indice posicional na Lista Ligada
NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice)
{
    // Área do código

    // Fim da área do código
}

Pixel *ObterAdjacentes(Pixel P)
{
    // Área do código
    // Fim da área do código
}

// Função que realiza a operação de dilatação na matriz de números binários
// Essa função recebe o ponteiro para o nó atual na lista, total de linhas 'n'
// e total de colunas 'm' da matriz
void Dilatacao(NoListaSimples **noAtual, int n, int m)
{
    // Área do código

    // Fim da área do código
}

void Erosao(NoListaSimples **noAtual, int n, int m)
{
    int i, j;
    int valor_referencia, valor;
    NoListaSimples *temp = (NoListaSimples *)calloc(n * m, sizeof(NoListaSimples));

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            valor_referencia = 1;
            Pixel P;
            P.x = i;
            P.y = j;
            Pixel *C = ObterAdjacentes(P);

            for (int k = 0; k < 8; k++)
            {
                if ((C[k].x >= 0) && (C[k].y >= 0) && (C[k].x < n) && (C[k].y < m)) // verifica se é uma posição 2D (i,j) válida no domínio da matriz
                {
                    /* Área do código */
                    // Obtenha valor de nó CANDIDATO usando a função ObterNo que recebe o noAtual e indice (i*m + j)
                    /* Fim da área do código */

                    if (valor < valor_referencia) // atualize min se o valor for menor que min
                    {
                        valor_referencia = valor;
                    }
                }
            }

            /* Área do código */

            // atribua valor_referencia para o membro valor do No no array temp.
            // Use indexação no array temp a partir da fórmula (i*m + j) do indice posicional que converte 
            // os indices (i,j) da matriz 2D para um indice da posição do nó correspondente na Lista Ligada.

            /* Fim da área do código */
        }
    }

    // Copia os valores erodidos de volta para a lista original
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {

            /* Área do código */

            // 1 passo) Acesse um nó da lista com ObterNo usando o noAtual e índice considerando as coordenadas (i,j) e dimensão (m) matriz 2D
            // 2 passo) Acesse o valor desse nó obtido
            // 3 passe) Altere esse valor acessado com o valor do nó correspondente no array temp.
            // Lembre que o array temp possui os valores dilatados nesse ponto da função,
            // então apenas acesse o nó no array temp usando o mesmo indice posicional usado no
            // passo 1.

            /* Fim da área do código */
        }
    }

    free(temp);
}

void Abertura(NoListaSimples **noAtual, int n, int m)
{
    /*
    A operação de abertura é realizada primeiro aplicando a erosão, seguida
    pela dilatação. A abertura suaviza o contorno de uma imagem, quebra
    estreitamentos e elimina projeções finas.
    */

    // Área do código

    // Fim da área do código
}

void Fechamento(NoListaSimples **noAtual, int n, int m)
{
    /*
    A operação de fechamento é o inverso da abertura. Primeiro, aplica-se a
    dilatação e, em seguida, a erosão. O fechamento também suaviza o contorno
    de uma imagem, mas, ao contrário da abertura, o fechamento geralmente
    funde estreitamentos e preenche buracos (valores '0s' com valores '1s' adjacentes) pequenos.
    */

    // Área do código

    // Fim da área do código
}

// essa função mostra a Lista Ligada em um formato mais legível de matrizes numéricas
void VisualizarListaComoMatriz(NoListaSimples *cabeca, int linhas, int colunas)
{
    NoListaSimples *noAtual = cabeca;
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (noAtual != NULL)
            {
                printf("%d ", noAtual->valor);
                char caractere_valor_atual = noAtual->valor + '0';
                if (arquivo_saida_ponteiro != NULL)
                {
                    fprintf(arquivo_saida_ponteiro, "%c ", caractere_valor_atual);
                }

                // sprintf(str, "%d", num); // convert multiple digit integer to string
                noAtual = noAtual->proximo;
            }
        }
        printf("\n");
        if (arquivo_saida_ponteiro != NULL)
        {
            fprintf(arquivo_saida_ponteiro, "\n");
        }
    }
}

// Função para preencher uma Lista Ligada com os elementos obtidos de cada posição da Imagem
void PreencherListaLigadaComImagemBinaria(Imagem *imagem_binaria)
{
    int ncolunas = imagem_binaria->altura;
    int nlinhas = imagem_binaria->largura;
    for (int i = 0; i < ncolunas; i++)
    {
        for (int j = 0; j < nlinhas; j++)
        {
            InserirElementoNoFimLista(&noAtual, imagem_binaria->Posicao[i][j]);
        }
    }
}

// Função para exibir todos os resultados do programa no console
void ExibirResultados(Imagem *imagem_binaria, int NUM_COLUNAS, int NUM_LINHAS)
{
    printf("Dilation\n");
    if (arquivo_saida_ponteiro != NULL)
    {
        fprintf(arquivo_saida_ponteiro, "%s\n", "Dilation");
    }
    Dilatacao(&noAtual, NUM_COLUNAS, NUM_LINHAS);
    VisualizarListaComoMatriz(noAtual, NUM_LINHAS, NUM_COLUNAS);
    DestroiListaLigada(&noAtual);
    PreencherListaLigadaComImagemBinaria(imagem_binaria);

    printf("Erosion\n");
    if (arquivo_saida_ponteiro != NULL)
    {
        fprintf(arquivo_saida_ponteiro, "%s\n", "Erosion");
    }
    Erosao(&noAtual, NUM_COLUNAS, NUM_LINHAS);
    VisualizarListaComoMatriz(noAtual, NUM_LINHAS, NUM_COLUNAS);
    DestroiListaLigada(&noAtual);
    PreencherListaLigadaComImagemBinaria(imagem_binaria);

    printf("Opening\n");
    if (arquivo_saida_ponteiro != NULL)
    {
        fprintf(arquivo_saida_ponteiro, "%s\n", "Opening");
    }
    Abertura(&noAtual, NUM_COLUNAS, NUM_LINHAS);
    VisualizarListaComoMatriz(noAtual, NUM_LINHAS, NUM_COLUNAS);
    DestroiListaLigada(&noAtual);
    PreencherListaLigadaComImagemBinaria(imagem_binaria);

    printf("Closing\n");
    if (arquivo_saida_ponteiro != NULL)
    {
        fprintf(arquivo_saida_ponteiro, "%s\n", "Closing");
    }
    Fechamento(&noAtual, NUM_COLUNAS, NUM_LINHAS);
    VisualizarListaComoMatriz(noAtual, NUM_LINHAS, NUM_COLUNAS);
    DestroiListaLigada(&noAtual);
}
bool BuscaColuna(NoMatrizEsparsa *inicio, NoMatrizEsparsa **pos, int col)
{
  while (((*pos)->col < col)&&((*pos)->direita != inicio)){
    (*pos) = (*pos)->direita;
  }
  if ((*pos)->col == col) 
    return(true);
  else
    return(false);
}

/* Retorna em pos o ponteiro do elemento da linha lin, encontrado
   apartir de inicio. */

bool BuscaLinha(NoMatrizEsparsa *inicio, NoMatrizEsparsa **pos, int lin)
{
  while (((*pos)->lin < lin)&&((*pos)->abaixo != inicio)){
    (*pos) = (*pos)->abaixo;
  }
  if ((*pos)->lin == lin) 
    return(true);
  else
    return(false);
}

/* Retorna em pos o ponteiro do elemento encontrado na matriz */

bool BuscaElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col, NoMatrizEsparsa **pos)
{
  NoMatrizEsparsa *inicio;

  *pos = M->direita;
  if (BuscaColuna(M,pos,col)){ 
    inicio = *pos;
    if (BuscaLinha(inicio,pos,lin)){
      return(true);
    }
  }

  return(false);
}

void VerificaSePrecisaDeMaisNosCabecasNasColunas(MatrizEsparsa *M, int col)
{
  int ncol = NumeroColunasMatrizEsparsa(M),c;
  NoMatrizEsparsa *p,*q; 

  if (ncol-1 < col) { /* necessita de mais nos cabecas nas colunas */
    p = M; 
    while(p->direita != M) /* vai para a ultima posicao da lista de nos
			  cabecas das colunas */
      p=p->direita;

      for (c=ncol; c <= col; c++) { /* aumenta a lista de nos cabecas
				       das colunas */
	q = CriaNoMatrizEsparsa(-1,c,0.0);
	p->direita = q;
	q->direita = M;
	p      = q;
      }
    }
}

void VerificaSePrecisaDeMaisNosCabecasNasLinhas(MatrizEsparsa *M, int lin)
{
  int nlin = NumeroLinhasMatrizEsparsa(M),l;
  NoMatrizEsparsa *p,*q; 

  if (nlin-1 < lin) { /* necessita de mais nos cabecas nas linhas */
    p = M; 
    while(p->abaixo != M) /* vai para a ultima posicao da lista de
			    nos cabecas das linhas */
      p=p->abaixo;

    for (l=nlin; l <= lin; l++) { /* aumenta a lista de nos cabecas
				     das linhas */
      q = CriaNoMatrizEsparsa(l,-1,0.0);
      p->abaixo = q;
      q->abaixo = M;
      p      = q;
    }
  }
}

NoMatrizEsparsa *PosicaoInsercaoNaColuna(MatrizEsparsa *M, int lin, int col)
{
  NoMatrizEsparsa *pos,*pos_ant,*inicio_col;

  /* identifica apontador de inicio da coluna para insercao */

  pos = M->direita; 
  while (pos->col != col)
    pos = pos->direita;
  
  inicio_col = pos;

  /* percorre os elementos da coluna para identificar o ponto de
     inserçao */
  
  pos_ant = pos; pos=pos->abaixo;    
  while ((pos->lin < lin)&&(pos!=inicio_col)){  
    pos_ant = pos;
    pos     = pos->abaixo;
  }

  return(pos_ant);
}

NoMatrizEsparsa *PosicaoInsercaoNaLinha(MatrizEsparsa *M, int lin, int col)
{
  NoMatrizEsparsa *pos,*pos_ant,*inicio_lin;

  /* identifica apontador de inicio da linha para insercao */

  pos = M->abaixo; 
  while (pos->lin != lin)
    pos = pos->abaixo;
    
  inicio_lin = pos; 

  /* percorre os elementos da linha para identificar o ponto de
     inserçao */

  pos_ant = pos; pos=pos->direita;  
  while ((pos->col < col)&&(pos != inicio_lin)){       
      pos_ant = pos; 
      pos     = pos->direita;
    }

  return(pos_ant);
}


/* --------------------- Publicas ---------------------------------*/

NoMatrizEsparsa *CriaNoMatrizEsparsa(int lin, int col, float valor)
{
  NoMatrizEsparsa *q = (NoMatrizEsparsa *)calloc(1,sizeof(NoMatrizEsparsa));
  q->lin    = lin; 
  q->col    = col; 
  q->valor  = valor; 
  q->direita    = q;
  q->abaixo = q;

  return(q);
}

MatrizEsparsa *CriaMatrizEsparsaVazia()
{
  NoMatrizEsparsa *M=CriaNoMatrizEsparsa(-1,-1,0.0); /* no cabeca */

  return(M);
}

int NumeroLinhasMatrizEsparsa(MatrizEsparsa *M)
{
  int nlin=0; 
  NoMatrizEsparsa *p=M;

  while (p->abaixo != M) {
    nlin++;
    p = p->abaixo;
  }

  return(nlin);
}

int NumeroColunasMatrizEsparsa(MatrizEsparsa *M)
{
  int ncol=0; 
  NoMatrizEsparsa *p=M;

  while (p->direita != M) {
    ncol++;
    p = p->direita;
  }

  return(ncol);
}

bool MatrizEsparsaVazia(MatrizEsparsa *M)
{
  if (M != NULL){
    if ((M->abaixo == M)&&(M->direita == M))
      return(true);
    else
      return(false);
  } else 
    return(false);
}

MatrizEsparsa *LeMatrizEsparsa(char *arq)
{
  FILE *fp=fopen(arq,"r");
  int i, nelems, lin, col;
  float valor;
  MatrizEsparsa *M=CriaMatrizEsparsaVazia();
  
  fscanf(fp,"%d\n",&nelems);
  for (i=0; i < nelems; i++) {
    fscanf(fp,"%d %d %f\n",&lin,&col,&valor);
    InsereElemMatrizEsparsa(M,lin,col,valor);    
  }
  fclose(fp);

  return(M);
}



void InsereElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col, float valor)
{
  NoMatrizEsparsa *pos, *linha_pos_ant, *coluna_pos_ant;

  if (BuscaElemMatrizEsparsa(M,lin,col,&pos)){ /* atualiza valor, caso o
						  elemento ja esteja na
						  matriz */
    printf("Atualizando valor de %f para %f em (%d,%d)\n",pos->valor,valor,lin,col);
    pos->valor = valor;

  } else {
    VerificaSePrecisaDeMaisNosCabecasNasColunas(M,col);
    VerificaSePrecisaDeMaisNosCabecasNasLinhas(M,lin);
    coluna_pos_ant = PosicaoInsercaoNaColuna(M, lin, col);
    linha_pos_ant  = PosicaoInsercaoNaLinha(M, lin, col);

    /* Cria e insere novo no */

    pos = CriaNoMatrizEsparsa(lin,col,valor); /* cria o novo no */
    pos->abaixo            = coluna_pos_ant->abaixo;
    coluna_pos_ant->abaixo = pos;
    pos->direita               = linha_pos_ant->direita;
    linha_pos_ant->direita     = pos;

    //    ImprimeMatrizEsparsa(M);  
  }
}

void DestroiMatrizEsparsa(MatrizEsparsa **M)
{
  MatrizEsparsa   *aux=*M;
  NoMatrizEsparsa *p, *q, *inicio;

  /* libera memoria dos nos internos */

  inicio = aux->direita;
  while (inicio != aux) {
    p = inicio->abaixo;
    while (p != inicio) { /* enquanto a coluna nao estiver vazia */
      q = p->abaixo;
      free(p);
      p = q;
    }
    inicio = inicio->direita;
  }

  /* libera nos cabecas das colunas */

  inicio = aux->direita;
  while (inicio != aux){
    q = inicio->direita;
    free(inicio);
    inicio = q;
  }

  /* libera nos cabecas das linhas */

  inicio = aux->abaixo;
  while (inicio != aux){
    q = inicio->abaixo;
    free(inicio);
    inicio = q;
  }
  
  free(aux); /* libera no cabeca da matriz */
  *M = NULL; 
}

void ImprimeMatrizEsparsa(MatrizEsparsa *M)
{
  int c,l,ncol,nlin;
  NoMatrizEsparsa *p;

  ncol = NumeroColunasMatrizEsparsa(M);
  nlin = NumeroLinhasMatrizEsparsa(M);

  for (l=0; l < nlin; l++) {    
    for (c=0; c < ncol; c++) {
      if (BuscaElemMatrizEsparsa(M,l,c,&p))
	printf("%5.2f ",p->valor);
      else
	printf("%5.2f ",0.0);
    }
    printf("\n");
  }
  printf("\n");
}
int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        Erro(
            "%s <arquivo texto de entrada> [<arquivo texto de saida>]\n"
            "Por exemplo, ./main ./arq1.in ./arq1.out\n",
            "main", argv[0]);
    }
    char *arquivo_saida = argv[2];
    if (arquivo_saida != NULL)
    {
        arquivo_saida_ponteiro = fopen(argv[2], "w");
        if (arquivo_saida_ponteiro == NULL)
        {
            printf("Falha na abertura do arquivo");
            return -1;
        }
    }

    Imagem *imagem_binaria = NULL;

    imagem_binaria = LeImagem(argv[1]);

    int NUM_LINHAS = imagem_binaria->largura;
    int NUM_COLUNAS = imagem_binaria->altura;

    PreencherListaLigadaComImagemBinaria(imagem_binaria);

    ExibirResultados(imagem_binaria, NUM_COLUNAS, NUM_LINHAS);

    DestroiImagem(&imagem_binaria);
    if (arquivo_saida_ponteiro != NULL)
    {
        fclose(arquivo_saida_ponteiro);
    }

    return 0;
}
