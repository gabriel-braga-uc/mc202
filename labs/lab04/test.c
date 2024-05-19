#include <stdio.h>
#include <stdlib.h>


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
    printf("n: %d\npre: %s\n in: %s", n2, pre, in);
    return 0;
}