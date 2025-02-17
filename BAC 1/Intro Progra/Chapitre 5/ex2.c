#include <stdio.h>

int main(){
    int matrice_1[2][2]={{1, 3},
                         {5, 4}};
    int matrice_2[2][2]= {{3,6},
                         {2, 1}};
    int matrice_3[2][2];

    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            matrice_3[i][j] = matrice_1[i][j]+matrice_2[i][j];
            
        }
    }
    for(int k = 0;k<2;k++){
        for(int l = 0; l<2;l++){
            printf("%d ", matrice_3[k][l]);
        }
        printf("\n");
    }
    return 0;
}