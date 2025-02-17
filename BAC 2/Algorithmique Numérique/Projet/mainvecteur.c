#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "matricecreuse.h"
#include "valeurpropre.h"
#include "produit.h"

int main(){
    char fileName[100];  // Vous pouvez ajuster la taille selon vos besoins
    int maxIterations;

    printf("Entrez le nom du fichier (par exemple, brand.A.mtx) : ");
    scanf("%s", fileName);
    // printf("Nom fichier : %s\n", fileName);
    // Vérifiez que le fichier a l'extension .mtx et le suffixe "A.mtx"
    size_t len = strlen(fileName);
    if(len < 6 || strcmp(&fileName[len - 6], ".A.mtx") != 0){
        printf("Le fichier doit avoir l'extension .mtx et le suffixe 'A.mtx'\n");
        return -1;
    }

    printf("Entrez le nombre d'itérations : ");
    scanf("%d", &maxIterations);
    // printf("Nb itérations : %d\n", maxIterations);

    sparseMatrix *matrix = NULL;
    int result = CheckAndSort2(fileName);

    if (result == -2){
        printf("Le fichier est déjà trié\n");
        int resultLoad1 = load_sparse_matrix_and_vector(&matrix, fileName);
        if(resultLoad1 < 0){
            printf("Erreur de chargement de la matrice!\n");
        }
    } else if(result == -3){
        printf("Le fichier a été trié\n");
        int resultLoad1 = load_sparse_matrix_and_vector(&matrix, "fichier_trie.A.mtx");
        if(resultLoad1 < 0){
            printf("Erreur de chargement de la matrice !\n");
        }
    } else{
        printf("Erreur lors de la vérification du fichier\n!");
        return -1;
    }

    double eigenResult = 1;
    sparseMatrix *result2 = powerMethod(matrix, maxIterations, &eigenResult);
    printf("Valeur propre : %lf\n", eigenResult);
    filemtx_result(result2, 2);

    // Libérer la mémoire
    free_sparse_matrix(result2);

    return 0;
}
