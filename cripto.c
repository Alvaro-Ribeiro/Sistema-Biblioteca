#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

void cripto(FILE **entrada, int k){
    char c;
    int a;
    fscanf((*entrada),"%c",&c);
    while(c != '$'){
        if(c == '\n'){
            fscanf(*entrada,"%c",&c);
        }
        fseek(*entrada,-1,SEEK_CUR);
        a = c;
        if(a+k>126){
            fprintf(*entrada,"%c",(c+k)-95);
        }
        else{
            fprintf(*entrada,"%c",(c+k));
        }
        fscanf(*entrada,"%c",&c);
    }
}

void descripto(FILE **saida, int k){
    char c;
    int b;
    fscanf((*saida),"%c",&c);
    while(c != '$'){
        if(c == '\n'){
            fscanf(*saida,"%c",&c);
        }
        b = c;
        fseek(*saida,-1,SEEK_CUR);
        if(b-k < 32){
            fprintf(*saida,"%c",(c-k)+95);
        }
        else{
            fprintf(*saida,"%c",(c-k));
        }
        fscanf(*saida,"%c",&c);
    }
}
