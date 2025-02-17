#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "matricecreuse.h"

int compareElementsSets(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

// Fonction pour initialiser un ensemble vide
Set createEmptySet(){
    Set set;
    set.elements = NULL;
    set.size = 0;
    return set;
}

// Fonction pour ajouter un élément à l'ensemble (s'il n'est pas déjà présent)
void addToSet(Set *set, int element){
    for (int i = 0; i < set->size; i++){
        if(set->elements[i] == element){
            // L'élément est déjà présent, ne rien faire
            return;
        }
    }

    // Ajouter l'élément à la fin du tableau
    set->size++;
    set->elements = realloc(set->elements, set->size * sizeof(int));
    set->elements[set->size - 1] = element;
}

// Fonction pour afficher les éléments de l'ensemble
void printSet(Set set){
    printf("Ensemble : \n");
    for(int i = 0; i < set.size; i++){
        printf("%d ", set.elements[i]);
    }
    printf("\n");
}

// Fonction pour trier les éléments de l'ensemble
void sortSet(Set *set){
    qsort(set->elements, set->size, sizeof(int), compareElementsSets);
}

int CheckAndSort(const char *fileName, const char *fileName2){
    // Traitement du premier fichier
    FILE *file = fopen(fileName, "r");
    if(!file){
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    int nbrows, nbcolumns, nbElements;
    fscanf(file, "%d %d %d", &nbrows, &nbcolumns, &nbElements);

    elementMatrix *matrix = malloc(nbElements * sizeof(elementMatrix));

    for(int i = 0; i < nbElements; i++){
        fscanf(file, "%d %d %lf", &(matrix[i].row), &(matrix[i].column), &(matrix[i].value));
    }

    fclose(file);

    // Vérifier si les colonnes sont triées pour le premier fichier
    int sort1 = 1;
    for(int i = 1; i < nbElements; i++){
        if(matrix[i].column < matrix[i - 1].column){
            sort1 = 0;
            break;
        }
    }

    // Traitement du deuxième fichier
    FILE *file2 = fopen(fileName2, "r");
    if (!file2){
        perror("Erreur lors de l'ouverture du fichier 2");
        free(matrix);
        return -1;
    }

    int nbrows2, nbcolumns2, nbElements2;
    fscanf(file2, "%d %d %d", &nbrows2, &nbcolumns2, &nbElements2);

    elementMatrix *matrix2 = malloc(nbElements2 * sizeof(elementMatrix));

    for(int i = 0; i < nbElements2; i++){
        fscanf(file2, "%d %d %lf", &(matrix2[i].row), &(matrix2[i].column), &(matrix2[i].value));
    }

    fclose(file2);

    // Vérifier si les colonnes sont triées pour le deuxième fichier
    int sort2 = 1;
    for(int i = 1; i < nbElements2; i++){
        if(matrix2[i].column < matrix2[i - 1].column){
            sort2 = 0;
            break;
        }
    }

    // Comparer les résultats pour déterminer les cas possibles
    if(sort1 && sort2){
        free(matrix);
        free(matrix2);
        return -2;  // Les deux fichiers sont triés
    }else if(!sort1 && sort2){
        // Trier les columns
        qsort(matrix, nbElements, sizeof(elementMatrix), compareElements);

        // Écrire les données triées dans un nouveau fichier
        FILE *sortFile = fopen("fichier_trieA.mtx", "w");
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
        free(matrix2);
        return -3;  // Seul le premier fichier est modifié
    }else if(sort1 && !sort2){
        // Trier les columns
        qsort(matrix, nbElements, sizeof(elementMatrix), compareElements);

        // Écrire les données triées dans un nouveau fichier
        FILE *sortFile2 = fopen("fichier_trieB.mtx", "w");
        if(!sortFile2){
            perror("Erreur lors de la création du fichier trié");
            free(matrix);
            free(matrix2);
            return -1;
        }

        fprintf(sortFile2, "%d %d %d\n", nbrows, nbcolumns, nbElements);

        for(int i = 0; i < nbElements; i++){
            fprintf(sortFile2, "%d %d %.15lf\n", matrix[i].row, matrix[i].column, matrix[i].value);
        }

        fclose(sortFile2);

        free(matrix);
        free(matrix2);
        return -4;  // Seul le deuxième fichier est modifié
    }else{
        // Trier les columns
        qsort(matrix, nbElements, sizeof(elementMatrix), compareElements);

        // Écrire les données triées dans un nouveau fichier
        FILE *sortFile3 = fopen("fichier_trieA.mtx", "w");
        if(!sortFile3){
            perror("Erreur lors de la création du fichier trié");
            free(matrix);
            return -1;
        }

        fprintf(sortFile3, "%d %d %d\n", nbrows, nbcolumns, nbElements);

        for(int i = 0; i < nbElements; i++){
            fprintf(sortFile3, "%d %d %.15lf\n", matrix[i].row, matrix[i].column, matrix[i].value);
        }

        fclose(sortFile3);

        free(matrix);
        free(matrix2);
        qsort(matrix, nbElements, sizeof(elementMatrix), compareElements);

        // Écrire les données triées dans un nouveau fichier
        FILE *sortFile4 = fopen("fichier_trieB.mtx", "w");
        if(!sortFile4){
            perror("Erreur lors de la création du fichier trié");
            free(matrix);
            free(matrix2);
            return -1;
        }

        fprintf(sortFile4, "%d %d %d\n", nbrows, nbcolumns, nbElements);

        for(int i = 0; i < nbElements; i++){
            fprintf(sortFile4, "%d %d %.15lf\n", matrix[i].row, matrix[i].column, matrix[i].value);
        }

        fclose(sortFile4);

        free(matrix);
        free(matrix2);
        return -5;  // Les deux fichiers sont modifiés
    }
}

sparseMatrix *multiplication_sparse_matrix(sparseMatrix *matrix1, sparseMatrix *matrix2){
    assert(matrix1!= NULL && matrix2 != NULL);
    
    int index = 0;
    int index2 = 0;
    double *y = NULL;
    Set set = createEmptySet();
    sparseMatrix *multiplicationMatrix = create_sparse_matrix(set.size, matrix1->row, matrix2->column);
    if(multiplicationMatrix == NULL)
        return NULL;
    multiplicationMatrix->vector->startColumn[0] = 0; 

    for(int i = 0; i < matrix2->column; i++){
        for(int j = matrix2->vector->startColumn[i]; j < matrix2->vector->startColumn[i + 1]; j++){
            int columnA = matrix2->vector->indexRow[j];
            for(int k = matrix1->vector->startColumn[columnA - 1]; k < matrix1->vector->startColumn[columnA]; k++){
                addToSet(&set, matrix1->vector->indexRow[k]);
                // printf("indexrow : %d\n", matrix1->vector->indexRow[k]);
            }
        }
        sortSet(&set);
        // printSet(set);
        //on réalloue les tableaux indexRow et values car nous n'avons pas eu la taille préalablement.
        multiplicationMatrix->vector->indexRow = realloc(multiplicationMatrix->vector->indexRow, (multiplicationMatrix->size + set.size + 1) * sizeof(int));
        multiplicationMatrix->vector->values = realloc(multiplicationMatrix->vector->values, (multiplicationMatrix->size + set.size + 1) * sizeof(double));
        // Vérification de la réallocation
        if(multiplicationMatrix->vector->indexRow == NULL || multiplicationMatrix->vector->values == NULL){
            // Gérer l'erreur, libérer la mémoire, etc.
            free_sparse_matrix(multiplicationMatrix);
            return NULL;
        }

        index = multiplicationMatrix->size;
        //on remplit indexRow de la matrice C.
        while(index < set.size + multiplicationMatrix->size){
            multiplicationMatrix->vector->indexRow[index] = set.elements[index - multiplicationMatrix->size];
            index++;
        }
        //remplit startColumn a partir de l'index 1
        multiplicationMatrix->vector->startColumn[i + 1] = multiplicationMatrix->size + set.size;
        //alloue de la mémoire pour set.size éléments
        y = malloc(set.size * sizeof(double));
        if(y == NULL)
            return NULL;

        for(int l = matrix2->vector->startColumn[i]; l < matrix2->vector->startColumn[i + 1]; l++){
            int column2A = matrix2->vector->indexRow[l];
            for(int m = matrix1->vector->startColumn[column2A - 1]; m < matrix1->vector->startColumn[column2A]; m++){
                double tmp = matrix2->vector->values[l] * matrix1->vector->values[m];
                for(index2 = multiplicationMatrix->size; index2 < multiplicationMatrix->size + set.size; index2++){
                    if(matrix1->vector->indexRow[m] == multiplicationMatrix->vector->indexRow[index2]){
                        y[index2 - multiplicationMatrix->size] += tmp;
                    }

                }
            }
        }
        int index3 = multiplicationMatrix->size;
        while(index3 < set.size + multiplicationMatrix->size){
            multiplicationMatrix->vector->values[index3] = y[index3 - multiplicationMatrix->size];
            // printf("multiplicationMatrix->vector->values[index] : %lf\n", multiplicationMatrix->vector->values[index3]);
            index3++;
        }
        
        multiplicationMatrix->size += set.size;
        free(y);
        set = createEmptySet();
    }
    //désormais toutes les valeurs de multiplicationMatrix sont stockées en mémoire.
    // Appeler la fonction pour sauvegarder le résultat dans un fichier
    int saveResult = filemtx_result(multiplicationMatrix, 1);
    if(saveResult != 0){
        printf("Erreur lors de la sauvegarde du fichier résultat.\n");
        // Gérer l'erreur, libérer la mémoire, etc.
        return NULL;
    }

    return multiplicationMatrix;
}