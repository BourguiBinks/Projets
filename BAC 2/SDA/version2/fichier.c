#include <stdio.h>
#include <math.h>

int main(){
int a,b,c;
printf("Donne moi un les coefficients d'un polynôme du second degré (dans l'ordre x², x et terme indépendant) et je me charge de calculer le(s) zéro(s)\n");
scanf("%d %d %d", &a, &b ,&c);

float delta = (b*b) - (4*a*c) ;
float racine, racine2;
if(delta < 0){
    printf("Il n'existe pas de zéro réel\n");
    return 0;
}

racine = (-b + sqrt(delta))/ (2*a);
racine2 = (-b - sqrt(delta))/ (2*a);
if (delta == 0 || racine == racine2){
racine = -b / 2*a;
    printf("Le zéro du polynôme %d x² + %d x + %d est %f\n", a, b , c, racine);
}
else{

    printf("Les zéros du polynôme %d x² + %d x + %d sont %f et %f\n", a, b , c, racine, racine2);
}
    return 0;
}