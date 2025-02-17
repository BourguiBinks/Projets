#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "matricecreuse.h"
#include "valeurpropre.h"
#include "produit.h"


int CheckAndSort2(const char *fileName){
    // Traitement du premier fichier
    FILE *file = fopen(fileName, "r");
    if(!file){
        perror("Erreur lors de l'ouverture du file");
        return -1;
    }

    int nbrows, nbcolumns, nbElements;
    fscanf(file, "%d %d %d", &nbrows, &nbcolumns, &nbElements);

    elementMatrix *matrix = malloc(nbElements * sizeof(elementMatrix));

    for(int i = 0; i < nbElements; i++){
        fscanf(file, "%d %d %lf", &(matrix[i].row), &(matrix[i].column), &(matrix[i].value));
    }

    fclose(file);

    // Vérifier si les colonnes sont triées pour le file
    int sort = 1;
    for(int i = 1; i < nbElements; i++){
        if(matrix[i].column < matrix[i - 1].column){
            sort = 0;
            break;
        }
    }
    if(sort){
        free(matrix);
        return -2;  // Le file est trié
    }
    else{
        // Trier les columns
        qsort(matrix, nbElements, sizeof(elementMatrix), compareElements);

        // Écrire les données triées dans un nouveau file
        FILE *sortFile = fopen("fichier_trie.A.mtx", "w");
        if(!sortFile){
            perror("Erreur lors de la création du fichier trié");
            free(matrix);
            return -1;
        }

        fprintf(sortFile, "%d %d %d\n", nbrows, nbcolumns, nbElements);

        for(int i = 0; i < nbElements; i++){
            fprintf(sortFile, "%d %d %.15lf\n", matrix[i].row, matrix[i].column, matrix[i].value);
        }

        fclose(sortFile);

        free(matrix);

        return -3;  // Le fichier a été modifié
    }
}

sparseMatrix *powerMethod(sparseMatrix *matrix, int maxIterations, double *eigenResult){
    assert(matrix != NULL && maxIterations > 0);
    double norm= 1e-10;

    // Initialisation du vecteur propre initial
    sparseMatrix *eigenVector = create_sparse_matrix(matrix->row, matrix->row, 1);
    eigenVector->vector->startColumn[0] = 0;
    eigenVector->vector->startColumn[1] = matrix->row;

    for(int i = 0; i < matrix->row; i++){
        eigenVector->vector->values[i] = 1.0; // Peut être initialisé autrement selon le besoin
        eigenVector->vector->indexRow[i] = i + 1;
    }

    sparseMatrix *result = NULL;

    for(int i = 0; i < maxIterations; i++){
        result = multiplication_sparse_matrix(matrix, eigenVector);

        double standard = 0;
        for(int j = 0; j < result->size; j++){
            standard += result->vector->values[j] * result->vector->values[j];
        }
        standard = sqrt(standard);

        if(fabs(standard - *eigenResult) < norm){
            break;
        }

        *eigenResult = standard;

        for(int k = 0; k < result->size; k++){
            unsigned m = result->vector->indexRow[k];
            eigenVector->vector->values[m - 1] = result->vector->values[k] / standard;
        }
    }

    // Libération de la mémoire
    free_sparse_matrix(result);

    return eigenVector;
}