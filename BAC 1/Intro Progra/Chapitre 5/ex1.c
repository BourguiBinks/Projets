#include <stdio.h>
#define n 5
// AFFICHE LES ELEMENTS D'INDINCE IMPAIRS
int main(){
    int tab[n] = {14,55,33,143,51};

   /* for(int i =0; i < 5 ; i++ ){
        if((i%2)!=0)
            printf("%d ", tab[i]);
    }
*/

//AFFICHE LE MIN ET LE MAX D'UN TABLEAU
int min= tab[0];
int max = tab [0];
    for(int i = n-1; i>=0 ; i--){
        if(tab[i]>max)
        max = tab[i];
        else
        min = tab[i];
    }
    printf("Le max est %d et le min est %d\n", max, min );
    return 0;
}