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
static int tmpTab[2];
static int (*globalCompare)(const void *, size_t i, size_t j);
static void (*globalSwap)(void *array, size_t i, size_t j);


static int compareIndexes(const void *array, size_t i, size_t j){
    const element *arrayPtr = (const element *)array;
    return arrayPtr[i].value - arrayPtr[j].value;
}

static int compareIndicesForStable(const void *array, size_t i, size_t j){
    const element *arrayPtr = (const element *)array;
    //we want to give to globalCompare a int tab and not the structure tab because globalCompare uses a int tab.
    tmpTab[0] = arrayPtr[i].value;
    tmpTab[1] = arrayPtr[j].value;
    printf("tmptab : %d\n", tmpTab[0]);
    printf("tmptab : %d\n", tmpTab[1]);

    return globalCompare(tmpTab, 0, 1);
    

}

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
    // printf("yo\n");
    element *intermediateArray = NULL;
    // printf("yo\n");
    intermediateArray = malloc(length * sizeof(element));
    // printf("yo\n");
    if(intermediateArray == NULL)
        return NULL;
    //store the array elements in an intermediate array before sorting.
    for(size_t i = 0; i < length; i++){
        // printf("caca\n");
        intermediateArray[i].value = array[i];
        // printf("caca2\n");

        // printf("valeur de array[i] : %d", array[i]);
        intermediateArray[i].index = i;
        // printf("valeur de i : %d", intermediateArray[i].value);
    }
    printf("\n");
    //sort the storing array
    sort(algo, intermediateArray, length, compareIndexes, swapValues);
    // printf(" case 6672 :%d\n", intermediateArray[6671].value);
    // for(size_t i = 0; i < length; i++){
    //     printf("%d\n", intermediateArray[i].value);
    // }
    // printf("\n");
    // for(size_t i = 0; i < length; i++){
    //     printf("%ld\n", intermediateArray[i].index);
    // }
    //look if the sorting array is stable or no.
    // to do so: look for consecutives values and when you have some, you look if their indexes are increasing or not
    //if they are increasing, stable if not it is not stable.
    for(size_t i = 0; i < length - 1; i++){
        if(intermediateArray[i].value == intermediateArray[i + 1].value && intermediateArray[i].index > intermediateArray[i + 1].index){ // issue : we only look for 2 (quid if 3 consecutive?)
            // if(intermediateArray[i].index > intermediateArray[i + 1].index)
            //     return false;
            return false;
        }
    }
    return true;
    //caca


}
void stableSort(size_t algo, void *array, size_t length,
                int (*compare)(const void *, size_t i, size_t j),
                void (*swap)(void *array, size_t i, size_t j))
{
    globalCompare = compare;
    globalSwap = swap;
    // A modifier/compléter
    sort(algo, array, length, compare, swap);
}
