char invSeqChar(char* s){
    unsigned int len = sizeof(s);
    char inv_s[len];
    for(unsigned int i = 0; i < len; i++){
        inv_s[len-(i+1)] = s[i];
    }
    return(*inv_s);
}