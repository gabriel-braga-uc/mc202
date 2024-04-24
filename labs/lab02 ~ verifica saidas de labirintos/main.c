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
Labirinto* LeLabirinto(char* nomearq)
{
  FILE* fp = fopen(nomearq, "r");
  Labirinto* L = (Labirinto*)calloc(1, sizeof(Labirinto));

  fscanf(fp, "%d %d %d %d\n", &L->nx, &L->ny, &L->nz, &L->ne);
  L->nx = L->nx - 1;
  L->ny = L->ny - 1;
  L->nz = L->nz - 1;
  L->Posicao = (char***)calloc(L->nz, sizeof(char**));
  for (int z = 0; z < L->nz; z++) {
    L->Posicao[z] = (char**)calloc(L->ny, sizeof(char*));
    for (int y = 0; y < L->ny; y++) {
      L->Posicao[z][y] = (char*)calloc(L->nx, sizeof(char));
    }
  }
  int aux = 0;
  for (int z = 0; z < L->nz; z++) {
    for (int y = 0; y < L->ny; y++) {
      for (int x = 0; x < L->nx; x++) {
        fscanf(fp, "%c", &L->Posicao[z][y][x]);
        if (L->Posicao[z][y][x] == 'E') {
          L->entradas[aux].x = x; L->entradas[aux].y = y; L->entradas[aux].z = z;
          L->Posicao[z][y][x] = 'P';
        }
        else {
          if (L->Posicao[z][y][x] == 'S') {
            L->saidas[aux].x = x; L->saidas[aux].y = y; L->saidas[aux].z = z;
            L->ns++;
            L->Posicao[z][y][x] = 'P';
          }
        }
      }
      fscanf(fp, "\n");
    }
  }
  printf("\nnx %d, ny %d, nz %d, ne %d, ns %d", L->nx, L->ny, L->nz, L->ne, L->ns);
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
bool Backtrack(Labirinto* L, Ponto P)
{
  bool res = false;
  if ((P.z == L->saida.z) && (P.y == L->saida.y) && (P.x == L->saida.x)) {
    res = true;
  }
  else {
    Ponto* C = (Ponto*)calloc(4, sizeof(Ponto));
    C[0].x = P.x - 1; C[0].y = P.y; C[0].z = P.z;
    C[1].x = P.x + 1; C[1].y = P.y; C[1].z = P.z;
    C[2].x = P.x; C[2].y = P.y - 1; C[2].z = P.z;
    C[3].x = P.x; C[3].y = P.y + 1; C[3].z = P.z;
    C[4].x = P.x; C[4].y = P.y; C[4].z = P.z - 1;
    C[5].x = P.x; C[5].y = P.y; C[5].z = P.z + 1;

    char valor_original = L->Posicao[P.z][P.y][P.x];
    L->Posicao[P.z][P.y][P.x] = 'X';
    for (int i = 0; (i < 7) && (res != true); i++) {
      if ((C[i].x >= 0) && (C[i].x < L->nx) && (C[i].y >= 0) && (C[i].y < L->ny) && (C[i].z >= 0) && (C[i].z < L->nz)) {
        if (L->Posicao[C[i].z][C[i].y][C[i].x] != 'X') {
          res = Backtrack(L, C[i]);
        }
      }
    }
    L->Posicao[P.z][P.y][P.x] = valor_original;
    free(C);
  }
  printf("test1");
  return(res);
}

int main(int argc, char** argv)
{
  //for (int i = 10; i > 0; i--) {
  //  printf("Sexo %d", i);
  //}
  Labirinto* L = NULL;
  L = LeLabirinto(argv[1]);
  for (int i = 0; i < L->ne; i++) {
    if (Backtrack(L, L->entradas[i])) {
      printf("[Entrada %d] Saída encontrada!)\n", i);
    }
    else {
      printf("[Entrada %d] Saída não encontrada!)\n", i);
    }
  }
  printf("test");
  return(0);
}
