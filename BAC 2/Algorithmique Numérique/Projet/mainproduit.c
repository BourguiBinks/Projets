#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matricecreuse.h"
#include "produit.h"

int main() {
    char familyName[50]; // Supposons que la famille de matrice a un nom de moins de 50 caractères
    printf("Veuillez entrer le nom de famille de la matrice : ");
    scanf("%s", familyName);

    char fileName1[100];
    char fileName2[100];
    sprintf(fileName1, "%s.A.mtx", familyName);
    sprintf(fileName2, "%s.B.mtx", familyName);

    sparseMatrix *matrix1 = NULL;
    sparseMatrix *matrix2 = NULL;

    int verificationResult = CheckAndSort(fileName1, fileName2);

    switch (verificationResult) {
        case -1:
            printf("Erreur lors de la vérification d'un (ou des) fichier(s)!\n");
            return -1;
            break;

        case -2:
            printf("Les deux fichiers sont triés\n");
            int result1Matrix1 = load_sparse_matrix_and_vector(&matrix1, fileName1);
            int result2Matrix2 = load_sparse_matrix_and_vector(&matrix2, fileName2);
            if(result1Matrix1 < 0 || result2Matrix2 < 0){
                return -1;
            }
            break;

        case -3:
            printf("Le premier fichier a été trié\n");
            int result3Matrix1 = load_sparse_matrix_and_vector(&matrix1, "fichier_trieA.mtx");
            int result4Matrix2 = load_sparse_matrix_and_vector(&matrix2, fileName2);
            if(result3Matrix1 < 0 || result4Matrix2 < 0){
                return -1;
            }
            break;

        case -4:
            printf("Le deuxième fichier a été trié\n");
            int result5Matrix1 = load_sparse_matrix_and_vector(&matrix1, fileName1);
            int result6Matrix2 = load_sparse_matrix_and_vector(&matrix2, "fichier_trieB.mtx");
            if(result5Matrix1 < 0 || result6Matrix2 < 0){
                return -1;
            }
            break;

        case -5:
            printf("Les deux fichiers ont été triés\n");
            int result7Matrix1 = load_sparse_matrix_and_vector(&matrix1, "fichier_trieA.mtx");
            int result8Matrix2 = load_sparse_matrix_and_vector(&matrix2, "fichier_trieB.mtx");
            if(result7Matrix1 < 0 || result8Matrix2 < 0){
                return -1;
            }
            break;

        default:
            printf("Erreur :/ \n");
            break;
    }

    // Vérifie que le produit matriciel est calculable.
    if (matrix1->column != matrix2->row) {
        printf("Impossible de réaliser la multiplication matricielle\n");
        return -1;
    }

    multiplication_sparse_matrix(matrix1, matrix2);
    printf("Le résultat de la multiplication a été écrit dans produit.mtx\n");

    // Libérer la mémoire
    free_sparse_matrix(matrix1);

    return 0;
}
