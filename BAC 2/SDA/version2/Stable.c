#include "Stable.h"
#include "Sort.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct{
    int value; 
    size_t index;
}element;



//create a tab with two elements
// static int tmpTab[2];
static int (*global_compare)(const void *, size_t i, size_t j);
static void (*global_swap)(void *array, size_t i, size_t j);
static void *array_stablesort;
static size_t *tabIndice;


static int compareIndexes(const void *array, size_t i, size_t j){
    const element *arrayPtr = (const element *)array;
    return arrayPtr[i].value - arrayPtr[j].value;
}

// static int compareIndicesForStable(const void *array, size_t i, size_t j){
//     const element *arrayPtr = (const element *)array;
//     //we want to give to global_compare a int tab and not the structure tab because global_compare uses a int tab.
//     tmpTab[0] = arrayPtr[i].value;
//     tmpTab[1] = arrayPtr[j].value;
//     printf("tmptab : %d\n", tmpTab[0]);
//     printf("tmptab : %d\n", tmpTab[1]);

//     return global_compare(tmpTab, 0, 1);
    

// }

static void swapValues(void *array, size_t i, size_t j){
    element *arrayPtr = (element *)array;
    //Échangez les valeurs à l'indice i et j
    long int tempValue = arrayPtr[i].value;
    arrayPtr[i].value = arrayPtr[j].value;
    arrayPtr[j].value = tempValue;
    // // Échangez les indices à l'indice i et j
    long int tempIndex = arrayPtr[i].index;
    arrayPtr[i].index = arrayPtr[j].index;
    arrayPtr[j].index = tempIndex;
}

bool isSortStable(size_t algo, const int *array, size_t length){
    element *intermediateArray = NULL;
    intermediateArray = malloc(length * sizeof(element));
    if(intermediateArray == NULL)
        return NULL;
    //store the array elements in an intermediate array before sorting.
    for(size_t i = 0; i < length; i++){
        intermediateArray[i].value = array[i];
        intermediateArray[i].index = i;
    }
    printf("\n");
    //sort the storing array
    sort(algo, intermediateArray, length, compareIndexes, swapValues);
    
    //look if the sorting array is stable or no.
    // to do so: look for consecutives values and when you have some, you look if their indexes are increasing or not
    //if they are increasing, stable if not it is not stable.
    for(size_t i = 0; i < length - 1; i++){
        if(intermediateArray[i].value == intermediateArray[i + 1].value && intermediateArray[i].index > intermediateArray[i + 1].index){ // issue : we only look for 2 (quid if 3 consecutive?)

            return false;
        }
    }
    return true;


}

static int compare_new(const void *array, size_t i, size_t j){
    //printf("compare entre %d et %d\n", ((int*)array)[i], ((int*)array)[j]);
    return global_compare(array_stablesort, i, j);
}

static int compare_encore(const void *array2, size_t i, size_t j){
    // printf("compare entre %d et %d\n", ((int*)array2)[i], ((int*)array2)[j]);
    return global_compare(tabIndice, i, j);
}

static void print_array(int* array, size_t length)
{   
    for(size_t i = 0; i < length; i++)
        fprintf(stdout,"%d ", array[i]);
    fprintf(stdout, "\n");
}

static void swap_new(void *array, size_t i, size_t j){
    //Échangez les valeurs à l'indice i et j
    // print_array(array, 10);
    //printf("swap entre %d et %d\n", ((int*)array)[i], ((int*)array)[j]);
    global_swap(array_stablesort, i, j);

    global_swap(array, i, j);

    // printf("Dans le swap :\n");
    // print_array(array, 5);
    // print_array(array, 10);

}
static void swap_encore(void *array2, size_t i, size_t j){
    //Échangez les valeurs à l'indice i et j
    // print_array(array, 10);
    // printf("swap entre %d et %d\n", ((int*)array2)[i], ((int*)array2)[j]);
    global_swap(tabIndice, i, j);

    global_swap(array2, i, j);

    // printf("Dans le swap :\n");
    // print_array(array, 5);
    // print_array(array, 10);

}



void stableSort(size_t algo, void *array, size_t length,
                int (*compare)(const void *, size_t i, size_t j),
                void (*swap)(void *array, size_t i, size_t j))
{
    size_t cpt = 1;
    global_compare = compare;
    global_swap = swap;
    array_stablesort = array;
    // print_array(array_stablesort, length);
    tabIndice = malloc(length * sizeof(size_t));
    if(tabIndice == NULL)
        return;
    
    for(size_t j = 0; j < length; j++){
        ((int *)tabIndice)[j] = j;
    }
    // print_array(tabIndice, length);
    // A modifier/compléter
    sort(algo, tabIndice, length, compare_new, swap_new);
    // printf("Tableau d'indice :\n");
    // print_array(tabIndice, length);

    print_array(array_stablesort, length);
    printf("Avant stabilisation\n");
    print_array(tabIndice, length);
    for(size_t i = 0; i < length - 1; i++){
        // printf("i = %ld\n", i);
        if(global_compare(array_stablesort, i, i + 1) == 0){
            cpt++;
            if(i == length - 2 && cpt > 1){
                printf("Arrivé à la dernière comparaison !\n");
                sort(0, tabIndice + i - cpt + 1, cpt, compare_encore, swap_encore);
                printf("Sous tableau trié (de %ld de longueur %ld) : \n", i - cpt + 1,  cpt);
                print_array(tabIndice, length);
            }
        }else{
            if(cpt > 1){
                //("heyy ca va ?\n");
                sort(0, tabIndice + i - cpt + 1, cpt, compare_encore, swap_encore);
                printf("Sous tableau trié (de %ld de longueur %ld) : \n", i - cpt + 1,  cpt);
                print_array(tabIndice, length);
            }
            cpt = 1;
        }
        // printf("cpt = %ld\n", cpt);

    }
    printf("Apres stabilisation\n");
    print_array(tabIndice, length);

}
