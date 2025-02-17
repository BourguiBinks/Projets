#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matricecreuse.h"

int compareElements(const void *a, const void *b){
    return ((elementMatrix *)a)->column - ((elementMatrix *)b)->column;
}

sparseMatrix *create_sparse_matrix(int size, int row, int column){
    sparseMatrix *matrix = malloc(sizeof(sparseMatrix));
    if(matrix == NULL){
        return NULL;
    }

    matrix->vector = malloc(sizeof(sparseVector));
    if(matrix->vector == NULL){
        free(matrix);
        return NULL;
    }

    matrix->vector->startColumn = malloc(sizeof(int) * column);
    if(matrix->vector->startColumn == NULL){
        free(matrix->vector);
        free(matrix);
        return NULL;
    }

    matrix->vector->indexRow = malloc(sizeof(int) * size);
    if(matrix->vector->indexRow == NULL){
        free(matrix->vector->startColumn);
        free(matrix->vector);
        free(matrix);
        return NULL;
    }

    matrix->vector->values = malloc(sizeof(double) * size);
    if(matrix->vector->values == NULL){
        free(matrix->vector->indexRow);
        free(matrix->vector->startColumn);
        free(matrix->vector);
        free(matrix);
        return NULL;
    }

    matrix->row = row;
    matrix->column = column;
    matrix->size = size;

    return matrix;
}

void free_sparse_matrix(sparseMatrix *matrix){
    assert(matrix != NULL);
    free(matrix->vector->startColumn);
    free(matrix->vector->indexRow);
    free(matrix->vector->values);
    free(matrix->vector);
    free(matrix);
}

int filemtx_result(sparseMatrix *matrix, int choice){
    assert(matrix != NULL);
    char *file = NULL;
    if(choice == 1){
        file = "produit.mtx";
    }
    else if(choice == 2){
        file = "vecteur.mtx";
    }
    
    FILE *fp = fopen(file, "w");
    if(fp == NULL){
        free(matrix);
        fclose(fp);
        return -2;
    }
    fprintf(fp, "%d %d %d\n", matrix->row, matrix->column, matrix->size);
    for(int j = 0; j < matrix->column; j++){
        for(int i = matrix->vector->startColumn[j]; i < matrix->size; i++){
            if(i == matrix->vector->startColumn[j + 1])
                break;
            fprintf(fp, "%d %d %.15lf\n", matrix->vector->indexRow[i], j + 1, matrix->vector->values[i]);
            // printf("matrix->vector->values[i] : %d\n", matrix->vector->values[i]);
        }
    }
    fclose(fp);
    return 0;
}

int load_sparse_matrix_and_vector(sparseMatrix **matrix, char *filename){
    assert(matrix != NULL && filename != NULL);    
    int size, row, column = 0;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Ici 1 \n");
        return -2; 
    }
    if(fscanf(fp, "%d %d %d", &row, &column, &size) != 3){
        fclose(fp);
        printf("Ici 2 \n");
        return -2; 
    }
    // création d'une instance de la structure sparseMatrix
    *matrix = create_sparse_matrix(size, row, column);
    if(*matrix == NULL){
        fclose(fp);
        printf("Ici 3 \n");
        return -3; 
    }
    int tmp, cmp, j = 0;  
    int currentColumn = 0;  
    for(int i = 0; i < size; i++){
        if(fscanf(fp, "%d %d %lf", &(*matrix)->vector->indexRow[i], &tmp, &(*matrix)->vector->values[i]) != 3){
            // free(*matrix); ou //free_sparse_matrix(*matrix)
            fclose(fp);
            printf("Ici 4 \n");
            return -1;
        }
        j++;

        if(tmp != cmp){
            if(j > (*matrix)->column){
                // free_sparse_matrix(*matrix);
                fclose(fp);
                printf("Ici 5 \n");
                return -1;
            }
            //Ajustez l'indice de début
            (*matrix)->vector->startColumn[currentColumn] = i;  // Ajustez l'indice de début
            // printf("startColumn[%d] = %d\n", currentColumn, i);
            j = 0;
            currentColumn++;
        }
        // printf("indexRow[%d] = %d\n, values[%d] = %.2lf\n", i, (*matrix)->vector->indexRow[i], i, (*matrix)->vector->values[i]);
        cmp = tmp;

    }
    // printf("currentcolumn : %d\n", currentColumn);
    //on rajoute a la derniere case de startColumn le nombre d'éléments totaux cfr slide.
    (*matrix)->vector->startColumn[currentColumn] = size;
    
    // printf("startColumn dernier element : [%d] = %d\n", currentColumn, size);

    fclose(fp);
    return 0;
}

