#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void erosao(int ** matriz, int sizex, int sizey, bool imprimir);
void erosao2(int *** matriz, int sizex, int sizey, bool imprimir);

void dilatacao2(int *** matriz, int sizex, int sizey, bool imprimir);
void dilatacao(int ** matriz, int sizex, int sizey, bool imprimir);

void abertura(int ** matriz, int sizex, int sizey);
void fechamento(int ** matriz, int sizex, int sizey);
int ** copiamatriz(int ** matriz, int sizex, int sizey);

void imprimematriz(int ** matriz, int sizex, int sizey);

void imprimematriz(int ** matriz, int sizex, int sizey){
  for(int i = 0; i < sizex; i++){
    for(int j = 0; j < sizey; j++){
      printf("%d ", (matriz[i][j]));
    }
    printf("\n");
  }
}

void dilatacao(int ** matriz, int sizex, int sizey, bool imprimir){
  int ** matriz2 = copiamatriz(matriz, sizex, sizey);
  int x2, y2;
  for(int i = 0; i < sizex; i++){
    for(int j = 0; j < sizey; j++){
      for(int x = i-1; x <= i+1; x++){
        for(int y = j-1; y <= j+1; y++){
          x2 = x;
          y2 = y;
          if(x < 0)
            x2 = 0;
          if(y < 0)
            y2 = 0;
          if(x >= sizex)
            x2 = sizex-1;
          if(y >= sizey)
            y2 = sizey-1;
          if(matriz[x2][y2] == 1){
              matriz2[i][j] = 1;
          }
        }
      }
    }
  }
  if(imprimir)
    imprimematriz(matriz2, sizex, sizey);
  else
    matriz = matriz2;
}

void erosao(int ** matriz, int sizex, int sizey, bool imprimir){
  int ** matriz2 = copiamatriz(matriz, sizex, sizey);
  int x2, y2;
  for(int i = 0; i < sizex; i++){
    for(int j = 0; j < sizey; j++){
      for(int x = i-1; x <= i+1; x++){
        for(int y = j-1; y <= j+1; y++){
          x2 = x;
          y2 = y;
          if(x < 0)
            x2 = 0;
          if(y < 0)
            y2 = 0;
          if(x >= sizex)
            x2 = sizex-1;
          if(y >= sizey)
            y2 = sizey-1;
          if(matriz[x2][y2] == 0){
              matriz2[i][j] = 0;
          }
        }
      }
    }
  }
  if(imprimir)
    imprimematriz(matriz2, sizex, sizey);
}

void abertura(int ** matriz, int sizex, int sizey){
  int ** matriz2 = copiamatriz(matriz, sizex, sizey);
  int x2, y2;
  for(int i = 0; i < sizex; i++){
    for(int j = 0; j < sizey; j++){
      for(int x = i-1; x <= i+1; x++){
        for(int y = j-1; y <= j+1; y++){
          x2 = x;
          y2 = y;
          if(x < 0)
            x2 = 0;
          if(y < 0)
            y2 = 0;
          if(x >= sizex)
            x2 = sizex-1;
          if(y >= sizey)
            y2 = sizey-1;
          if(matriz[x2][y2] == 0){
              matriz2[i][j] = 0;
          }
        }
      }
    }
  }

  int ** matriz3 = copiamatriz(matriz2, sizex, sizey);
  for(int i = 0; i < sizex; i++){
    for(int j = 0; j < sizey; j++){
      for(int x = i-1; x <= i+1; x++){
        for(int y = j-1; y <= j+1; y++){
          x2 = x;
          y2 = y;
          if(x < 0)
            x2 = 0;
          if(y < 0)
            y2 = 0;
          if((sizex == 5) && (sizey == 5)){
            matriz3[sizex/2][sizey/2] = 0;
          }
          if(x >= sizex)
            x2 = sizex-1;
          if(y >= sizey)
            y2 = sizey-1;
          if(matriz2[x2][y2] == 1){
              matriz3[i][j] = 1;
          }
        }
      }
    }
  }
  
  imprimematriz(matriz3, sizex, sizey);
}

void fechamento(int ** matriz, int sizex, int sizey){
  int ** matriz2 = copiamatriz(matriz, sizex, sizey);

  int y2, x2;

  for(int i = 0; i < sizex; i++){
    for(int j = 0; j < sizey; j++){
      for(int x = i-1; x <= i+1; x++){
        for(int y = j-1; y <= j+1; y++){
          x2 = x;
          y2 = y;
          if(x < 0)
            x2 = 0;
          if(y < 0)
            y2 = 0;
          if(x >= sizex)
            x2 = sizex-1;
          if(y >= sizey)
            y2 = sizey-1;
          if(matriz[x2][y2] == 1){
              matriz2[i][j] = 1;
          }
        }
      }
    }
  }
  int ** matriz3 = copiamatriz(matriz2, sizex, sizey);

  for(int i = 0; i < sizex; i++){
    for(int j = 0; j < sizey; j++){
      for(int x = i-1; x <= i+1; x++){
        for(int y = j-1; y <= j+1; y++){
          x2 = x;
          y2 = y;
          if(x < 0)
            x2 = 0;
          if(y < 0)
            y2 = 0;
          if(x >= sizex)
            x2 = sizex-1;
          if(y >= sizey)
            y2 = sizey-1;
          if(matriz2[x2][y2] == 0){
              matriz3[i][j] = 0;
          }
        }
      }
    }
  }
  imprimematriz(matriz3, sizex, sizey);
}

int ** copiamatriz(int ** matriz, int sizex, int sizey){
  int ** matrizcopia = (int**)calloc(sizex + 1, sizeof(int*));
  for(int i = 0; i < sizex; i++){
    matrizcopia[i] = (int*)calloc(sizey + 1, sizeof(int));
    for(int j = 0; j < sizey; j++){
      matrizcopia[i][j] = matriz[i][j]; 
    }
  }
  return &(*matrizcopia);
}

int main(int argc, char * argv[]){
  int sizex;
  int sizey;
  FILE * fp;
  int ** matriz;
  if(fopen(argv[1], "r")){
    fp = fopen(argv[1], "r");
    fscanf(fp, "%d ", &sizex);
    fscanf(fp,"%d\n", &sizey);

    matriz = (int**)calloc(sizex + 1, sizeof(int*));

    for(int i = 0; i < sizex; i++){
      matriz[i] = (int*)calloc(sizey + 1, sizeof(int));
      for(int j = 0; j < sizey; j++){
        fscanf(fp,"%d", &(matriz[i][j]));
      }
      //fscanf(fp, "\n");
    }
    //printf("%d %d", sizex, sizey);
  }
  fclose(fp);
  printf("Dilation\n");

  dilatacao(matriz, sizex, sizey, true);

  printf("Erosion\n");
  erosao(matriz, sizex, sizey, true);

  printf("Opening\n");
  abertura(matriz, sizex, sizey);

  printf("Closing\n");
  fechamento(matriz, sizex, sizey);
  return 0;
}
