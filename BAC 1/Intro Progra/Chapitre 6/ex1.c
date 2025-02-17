#include <stdio.h>
#include "ex1_module.h"
int main(){
    int test;
    unsigned int n;
printf("Tape 1 pour un bonjour, tape 2 pour n fois bonjour (indique le nombre de fois) et tape 3 pour pareil que le 2\n");
scanf("%d",&test);
if(test == 1){
    affiche_bonjour();
}
if(test == 2){
    printf("Donne le nombre de bonjour\n");
    scanf("%u",&n);
    affiche_bonjour_nfois(n);
}
if (test == 3){
    printf("Donne le nombre de bonjour\n");
    scanf("%u",&n);
    affiche_bonjour_nfois2(n);
}
    return 0;
}