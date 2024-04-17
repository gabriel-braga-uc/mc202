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

Labirinto *LeLabirinto(char *nomearq);
void DestroiLabirinto(Labirinto **L);
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
int main(){
	return 0;
}