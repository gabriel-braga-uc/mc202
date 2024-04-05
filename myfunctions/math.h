#ifndef math
int isum(int i, int upper_index){    /*Integer=1 step summation*/
    if(i == upper_index){
        return(i);
    }
    else{
        return(i+isum(i+1, upper_index));
    }
}
float csum(float i, float upper_index, float step){  /*Custom step summation*/
    if(i == upper_index){
        return(i);
    }else if(i > upper_index){
        return(i - step);
    }
    else{
        return(i+csum(i+step, upper_index, step));
    }
}
unsigned long long fat(unsigned long long n){   /*Weak induction standard factorial function (up to n=20)*/
    if(n <= 20 && n >= 0){
        if(n <= 1){
            return(1);
        }else{
            return((fat(n-1)) * n);
        }
    }
    else{ 
        return(0);
    }
}
#endif
