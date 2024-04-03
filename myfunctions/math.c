#include <stdio.h>

int issum(int i, int topofsigma){    /*Integer=1 step summation*/
    if(i == topofsigma){
        return(i);
    }
    else{
        return(i+isum(i+1, topofsigma));
    }
}

float cssum(float i, float topofsigma, float step){  /*Custom step summation*/
    if(i == topofsigma){
        return(i);
    }else if(i > topofsigma){
        return(i - step);
    }
    else{
        return(i+ssum(i+step, topofsigma, step));
    }
}

unsigned long long fat_df_0t20(unsigned long long n){   /*Weak induction standard factorial function (up to n=20)*/
    if(n <= 20 && n >= 0){
        if(n <= 1){
            return(1);
        }else{
            return((fat_df_0t20(n-1)) * n);
        }
    }
    else{ 
        return(0);
    }
}
int main(){
    printf("%i\n", isum(1,5));
    printf("%f\n", ssum(1,5,0.1));
    return 0;
}