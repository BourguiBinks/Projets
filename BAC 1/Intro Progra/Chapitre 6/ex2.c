#include <stdio.h>

float calcul_impot(float r,unsigned int n){
    float impot;
    if((r/n)<500)
        impot = r/10;
    else 
        impot = r/20;

    return impot;
}
float calcul_revenu_net(float r, unsigned int n){
    float revenu_net = r - calcul_impot(r,n);

    return revenu_net;
}
int main(){
    float revenu;
    unsigned int membres;

    printf("Donne moi ton revenu brut et le nombre de membres dans ta famille :\n");
    scanf("%f %u", &revenu, &membres);

    printf("L'impôt est de %f et le revenu net est %f\n", calcul_impot(revenu,membres), calcul_revenu_net(revenu,membres));
    
    return 0;
}