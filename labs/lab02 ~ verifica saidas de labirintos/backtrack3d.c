#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
/* gcc backtrack.c cadeias.c -o backtrack */

/* Busca a saída de um labirinto a partir de uma posição inicial,
   andando com vizinhança-6. As posições são de três tipos: ' ' -
   válida, 'X' - inválida, e 'S' - saída. */

typedef struct _ponto {
  int x, y, z;
} Ponto;

typedef struct _labirinto {
  char ***Posicao;
  int nx, ny, nz;
  Ponto entrada, saida;
} Labirinto;

Labirinto *LeLabirinto(char *nomearq)
{
  FILE *fp = fopen(nomearq,"r");
  Labirinto *L = (Labirinto *)calloc(1,sizeof(Labirinto));
  
  fscanf(fp, "%d %d %d\n", &L->nx, &L->ny, &L->nz);
  L->Posicao = (char ***)calloc(L->nz,sizeof(char **));
    for(int z = 0; z < L->nz; z++){
      L->Posicao[z] = (char **)calloc(L->ny, sizeof(char*));
      for(int y = 0; y < L->ny; y++){
        L->Posicao[z][y] = (char *)calloc(L->nx, sizeof(char));
      }
    }
  for(int z=0; z <L->nz; z++){
    for (int y=0; y < L->ny; y++){ 
      for (int x=0; x < L->nx; x++) {
        fscanf(fp,"%c",&L->Posicao[z][y][x]);
        if (L->Posicao[z][y][x]=='E'){
	        L->entrada.x= x; L->entrada.y= y;
	        L->Posicao[z][y][x]='P';
        } else {
	        if (L->Posicao[z][y][x]=='S'){
	          L->saida.x=x;
            L->saida.y=y;
            L->saida.z=z;
	          L->Posicao[z][y][x]='P';
	        }
        }
      }
      fscanf(fp,"\n");
    }
  }

  fclose(fp);
  return(L);
}
void DestroiLabirinto(Labirinto **L)
{
  if ((*L)!=NULL){
    for(int z=0; z < (*L)->nz; z++){
      for (int y=0; y < (*L)->ny; y++){
        free((*L)->Posicao[z][y]);
        free((*L)->Posicao[z]);
        free((*L)->Posicao);
        free((*L));
        (*L) = NULL;
      }
    }
  }
}
bool Backtrack(Labirinto *L, Ponto P)
{
  bool res = false;
  if ((P.z == L->saida.z)&&(P.y == L->saida.y)&&(P.x == L->saida.x)) { 
    res = true; /* solução encontrada */
  } else { /* gera candidatos */
    Ponto *C = (Ponto *)calloc(4,sizeof(Ponto));
    C[0].x = P.x - 1; C[0].y = P.y; C[0].z = P.z;
    C[1].x = P.x + 1; C[1].y = P.y; C[1].z = P.z;
    C[2].x = P.x; C[2].y = P.y - 1; C[2].z = P.z;
    C[3].x = P.x; C[3].y = P.y + 1; C[3].z = P.z;
    C[4].x = P.x; C[4].y = P.y; C[4].z = P.z - 1;
    C[5].x = P.x; C[5].y = P.y; C[5].z = P.z + 1;

    /* Armazena a informação da posição atual para recuperar ela
       depois */
    char valor_original = L->Posicao[P.z][P.y][P.x];
    L->Posicao[P.z][P.y][P.x] = 'X'; /* evita pai e filho se visitarem
				   indefinidamente. Mais ainda,
				   permite tratar caminhos cíclicos,
				   pois ao retornar para um ponto já
				   visitado, ele estará marcado com
				   'X'. Caso contrário, o programa
				   entraria em loop. Na volta da
				   recursão, o valor original deve ser
				   recuperado. */	    
    /* processa os candidatos e a condição (res != true) evita visitar
       todas as posições */

       //PARADA, A CIMA CONVERTIDO PRA 3D, ABAIXO AINDA NÃO
    for (int i=0; (i < 7) && (res != true); i++) {
      /* verifica as restrições */
      if ((C[i].x >= 0)&&(C[i].x < L->nx)&&(C[i].y >= 0)&&(C[i].y < L->ny)&&(C[i].z >= 0)&&(C[i].z < L->nz)){
	      if (L->Posicao[C[i].z][C[i].y][C[i].x] != 'X'){ /* restrição */
	        //printf("Processa (%d,%d)=%c a partir de (%d,%d)\n",C[i].x,C[i].y,L->Posicao[C[i].y][C[i].x],P.x,P.y);
	        res = Backtrack(L,C[i]);
	      }
      }
    }
    L->Posicao[P.z][P.y][P.x] = valor_original; /* retorna ao valor original */
    free(C);
  }
  return(res);
}

int main(int argc, char **argv)
{
  Labirinto *L = NULL;
  
  L = LeLabirinto(argv[1]);

  /* for (int y=0; y < L->ny; y++){  */
  /*   for (int x=0; x < L->nx; x++) { */
  /*     printf("%c",L->Posicao[y][x]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  if (Backtrack(L,L->entrada))
    printf("Encontrou a saída em (%d,%d)\n",L->saida.x,L->saida.y);
  else
    printf("Labirinto sem saída\n");
	   
  return(0);
}
