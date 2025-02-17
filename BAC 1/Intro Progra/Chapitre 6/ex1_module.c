#include <stdio.h>
#include "ex1_module.h"
void affiche_bonjour(){
    printf("Bonjour fdp\n");
}
void affiche_bonjour_nfois(unsigned int n){
    for(unsigned int i = 0; i<n; i++)
        printf("Bonjour\n");
}
int affiche_bonjour_nfois2(unsigned int n){
    for(unsigned int i = 0; i<n; i++)
        printf("Bonjour gay\n"); 
        
    return 0;
}