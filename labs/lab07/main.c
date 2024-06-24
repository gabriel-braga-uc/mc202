#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
    char * tempstr = (char*)calloc(32, sizeof(char));
    FILE * fp;
    fp = fopen(argv[1], "r");
    int nnos = atoi(fgets(tempstr, 32, fp));
    fclose(fp);
    printf("%d", nnos);
    return 0;
}