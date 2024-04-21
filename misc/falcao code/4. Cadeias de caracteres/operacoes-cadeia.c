#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/* Se não foi definido, defina o tipo booleano */

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

/* Prototipagem das funções: permite que elas sejam encontradas
   independente da ordem em que são declaradas */

void   Erro(char *msg, char *funcao);
long   ComprimentoCadeia(char *cadeia);
char  *CopiaCadeia(char *cadeia, long pos_inicial, long pos_final);
bool   CadeiasIguais(char *cadeia1, char *cadeia2);
bool   BuscaPadraoProximaOcorrencia(char *cadeia, char *padrao, long *pos);
long   NumeroOcorrenciasPadrao(char *cadeia, char *padrao);
char  *CriaCadeia(long tamanho);
void   DestroiCadeia(char **cadeia);
bool   CadeiaNumerica(char *cadeia);
char  *MinusculasParaMaiusculas(char *cadeia);
void   CadeiaParaNumero(char *cadeia, char *tipo, void *num);
char  *NumeroParaCadeia(void *num, char *tipo);
char **QuebraCadeia(char *cadeia, char *delim);

/*----- Declaração das funções ------------------------*/

/* Imprime mensagem de erro e a função onde ela ocorreu */

void Erro(char *msg, char *funcao) 
{
  printf("Erro em %s: %s\n",funcao,msg);
  exit(1);
}

/* Calcula o comprimento útil de uma cadeia (não conta a posição do
   '\0'). Equivale a strlen() */

long ComprimentoCadeia(char *cadeia)
{

  // Complete
}

/* Cria nova cadeia com parte de outra. Funções relacionadas são
   strcpy e strncpy */

char *CopiaCadeia(char *cadeia, long pos_inicial, long pos_final)
{
  long comp_cadeia = ComprimentoCadeia(cadeia);

  /* Ajusta parâmetros fora do intervalo */
  
  if (pos_inicial < 0)
    pos_inicial = 0;

  if ((pos_final < 0)||(pos_final>=comp_cadeia))
    pos_final=comp_cadeia-1;

  /* Verifica erro para parâmetros no intervalo correto */
  
  if (pos_inicial > pos_final){
    char msg[200];
    sprintf(msg,"Posição inicial %ld não pode ser maior do que posição final %ld\n",pos_inicial,pos_final);
    Erro(msg,"CopiaCadeia");
  }

  /* Cria a cópia */

  // Complete

  return(copia_cadeia);
}


/* Verifica se duas cadeias são iguais, retornando 1 (verdadeiro) ou 0
   (falso). Relacionada com strcmp */

bool CadeiasIguais(char *cadeia1, char *cadeia2)
{
  long comp_cadeia = ComprimentoCadeia(cadeia1);
  if (comp_cadeia!=ComprimentoCadeia(cadeia2))
    return(false);
  else {

    // Complete

  }

  return(true);
}

/* Busca a próxima ocorrência de um padrão na cadeia. Se existir,
   retorna verdadeiro e sua posição inicial na variável pos. Caso
   contrário, retorna falso. */


bool BuscaPadraoProximaOcorrencia(char *cadeia, char *padrao, long *pos)
{
  long comp_cadeia = ComprimentoCadeia(cadeia);
  long comp_padrao = ComprimentoCadeia(padrao);

  do {
    if (cadeia[*pos] == padrao[0]){ /* detecta o primeiro caracter do
				       delimitador e verifica se
				       trata-se de uma ocorrência. */


      // Complete


    }    
    (*pos)++;    
  } while ((*pos) < (comp_cadeia - comp_padrao));

  return(false); /* não encontrou o padrão */
}

/* Calcula o número de ocorrências de um dado padrão em uma cadeia */

long NumeroOcorrenciasPadrao(char *cadeia, char *padrao)
{
  long num_ocorr = 0, pos = 0, comp_padrao = ComprimentoCadeia(padrao);

  while(BuscaPadraoProximaOcorrencia(cadeia, padrao,&pos)){

    // Complete

  }

  return(num_ocorr);
}

/* Cria uma cadeia vazia */

char *CriaCadeia(long tamanho)
{
  if (tamanho <= 0)
    Erro("Tamanho inválido","CriaCadeia");
    
  char *cadeia = (char *)calloc(tamanho+1,sizeof(char));
  cadeia[tamanho]='\0';
  return(cadeia);
}

/* Libera a área da cadeia na memória heap */

void DestroiCadeia(char **cadeia)
{
  if ((*cadeia) != NULL){
    free(*cadeia);
    (*cadeia)=NULL; 
  }
}

/* Verifica se os caracteres de uma cadeia são dígitos de 0 a 9, ou um
   ponto decimal. */

bool CadeiaNumerica(char *cadeia)
{
  for (long i=0; i < ComprimentoCadeia(cadeia); i++)
    if (((cadeia[i]!=46)&&(cadeia[i]<48))||(cadeia[i]>57))
      return(false);
  return(true);
}

/* Converte letras minúsculas em maiúsculas */

char *MinusculasParaMaiusculas(char *cadeia)
{
  long comp_cadeia = ComprimentoCadeia(cadeia);
  char *maiusculas = CriaCadeia(comp_cadeia);
  
  for (long i=0; i < comp_cadeia; i++){
    if ((cadeia[i]>=97)&&(cadeia[i]<=122)) /* se for letra minúscula */
      maiusculas[i] = cadeia[i]-32; /* converte para maiúscula */
    else
      maiusculas[i] = cadeia[i]; /* apenas copia o caracter */
  }

  return(maiusculas);
}

/* Converte uma cadeia numérica para número */

void CadeiaParaNumero(char *cadeia, char *tipo, void *num)
{
  if (!CadeiaNumerica(cadeia))
    Erro("Cadeia não numérica","CadeiaParaNumero");
	 
  // Complete
}

/* Converte número em cadeia numérica */

char *NumeroParaCadeia(void *num, char *tipo)
{
  char *cadeia = CriaCadeia(30);
  if (CadeiasIguais(tipo,"long")){
    sprintf(cadeia,"%ld",*((long *)num));
  }else{
    if (CadeiasIguais(tipo,"unsigned long")){
      sprintf(cadeia,"%lu",*((unsigned long *)num));
    }else{
      if (CadeiasIguais(tipo,"int")){
	sprintf(cadeia,"%d",*((int *)num));
      }else{
	if (CadeiasIguais(tipo,"unsigned int")){
	  sprintf(cadeia,"%u",*((unsigned int *)num));
	} else {
	  if (CadeiasIguais(tipo,"float")){
	    sprintf(cadeia,"%f",*((float *)num));
	  } else {
	    if (CadeiasIguais(tipo,"double")){
	      sprintf(cadeia,"%lf",*((double *)num));
	    } else {
	      if (CadeiasIguais(tipo,"long double")){
		sprintf(cadeia,"%Lf",*((long double *)num));
	      } else {
		Erro("tipo inválido","NumeroParaCadeia");
	      }
	    }
	  }
	}
      }
    }
  }
  return(cadeia);
}

/* Quebra a cadeia nos delimitadores, gerando as partes em um vetor de
   cadeias de caracteres. A primeira posição do vetor contém o número
   de partes. */

char **QuebraCadeia(char *cadeia, char *delim)
{
  long ndelim = 0, comp_delim = ComprimentoCadeia(delim);
  long pos = 0, pos_ant = 0;
  char **partes;

  ndelim = NumeroOcorrenciasPadrao(cadeia,delim);
  
  if (ndelim > 0){
    partes = (char **)calloc(ndelim+2,sizeof(char *));
    long tamanho = ndelim+1;
    partes[0]    = NumeroParaCadeia(&tamanho,"long");
    long i       = 1;
    pos          = pos_ant = 0; 
    while(BuscaPadraoProximaOcorrencia(cadeia, delim,&pos)){

      // Complete

    }
    if (cadeia[pos]!=delim[0]){ /* o usuário esqueceu delimitador após
				   o último campo */
      pos = pos + comp_delim;
    }
    partes[i] = CopiaCadeia(cadeia,pos_ant,pos-1);
  } else {
    partes    = (char **)calloc(1,sizeof(char *));
    long tamanho = 0;
    partes[0]    = NumeroParaCadeia(&tamanho,"long");
  }

  return(partes);
}

int main()
{
  char   opt = 'c';
  char   cadeia[200];
  char   delim[50];
  char  *maiusculas=NULL;
  double num;
  int    i;
  
  while (opt == 'c') {

   printf("Digite: \n");
   printf("1: Entrar com uma cadeia de caracteres\n"); 
   printf("2: Quebrar a cadeia por delimitador\n");
   printf("3: Converte letras minúsculas em maiúsculas\n");
   printf("4: Converte cadeia numérica para número real\n");

   scanf("%[^\n]c",&opt);
   setbuf(stdin,NULL); /* Limpa o buffer do teclado que está com o
			  \n. */
   
   switch(opt) {
   case '1':     
     printf("Entre com uma cadeia de caracteres: ");
     scanf("%[^\n]s",cadeia);
     setbuf(stdin,NULL);
     break;
     
   case '2':
     printf("Entre com um delimitador: ");
     scanf("%[^\n]s",delim);
     setbuf(stdin,NULL); 
     char **partes = QuebraCadeia(cadeia,delim);
     long nelems;
     CadeiaParaNumero(partes[0],"long",&nelems);
     for (long i=1; i <= nelems; i++)
       printf("%s\n",partes[i]);
     for (int i=0; i <= nelems; i++)
       DestroiCadeia(&partes[i]);
     free(partes);   
     break;

   case '3':     
     maiusculas = MinusculasParaMaiusculas(cadeia);
     printf("Maiúsculas: %s\n",maiusculas);
     free(maiusculas);
     break;

   case '4':     
     CadeiaParaNumero(cadeia,"double",&num);
     printf("Conversão para %lf\n",num);     
     break;

   default:     
     printf("Opção inválida\n");
   }

   printf("Digite c para continuar ou qualquer outro caracter para sair\n");
   scanf("%[^\n]c",&opt);
   setbuf(stdin,NULL);
  }

  return(0);
}
