#include <stdio.h>
#include <stdlib.h>
#include "somme.h"
int main(){
    int N = 5;
    int T[] = {3,7,-1,9,7};
    int min_pos ;
    int max_pos ;
    int sum = somme(T,N,&min_pos,&max_pos);
     
     printf("\tSomme :%d, (min_pos,min) : (%d,%d), (max_pos,max),(%d,%d)\n", sum, min_pos, T[min_pos], max_pos, T[max_pos]); 
     return 0;
}