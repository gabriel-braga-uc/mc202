#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct _ponto {
  int x, y, z;
} Ponto;
typedef struct _labirinto {
  char*** Posicao;
  int nx, ny, nz, ne, ns;
  Ponto entradas[200];
  Ponto saidas[200];
  Ponto entrada, saida;
} Labirinto;

Labirinto* LeLabirinto(char* nomearq){  
  FILE* fp = fopen(nomearq, "r");
  Labirinto* L = (Labirinto*)calloc(1, sizeof(Labirinto));

  fscanf(fp, "%d %d %d %d\n", &L->nx, &L->ny, &L->nz, &L->ne);
  L->Posicao = (char***)calloc(L->nz, sizeof(char**));
  for (int z = 0; z < L->nz; z++) {
    L->Posicao[z] = (char**)calloc(L->ny, sizeof(char*));
    for (int y = 0; y < L->ny; y++) {
      L->Posicao[z][y] = (char*)calloc(L->nx, sizeof(char));
    }
  }
  int aux_e = 0;
  int aux_s = 0;
  //printf("%d", L->nz);
  for (int z = 0; z < L->nz; z++) {
    for (int y = 0; y < L->ny; y++) {
      //printf("\n");
      for (int x = 0; x < L->nx; x++) {
        fscanf(fp, "%c", &L->Posicao[z][y][x]);
        //printf("%c", L->Posicao[z][y][x]);
        if (L->Posicao[z][y][x] == 'E') {
          //printf("\n <!> DEBUG E <!>\n");
          L->entradas[aux_e].x = x; L->entradas[aux_e].y = y; L->entradas[aux_e].z = z;
          //L->Posicao[z][y][x] = 'P';
          aux_e++;
        }
        else {
          if (L->Posicao[z][y][x] == 'S') {
            //printf("\n <!> DEBUG S <!>\n");
            L->ns++;
            L->saidas[aux_s].x = x;
            L->saidas[aux_s].y = y;
            L->saidas[aux_s].z = z;
            aux_s++;
            L->Posicao[z][y][x] = 'P';
          }
        }
        fscanf(fp, "\n");
      }
    }
  }
  //int www = 5;
  //("\nnx %d, ny %d, nz %d, ne %d, ns %d\n", L->nx, L->ny, L->nz, L->ne, L->ns);
  fclose(fp);
  return(L);
}
void DestroiLabirinto(Labirinto** L)
{
  if ((*L) != NULL) {
    for (int z = 0; z < (*L)->nz; z++) {
      for (int y = 0; y < (*L)->ny; y++) {
        free((*L)->Posicao[z][y]);
        free((*L)->Posicao[z]);
        free((*L)->Posicao);
        free((*L));
        (*L) = NULL;
      }
    }
  }
}


bool Backtrack(Labirinto* L, Ponto P){
  //printf("\n <!> DEBUG <!>\n");
  bool res = false;
  for(int k = 0; k < L->ns; k++){
      L->saida.x = L->saidas[k].x; L->saida.y = L->saidas[k].y; L->saida.z = L->saidas[k].z;
      if ((P.z == L->saida.z) && (P.y == L->saida.y) && (P.x == L->saida.x)) {
        return(true);
      }
    }
    Ponto* C = (Ponto*)calloc(6, sizeof(Ponto));
    C[0].x = P.x - 1;
    C[0].y = P.y;
    C[0].z = P.z;
    C[1].x = P.x + 1;
    C[1].y = P.y;
    C[1].z = P.z;
    C[2].x = P.x;
    C[2].y = P.y - 1;
    C[2].z = P.z;
    C[3].x = P.x;
    C[3].y = P.y + 1;
    C[3].z = P.z;
    C[4].x = P.x;
    C[4].y = P.y;
    C[4].z = P.z - 1;
    C[5].x = P.x;
    C[5].y = P.y;
    C[5].z = P.z + 1;
    char valor_original = L->Posicao[P.z][P.y][P.x];
    L->Posicao[P.z][P.y][P.x] = 'X';
    for (int i = 0; (i < 6) && (res != true); i++) {
      //printf("\n!!!!!\n");
      if ((C[i].x >= 0) && (C[i].x < L->nx) && (C[i].y >= 0) && (C[i].y < L->ny) && (C[i].z >= 0) && (C[i].z < L->nz)) {
        if (L->Posicao[C[i].z][C[i].y][C[i].x] != 'X') {
          //printf("! ");
          res = Backtrack(L, C[i]);
        }
      }
    }
  L->Posicao[P.z][P.y][P.x] = valor_original;
  free(C);
  return(res);
}

int main(int argc, char** argv)
{
  Labirinto* L = NULL;
  L = LeLabirinto(argv[1]);
  //for(int k = 0; k < L->ns; k++){
  //  printf("\n%d, %d, %d\n", L->saidas[k].x, L->saidas[k].y, L->saidas[k].z);
  //}
  for (int i = 0; i < L->ne; i++) {
    L->entrada.x = L->entradas[i].x;
    L->entrada.y = L->entradas[i].y;
    L->entrada.z = L->entradas[i].z;
    //printf("E: %d, %d, %d\n", L->entrada.x, L->entrada.y, L->entradas[i].z);
    if (Backtrack(L, L->entrada)) {
      printf("[Entrada %d] Saída encontrada!\n", i);
    }
    else {
      printf("[Entrada %d] Saída não encontrada!\n", i);
      }
  }
  return(0);
}
